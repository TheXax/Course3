const express = require('express'); //фреймворк для создания веб-приложений
const multer = require('multer'); //для загрузки файлов
const fs = require('fs');
const path = require('path');

const app = express();
const port = 3000;

// Настройка multer для хранения загруженных файлов
const storage = multer.diskStorage({
    destination: (req, file, cb) => { //определяем куда загружаем данные
        cb(null, 'uploads/');
    },
    filename: (req, file, cb) => {
        cb(null, file.originalname);
    },
});

const upload = multer({ storage: storage }); //для обработки загрузок файлов с заданным хранилищем

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
    console.log(`Сервер запущен`);
});