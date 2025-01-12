using lab2b_task2.Models;
using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;

namespace lab2b_task2.Controllers
{
    [Route("it")]
    public class TAResearchController : Controller
    {
        [HttpGet("{n:int}/{letters}")]
        public IActionResult M04(int n, string letters)
        {
            return Content($"GET:M04:/{n}/{letters}");
        }

        [HttpGet("{b:bool}/{letters:alpha}")]
        public IActionResult M05(bool b, string letters)
        {
            return Content($"GET:M05:/{b}/{letters}");
        }

        [HttpPost("{b:bool}/{letters:alpha}")]
        public IActionResult M05Post(bool b, string letters)
        {
            return Content($"POST:M05:/{b}/{letters}");
        }
        
        [Route("{f:float}/{letters:minlength(2):maxlength(5)}")]
        [AcceptVerbs("DELETE", "GET")]
        public IActionResult M06(float f, string letters)
        {
            // Получаем HTTP-метод запроса
            string httpMethod = Request.Method;
            return Content($"{httpMethod}:M06:/{f}/{letters}"); //сделать определение метода
        }

        
        [HttpPut("{letters:minlength(3):maxlength(4):alpha}/{n:int:range(100,200)}")]
        public IActionResult M07(string letters, int n)
        {
            return Content($"PUT:M07:/{letters}/{n}/");
        }

        [HttpPost("{mail:regex(^\\S+@\\S+\\.\\S+$)}")]
        public IActionResult M08(string mail)
        {
            return Content($"POST:M08:/mail/{mail}");
        }
    }
}
