using System.Configuration; // Для работы с ConfigurationManager
using System.Reflection;
using Microsoft.EntityFrameworkCore;
using REALFILM.EFCore.Entities;

namespace REALFILM.EFCore
{
    public class DBContext : DbContext
    {
        // Определяем DbSet для каждой таблицы
        public DbSet<Users> Users { get; set; }
        public DbSet<Movie> Movie { get; set; }
        public DbSet<Schedule> Schedule { get; set; }
        public DbSet<Orders> Orders { get; set; }

        // Настройка параметров контекста базы данных
        protected override void OnConfiguring(DbContextOptionsBuilder builder)
        {
            // Получаем строку подключения из app.config
            string connectionString = ConfigurationManager.ConnectionStrings["DefaultConnection"].ConnectionString;
            builder.UseSqlServer(connectionString);
        }

        // Настройка модели данных в контексте базы данных
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            // Применяем конфигурации для моделей из текущей сборки
            modelBuilder.ApplyConfigurationsFromAssembly(Assembly.GetExecutingAssembly());
        }
    }
}
