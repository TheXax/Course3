const express = require('express');
const app = express();
const port = 3002;
const db = require('better-sqlite3')('source2.db');
const moment = require('moment');

app.use(express.json());

const init = () => {
    db.exec(`CREATE TABLE IF NOT EXISTS measurements (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    timestamp TEXT,
    value REAL
  )`);
};

app.get('/api/data', (req, res) => {
    const rows = db.prepare('SELECT * FROM measurements').all();
    res.json({ time: new Date(), data: rows });
});

app.get('/api/time', (req, res) => {
    res.json({ time: new Date().toISOString() });
});

app.post('/api/push', (req, res) => {
    const { data } = req.body;
    const insert = db.prepare('INSERT INTO measurements (timestamp, value) VALUES (?, ?)');

    if (Array.isArray(data)) {
        data.forEach(d => {
            const existingEntry = db.prepare(
                'SELECT 1 FROM measurements WHERE timestamp = ? AND value = ?'
            ).get(d.timestamp, d.value);

            if (!existingEntry) {
                insert.run(d.timestamp, d.value);
            }
        });
        return res.sendStatus(200);
    }

    if (data && typeof data === 'object' && data.timestamp && data.value !== undefined) {
        insert.run(data.timestamp, data.value);
        return res.sendStatus(200);
    }

    return res.sendStatus(400); 
});

setInterval(() => {
    db.prepare('INSERT INTO measurements (timestamp, value) VALUES (?, ?)')
        .run(moment().toISOString(), Math.random() * 100);
}, 15000);

init();

app.listen(port, () => console.log(`Source 2 listening on port ${port}`));