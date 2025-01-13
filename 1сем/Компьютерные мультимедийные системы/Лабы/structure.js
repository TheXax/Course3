const zoomableImages = document.querySelectorAll('.zoomable');

zoomableImages.forEach(img => {
    img.addEventListener('click', function() {
        if (this.style.transform === 'scale(1)') {
            this.style.transform = 'scale(1.2)';
        }
    });

    img.addEventListener('mouseleave', function() {
        this.style.transform = 'scale(1)';
    });
});

//бургер
function toggleMenu() {
    const menu = document.getElementById('menu');
    menu.classList.toggle('no'); // Переключаем класс для скрытия
    menu.classList.toggle('yes'); // Переключаем класс для показа
}