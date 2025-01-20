using Microsoft.EntityFrameworkCore.Storage.ValueConversion.Internal;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace UWSR.Models
{
    public class Comment
    {
        [Key]
        [DatabaseGenerated(DatabaseGeneratedOption.Identity)] //значение для этого поля будет автоматически генерироваться базой данных
        public int Id { get; set; }
        public string SessionId { get; set; }
        public DateTime Stamp { get; init; } = DateTime.Now; //Stamp представляет временную метку, когда комментарий был создан
        public string Text { get; set; }
        public Link Link { get; set; }
    }
}
