const express = require('express');
const { Sequelize, DataTypes } = require('sequelize'); //для работы с БД
const app = express();
app.use(express.json()); //для обработки json-запросов

// Настройка Sequelize с MSSQL
const sequelize = new Sequelize('SVA', 'sa', '123456789', {
    host: 'localhost',
    dialect: 'mssql',
    port: 1433,
    pool: { max: 5, min: 0, acquire: 30000, idle: 10000 },
    dialectOptions: {
        options: {
            encrypt: false,
            trustServerCertificate: true
        }
    }
});

// Определение моделей
const Faculty = sequelize.define('faculty', {
    faculty: { type: DataTypes.STRING(10), primaryKey: true },
    faculty_name: { type: DataTypes.STRING(100), allowNull: false } // NOT NULL
}, { tableName: 'faculty', timestamps: false });

const Pulpit = sequelize.define('pulpit', {
    pulpit: { type: DataTypes.STRING(10), primaryKey: true },
    pulpit_name: { type: DataTypes.STRING(100), allowNull: false }, // NOT NULL
    faculty: { type: DataTypes.STRING(10), references: { model: Faculty, key: 'faculty' } } // FOREIGN KEY
}, { tableName: 'pulpit', timestamps: false });

const Subject = sequelize.define('subject', {
    subject: { type: DataTypes.STRING(10), primaryKey: true },
    subject_name: { type: DataTypes.STRING(100), allowNull: false }, // NOT NULL
    pulpit: { type: DataTypes.STRING(10), references: { model: Pulpit, key: 'pulpit' } } // FOREIGN KEY
}, { tableName: 'subject', timestamps: false });

const Teacher = sequelize.define('teacher', {
    teacher: { type: DataTypes.STRING(10), primaryKey: true },
    teacher_name: { type: DataTypes.STRING(100), allowNull: false }, // NOT NULL
    pulpit: { type: DataTypes.STRING(10), references: { model: Pulpit, key: 'pulpit' } } // FOREIGN KEY
}, { tableName: 'teacher', timestamps: false });

const AuditoriumType = sequelize.define('auditoriumtype', {
    auditorium_type: { type: DataTypes.STRING(10), primaryKey: true },
    auditorium_typename: { type: DataTypes.STRING(100), allowNull: false } // NOT NULL
}, { tableName: 'auditoriumtype', timestamps: false });

const Auditorium = sequelize.define('auditorium', {
    auditorium: { type: DataTypes.STRING(10), primaryKey: true },
    auditorium_name: { type: DataTypes.STRING(100), allowNull: false }, // NOT NULL
    auditorium_capacity: { type: DataTypes.STRING(100), allowNull: false }, // NOT NULL
    auditorium_type: { type: DataTypes.STRING(10), references: { model: AuditoriumType, key: 'auditorium_type' } } // FOREIGN KEY
}, { tableName: 'auditorium', timestamps: false });

// Связывание моделей
Faculty.hasMany(Pulpit, { foreignKey: 'faculty' });
Pulpit.hasMany(Subject, { foreignKey: 'pulpit' });
Pulpit.hasMany(Teacher, { foreignKey: 'pulpit' });
AuditoriumType.hasMany(Auditorium, { foreignKey: 'auditorium_type' });

// Проверка подключения
(async () => {
    try {
        await sequelize.authenticate();
        console.log('Подключение к базе данных успешно установлено');
        // await sequelize.sync({ force: true }); // Используйте с осторожностью, только для создания таблиц
    } catch (error) {
        console.error('Ошибка подключения:', error.message);
    }
})();

// Статический HTML-файл
app.get('/', (req, res) => {
    res.send('<h1>Добро пожаловать на сервер БД SVA</h1>');
});

