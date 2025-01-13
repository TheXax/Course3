//бургер
function toggleMenu() {
    const menu = document.getElementById('menu');
    menu.classList.toggle('no'); // Переключаем класс для скрытия
    menu.classList.toggle('yes'); // Переключаем класс для показа
}