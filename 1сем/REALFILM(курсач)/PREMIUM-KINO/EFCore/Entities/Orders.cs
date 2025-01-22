using System;
using System.ComponentModel.DataAnnotations.Schema;

namespace REALFILM.EFCore.Entities
{
    public class Orders
    {
        public Guid Id { get; set; }
        public Guid Id_User { get; set; }
        public Guid Id_Schedule { get; set; }
        public int Number_Of_Seats { get; set; }
        public string Order_Status { get; set; }

        [NotMapped] //Атрибут, указывающий, что это свойство не должно отображаться в базе данных. 
        public Users User { get; set; }

    }
}