// GET-запросы
app.get('/api/faculties', async (req, res) => {
    try {
        const faculties = await Faculty.findAll();
        res.json(faculties);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

app.get('/api/pulpits', async (req, res) => {
    try {
        const pulpits = await Pulpit.findAll();
        res.json(pulpits);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

app.get('/api/subjects', async (req, res) => {
    try {
        const subjects = await Subject.findAll();
        res.json(subjects);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

app.get('/api/teachers', async (req, res) => {
    try {
        const teachers = await Teacher.findAll();
        res.json(teachers);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

app.get('/api/auditoriumstypes', async (req, res) => {
    try {
        const auditoriumTypes = await AuditoriumType.findAll();
        res.json(auditoriumTypes);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

app.get('/api/auditoriums', async (req, res) => {
    try {
        const auditoriums = await Auditorium.findAll();
        res.json(auditoriums);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

// POST-запросы
app.post('/api/faculties', async (req, res) => {
    try {
        const faculty = await Faculty.create(req.body);
        res.json(faculty);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

/*{
    "faculty": "F4",
    "faculty_name": "Экономика"
}*/

app.post('/api/pulpits', async (req, res) => {
    try {
        const pulpit = await Pulpit.create(req.body);
        res.json(pulpit);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});

/*{
    "pulpit": "P4",
    "pulpit_name": "Экономика и управление",
    "faculty": "F4"
}*/

app.post('/api/subjects', async (req, res) => {
    try {
        const subject = await Subject.create(req.body);
        res.json(subject);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
/*{
    "subject": "S4",
    "subject_name": "Экономика",
    "pulpit": "P4"
}*/

app.post('/api/teachers', async (req, res) => {
    try {
        const teacher = await Teacher.create(req.body);
        res.json(teacher);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
/*{
    "teacher": "T4",
    "teacher_name": "Смирнов С.С.",
    "pulpit": "P4"
}*/

app.post('/api/auditoriumstypes', async (req, res) => {
    try {
        const auditoriumType = await AuditoriumType.create(req.body);
        res.json(auditoriumType);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
/*{
    "auditorium_type": "AT4",
    "auditorium_typename": "New"
}*/

app.post('/api/auditoriums', async (req, res) => {
    try {
        const auditorium = await Auditorium.create(req.body);
        res.json(auditorium);
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
/*{
    "auditorium": "A4",
    "auditorium_name": "Аудитория 404",
    "auditorium_capacity": "40",
    "auditorium_type": "AT4"
}*/

// PUT-запросы
app.put('/api/faculties', async (req, res) => {
    try {
        const [updated] = await Faculty.update(req.body, { where: { faculty: req.body.faculty } });
        if (updated) {
            const faculty = await Faculty.findOne({ where: { faculty: req.body.faculty } });
            res.json(faculty);
        } else {
            res.status(404).json({ error: 'Факультет не найден' });
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
/*{
    "faculty": "F4",
    "faculty_name": "Экономика и управление"
}*/

app.put('/api/pulpits', async (req, res) => {
    try {
        const [updated] = await Pulpit.update(req.body, { where: { pulpit: req.body.pulpit } });
        if (updated) {
            const pulpit = await Pulpit.findOne({ where: { pulpit: req.body.pulpit } });
            res.json(pulpit);
        } else {
            res.status(404).json({ error: 'Кафедра не найдена' });
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
/*{
    "pulpit": "P4",
    "pulpit_name": "Экономика и управление обновлено",
    "faculty": "F4"
}*/

app.put('/api/subjects', async (req, res) => {
    try {
        const [updated] = await Subject.update(req.body, { where: { subject: req.body.subject } });
        if (updated) {
            const subject = await Subject.findOne({ where: { subject: req.body.subject } });
            res.json(subject);
        } else {
            res.status(404).json({ error: 'Дисциплина не найдена' });
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
/*{
    "subject": "S4",
    "subject_name": "Экономика обновлено",
    "pulpit": "P4"
}*/

app.put('/api/teachers', async (req, res) => {
    try {
        const [updated] = await Teacher.update(req.body, { where: { teacher: req.body.teacher } });
        if (updated) {
            const teacher = await Teacher.findOne({ where: { teacher: req.body.teacher } });
            res.json(teacher);
        } else {
            res.status(404).json({ error: 'Преподаватель не найден' });
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
/*{
    "teacher": "T4",
    "teacher_name": "Смирнов С.С. обновленный",
    "pulpit": "P4"
}*/

app.put('/api/auditoriumstypes', async (req, res) => {
    try {
        const [updated] = await AuditoriumType.update(req.body, { where: { auditorium_type: req.body.auditorium_type } });
        if (updated) {
            const auditoriumType = await AuditoriumType.findOne({ where: { auditorium_type: req.body.auditorium_type } });
            res.json(auditoriumType);
        } else {
            res.status(404).json({ error: 'Тип аудитории не найден' });
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
/*{
    "auditorium_type": "AT4",
    "auditorium_typename": "New 2.0"
}*/

app.put('/api/auditoriums', async (req, res) => {
    try {
        const [updated] = await Auditorium.update(req.body, { where: { auditorium: req.body.auditorium } });
        if (updated) {
            const auditorium = await Auditorium.findOne({ where: { auditorium: req.body.auditorium } });
            res.json(auditorium);
        } else {
            res.status(404).json({ error: 'Аудитория не найдена' });
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
/*{
    "auditorium": "A4",
    "auditorium_name": "Аудитория 404 обновленная",
    "auditorium_capacity": "50",
    "auditorium_type": "AT4"
}*/

// DELETE-запросы
app.delete('/api/faculties/:faculty', async (req, res) => {
    try {
        const faculty = await Faculty.findOne({ where: { faculty: req.params.faculty } });
        if (faculty) {
            await faculty.destroy();
            res.json(faculty);
        } else {
            res.status(404).json({ error: 'Факультет не найден' });
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
//http://localhost:3000/api/faculties/F4

app.delete('/api/pulpits/:pulpit', async (req, res) => {
    try {
        const pulpit = await Pulpit.findOne({ where: { pulpit: req.params.pulpit } });
        if (pulpit) {
            await pulpit.destroy();
            res.json(pulpit);
        } else {
            res.status(404).json({ error: 'Кафедра не найдена' });
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
// http://localhost:3000/api/pulpits/P4

app.delete('/api/subjects/:subject', async (req, res) => {
    try {
        const subject = await Subject.findOne({ where: { subject: req.params.subject } });
        if (subject) {
            await subject.destroy();
            res.json(subject);
        } else {
            res.status(404).json({ error: 'Дисциплина не найдена' });
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
//http://localhost:3000/api/subjects/S4

app.delete('/api/teachers/:teacher', async (req, res) => {
    try {
        const teacher = await Teacher.findOne({ where: { teacher: req.params.teacher } });
        if (teacher) {
            await teacher.destroy();
            res.json(teacher);
        } else {
            res.status(404).json({ error: 'Преподаватель не найден' });
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
//http://localhost:3000/api/teachers/T4

app.delete('/api/auditoriumstypes/:auditorium_type', async (req, res) => {
    try {
        const auditoriumType = await AuditoriumType.findOne({ where: { auditorium_type: req.params.auditorium_type } });
        if (auditoriumType) {
            await auditoriumType.destroy();
            res.json(auditoriumType);
        } else {
            res.status(404).json({ error: 'Тип аудитории не найден' });
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
//http://localhost:3000/api/auditoriumstypes/AT4

app.delete('/api/auditoriums/:auditorium', async (req, res) => {
    try {
        const auditorium = await Auditorium.findOne({ where: { auditorium: req.params.auditorium } });
        if (auditorium) {
            await auditorium.destroy();
            res.json(auditorium);
        } else {
            res.status(404).json({ error: 'Аудитория не найдена' });
        }
    } catch (error) {
        res.status(500).json({ error: error.message });
    }
});
//http://localhost:3000/api/auditoriums/A4

// Запуск сервера
const PORT = 3000;
app.listen(PORT, () => {
    console.log(`Сервер запущен на порту ${PORT}`);
});