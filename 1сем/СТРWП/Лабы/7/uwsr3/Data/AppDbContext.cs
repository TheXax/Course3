using Microsoft.EntityFrameworkCore;
using UWSR.Models;

namespace UWSR.Data
{
    public class AppDbContext : DbContext
    {
        public DbSet<Link> Links { get; set; } //Определяет свойство Links, которое представляет коллекцию объектов типа Link
        public DbSet<Comment> Comments { get; set; }
        public AppDbContext(DbContextOptions<AppDbContext> options)
            : base(options)
        {
            Database.EnsureCreated(); //сущетсвует ли бд, если нет, то создаётся
        }

        // настройка модели данных перед созданием базы данных
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);
        }
    }
}
