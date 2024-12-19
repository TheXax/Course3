using Microsoft.AspNetCore.Mvc;

namespace ASPCMVC03.Controllers
{
    public class StartController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }

        public IActionResult One()
        {
            return Content("<h1>Start/One</h1>", "text/html");
        }

        public IActionResult Two()
        {
            return Content("<h1>Start/Two</h1>", "text/html");
        }

        public IActionResult Three()
        {
            return Content("<h1>Start/Three</h1>", "text/html");
        }
    }
}
