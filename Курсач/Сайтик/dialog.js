var dialogOn = false;//открыто ли окно

function dialog_window() {
  document.body.innerHTML +=
    "<div id='dialog' class='dialog' style='margin-left:-45px;'>" +
    "<div class='label' onclick='openDialog()'>Нажми, чтобы спросить!</div>" +
    "<div class='header'>История:</div>" +
    "<div class='history' id='history'></div>" +
    "<div class='question'><input id='Qdialog' placeholder='Введите вопрос'/> <br><button onclick='ask(\"Qdialog\")'>Спросить</button></div>" +
    "</div>";

    //голосовой ввод
  window.ya.speechkit.settings.apikey = "5c6d6536-b453-4589-9bc7-f16c7a795106";
  var textline = new ya.speechkit.Textline("Qdialog", {
    onInputFinished: function (text) {
      document.getElementById("Qdialog").value = text;
    },
  });
}

function openDialog() {
  if (dialogOn) {
    $("#dialog").animate({ "margin-left": "-35px" }, 1000, function () {});
    dialogOn = false;
  } else {
    $("#dialog").animate({ "margin-left": "-1100px" }, 1000, function () {});
    dialogOn = true;
    clearInterval(timer);
  }
}

//обработка вопроса
function ask(questionInput) {
  var question = document.getElementById(questionInput).value;
  dialogOn = true;
  var newDiv = document.createElement("div");
  newDiv.className = "question"; //класс для нового эл-та
  newDiv.innerHTML = question;
  document.getElementById("history").appendChild(newDiv);
  +"</div>";
  newDiv = document.createElement("div");
  newDiv.className = "answer";
  newDiv.innerHTML = getAnswer(question);
  //аудио для ответа
  newDiv.innerHTML +=
    "<audio controls='true' autoplay='true' " +
    "src='http://tts.voicetech.yandex.net/" +
    "generate?format=wav&lang=ru-RU&" +
    "key=4a4d3a13-d206-45fc-b8fb-e5a562c9f587&" +
    "text=" +
    newDiv.innerText +
    "'></audio>";
  document.getElementById("history").appendChild(newDiv);
  if (newDiv.lastChild.tagName == "AUDIO") {
    newDiv.lastChild.play();
  }
  //прокрутка контейнера
  document.getElementById("history").scrollTop =
    document.getElementById("history").scrollHeight;
  document.getElementById(questionInput).value = "";
}

function incSize() {
  let elId = event.currentTarget.id
  document.getElementById(`${elId}`).style.width='70%'
}
function decSize() {
  let elId = event.currentTarget.id
  document.getElementById(`${elId}`).style.width='50%'
}