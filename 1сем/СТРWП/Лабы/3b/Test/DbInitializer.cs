using Microsoft.AspNetCore.Identity;
using Microsoft.EntityFrameworkCore;
using ASPCMVC08.Data;

namespace ASPCMVC08.Data
{
    public static class DbInitializer
    {
        public static async Task InitializeAsync(IServiceProvider serviceProvider) //метод инициализацию базы данных, получающий доступ к зарегистрированным сервисам с помощью IServiceProvider
        {
            using var context = new ApplicationDbContext( //создание экземпляра для работы с бд
                serviceProvider.GetRequiredService<DbContextOptions<ApplicationDbContext>>()); //получение параметров контекста бд

            var userManager = serviceProvider.GetRequiredService<UserManager<IdentityUser>>(); //Получает экземпляр UserManager
            var roleManager = serviceProvider.GetRequiredService<RoleManager<IdentityRole>>(); //Получает экземпляр RoleManager

            if (!await roleManager.RoleExistsAsync("Administrator")) //если роли админ нет
            {
                var role = new IdentityRole("Administrator"); //новый объект роли
                await roleManager.CreateAsync(role); //создание роли в бд
            }

            if (await userManager.FindByNameAsync("Administrator") == null) //если пользователя админ нет
            {
                var user = new IdentityUser { UserName = "Administrator", Email = "admin@example.com" };
                var result = await userManager.CreateAsync(user, "Admin@123456");

                if (result.Succeeded) //успешно ли создание
                {
                    await userManager.AddToRoleAsync(user, "Administrator"); //назначения роли пользователю
                }
            }
        }
    }
}