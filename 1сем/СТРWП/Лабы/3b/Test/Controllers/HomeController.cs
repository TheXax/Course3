using Microsoft.AspNetCore.Mvc;

namespace ASPCMVC08.Controllers
{
    public class HomeController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}