var http = require('http');
var url = require('url');
var util = require('util');
var ee = require('events');
console.log('imported db-module');


let db = 
[
    {
        id: 1,
        name: "first",
        bday: "05-08-2004"
    },
    {
        id: 2,
        name: "second",
        bday: "17-10-1972"
    },
    {
        id: 3,
        name: "third",
        bday: "15-01-1988"
    }
];





function DB()
{
    this.select = () => 
    {
        console.log("[SELECT]\n");
        return JSON.stringify(db, null, 2);
    }


    this.insert = (insertString) => 
    {
        for (let i = 0; i < db.length; ++i)
            if (JSON.parse(insertString).id == db[i].id) { return; }
        db.push(JSON.parse(insertString));
        console.log("[INSERT]\n");
        return JSON.stringify(db, null, 2);
    }


    this.update = (updateString) => 
    {
        console.log("[UPDATE]");
        var jsonString = JSON.parse(updateString);
        console.log(jsonString);
        var id = jsonString.id; //извлекаеем id записи
        console.log("id to update: " + id + "\n");
        var index = db.findIndex(elem => elem.id === parseInt(id));
        db[index].name = jsonString.name;
        db[index].bday = jsonString.bday;
        return JSON.stringify(db[index], null, 2);
    }


    this.delete = (id) => 
    {
        console.log("[DELETE]\n");
        var index = db.findIndex(elem => elem.id === parseInt(id));
        var deleted = db[index];
        db.splice(index, 1);
        return JSON.stringify(deleted, null, 2);
    }

    this.commit = () => {
        console.log("[COMMIT] База данных зафиксирована.");
        return "Состояние БД зафиксировано.";
    }
} 


util.inherits(DB, ee.EventEmitter); //Устанавливает наследование от класса EventEmitter, позволяя экземплярам DB генерировать и обрабатывать события
exports.DB = DB;