using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Builders;
using REALFILM.EFCore.Entities;

namespace REALFILM.EFCore.Configs
{
    public class UsersConfig : IEntityTypeConfiguration<Users>
    {
        public void Configure(EntityTypeBuilder<Users> entity)
        {
            entity.ToTable(nameof(Users));

            entity.HasKey(x => x.Id);
            entity.Property(x => x.Name).IsRequired().HasMaxLength(64);
            entity.Property(x => x.Surname).IsRequired().HasMaxLength(64);
            entity.Property(x => x.Login).IsRequired().HasMaxLength(64);
            entity.Property(x => x.Email).IsUnicode(false).HasMaxLength(64);
            entity.Property(x => x.Phone).IsUnicode(false).HasMaxLength(64);
            entity.Property(x => x.Role).IsRequired();
            entity.Property(x => x.Password).IsUnicode(false).HasMaxLength(64);

            entity.HasMany(x => x.Orders);
        }

    }
}
