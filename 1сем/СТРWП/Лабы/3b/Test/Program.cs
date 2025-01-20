using ASPCMVC08.Data;
using Microsoft.AspNetCore.Identity; //фреймворк для авторизации
using Microsoft.EntityFrameworkCore; //для работы с бд


var builder = WebApplication.CreateBuilder(args);


// Добавляем контекст данных
builder.Services.AddDbContext<ApplicationDbContext>(options => //Добавляет контекст базы данных (ApplicationDbContext) в контейнер зависимостей
    options.UseSqlServer(builder.Configuration.GetConnectionString("DefaultConnection"))); //Указывает, что контекст будет использовать SQL Server в качестве базы данных

// Добавляем Identity
builder.Services.AddIdentity<IdentityUser, IdentityRole>() //аутентификация и авторизация, используя классы IdentityUser и IdentityRole
    .AddEntityFrameworkStores<ApplicationDbContext>(); //Указывает, что Identity будет использовать Entity Framework для хранения пользователей и ролей в базе данных, определенной в ApplicationDbContext

builder.Services.AddControllersWithViews();

var app = builder.Build();

//инициализация БД
//Область видимости (scope) используется для управления временем жизни сервисов и их зависимостями.
using (var scope = app.Services.CreateScope()) //создание области видимости для получения сервисов
{
    var services = scope.ServiceProvider; //получает поставщик услуг
    await DbInitializer.InitializeAsync(services); //вызов метода инициализации бд
}

//вкл middleware аутентификации и авторизации
app.UseAuthentication();
app.UseAuthorization();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");

app.Run();