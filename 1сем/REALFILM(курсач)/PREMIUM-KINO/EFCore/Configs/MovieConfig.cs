using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using REALFILM.EFCore.Entities;

namespace REALFILM.EFCore.Configs
{
    public class MovieConfig : IEntityTypeConfiguration<Movie>
    {
        public void Configure(EntityTypeBuilder<Movie> entity)
        {
            entity.ToTable(nameof(Movie)); //nameof(Movie) для обеспечения безопасности при рефакторинге

            entity.HasKey(x => x.Id);
            entity.Property(x => x.Title).IsRequired().HasMaxLength(128);
            entity.Property(x => x.Director).IsRequired().HasMaxLength(128);
            entity.Property(x => x.Genre).IsRequired().HasMaxLength(64);
            entity.Property(x => x.Duration).IsRequired();
            entity.Property(x => x.Rating).HasColumnType("real");
            entity.Property(x => x.Photo).IsRequired();

            entity.HasMany(x => x.Schedule);//у каждого фильма может быть много связанных записей в таблице расписания (Schedule). Это определяет связь "один-ко-многим" между сущностями Movie и Schedule
        }
    }
}
