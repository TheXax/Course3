const express = require('express');
const app = express();
const port = 4000;
const axios = require('axios');
const db = require('better-sqlite3')('central.db');
const cron = require('node-cron');
const winston = require('winston');
const moment = require('moment');

const sources = [
    { name: 'source1', url: 'http://localhost:3001/api/data', pushUrl: 'http://localhost:3001/api/push', timeUrl: 'http://localhost:3001/api/time' },
    { name: 'source2', url: 'http://localhost:3002/api/data', pushUrl: 'http://localhost:3002/api/push', timeUrl: 'http://localhost:3002/api/time' }
];

const logger = winston.createLogger({
    level: 'info',
    format: winston.format.combine(
        winston.format.timestamp(),
        winston.format.printf(({ level, message, timestamp }) => `${timestamp} [${level}]: ${message}`)
    ),
    transports: [new winston.transports.Console(), new winston.transports.File({ filename: 'central.log' })]
});

app.use(express.json());

const init = () => {
    db.exec(`CREATE TABLE IF NOT EXISTS received_data (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    source TEXT,
    timestamp TEXT,
    value REAL
  )`);
};

cron.schedule('* * * * *', async () => {
    for (const [index, source] of sources.entries()) {
        try {
            const res = await axios.get(source.url);
            const { data } = res;
            if (!data || !data.data) continue;
            data.data.forEach(entry => {
                const existingEntry = db.prepare('SELECT 1 FROM received_data WHERE source = ? AND timestamp = ?')
                    .get(source.name, entry.timestamp);

                if (!existingEntry) {
                    db.prepare('INSERT INTO received_data (source, timestamp, value) VALUES (?, ?, ?)')
                        .run(source.name, entry.timestamp, entry.value);
                }
            });

            logger.info(`Fetched ${data.data.length} rows from ${source.name}`);
        } catch (err) {
            logger.error(`Error fetching from ${source.name}: ${err.message}`);
        }

        try {
            const { data } = await axios.get(source.timeUrl);
            const sourceTime = new Date(data.time);
            const localTime = new Date();

            const diffMs = Math.abs(localTime - sourceTime);
            const diffSec = diffMs / 1000;

            if (diffSec > 3) {
                logger.warn(`[${index}] Time difference with ${source.name}: ${diffSec.toFixed(2)} seconds`);
            } else {
                logger.info(`[${index}] Time sync OK with ${source.name} (diff: ${diffSec.toFixed(2)}s)`);
            }
        } catch (err) {
            logger.error(`[${index}] Failed to check time sync with ${source.name}: ${err.message}`);
        }
    }
});

app.get('/api/data', (req, res) => {
    const rows = db.prepare('SELECT * FROM received_data').all();
    res.json({ time: new Date(), data: rows });
});

app.get('/api/status', (req, res) => {
    const rows = db.prepare('SELECT source, COUNT(*) as count FROM received_data GROUP BY source').all();
    res.json(rows);
});

setInterval(async () => {
    const instertData = { value: Math.random() * 100, timestamp: moment().toISOString() };

    db.prepare('INSERT INTO received_data (source, timestamp, value) VALUES (?, ?, ?)')
        .run('central', instertData.timestamp, instertData.value);

    for (const source of sources) {
        try {
            await axios.post(source.pushUrl, { data: instertData });
            logger.info(`Pushed to ${source.name}`);
        } catch (err) {
            logger.error(`Error pushing to ${source.name}: ${err.message}`);
        }
    }
}, 15000);

init();

app.listen(port, () => logger.info(`Central service listening on port ${port}`));
