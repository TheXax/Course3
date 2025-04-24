const express = require('express');
const multer = require('multer');
const fs = require('fs');

const app = express();
const port = 3000;

// Настройка multer для хранения загруженных файлов
const storage = multer.diskStorage({
    destination: (req, file, cb) => {
        cb(null, 'uploads/');
    },
    filename: (req, file, cb) => {
        cb(null, file.originalname);
    },
});

const upload = multer({ storage: storage });

// Создание директории для загруженных файлов
if (!fs.existsSync('uploads')) {
    fs.mkdirSync('uploads');
}

// Обработка POST-запроса на загрузку файла
app.post('/upload', upload.single('file'), (req, res) => {
    console.log('Файл загружен:', req.file);
    res.send('Файл успешно загружен!');
});

// Запуск сервера
app.listen(port, () => {
    console.log(`Сервер запущен на http://localhost:${port}`);
});