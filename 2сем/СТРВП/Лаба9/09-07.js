const axios = require('axios'); //библиотека для выполнения HTTP-запросов
const FormData = require('form-data');
const fs = require('fs');

const form = new FormData();
form.append('file', fs.createReadStream('MyFile.png'));

axios.post('http://localhost:3000/upload', form, {
    headers: {
        ...form.getHeaders(),
    },
})
.then(response => {
    console.log('Файл успешно отправлен:', response.data);
})
.catch(error => {
    console.error('Ошибка при отправке файла:', error);
});
























//insomnia  http://localhost:3000/upload
