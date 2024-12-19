using Microsoft.AspNetCore.Mvc;

namespace ASPCMVC02.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}
//неправильно реализовано. Надо, чтобы оно по дефолту вызывало страницу html, а оно отображается какую-то часть или что-то такое она сказала
