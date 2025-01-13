const zoomableImages = document.querySelectorAll('.zoomable');

zoomableImages.forEach(img => {
    img.addEventListener('click', function() {
        // Увеличиваем изображение при клике
        if (this.style.transform === 'scale(1)') 
            this.style.transform = 'scale(1.2)'; // Увеличиваем изображение
        }
    );

    img.addEventListener('mouseleave', function() {
        // Возвращаем изображение к исходному размеру при уходе курсора
        this.style.transform = 'scale(1)';
    });
});


var textP6 = document.querySelector("#text_P6");
var pictureP6 = document.querySelector("#img_P6");
var textP1 = document.querySelector("#text_P1");
var pictureP1 = document.querySelector("#img_P1");

textP6.addEventListener("click", () => Show(textP6, pictureP6));
pictureP6.addEventListener("click", () => Hide(textP6, pictureP6));
textP1.addEventListener("click", () => Show(textP1, pictureP1));
pictureP1.addEventListener("click", () => Hide(textP1, pictureP1));

function Show(text, picture) {
    text.classList = "clickable inactive";
    picture.classList = "clickable active";
}

function Hide(text, picture) {
    picture.classList = "clickable inactive";
    text.classList = "clickable active";
}

//бургер
function toggleMenu() {
    const menu = document.getElementById('menu');
    menu.classList.toggle('no'); // Переключаем класс для скрытия
    menu.classList.toggle('yes'); // Переключаем класс для показа
}
