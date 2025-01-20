using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;

namespace ASPCMVC07.Controllers
{
    public class CalcController : Controller
    {
        [Authorize(Roles = "Employee,Master")]
        public IActionResult Index()
        {
            ViewBag.CurrentAction = "Index";
            return View("Index");
        }

        [HttpPost] 
        public IActionResult Sum(float x, float y) //выбор действия
        {
            float result = x + y;
            ViewBag.Result = result;
            ViewBag.CurrentAction = "Sum";

            return View("Index");

           
        }
        public IActionResult Sum() //сам подсчёт
        {
            ViewBag.CurrentAction = "Sum";
            return View("Index");
        }

        [HttpPost]
        public IActionResult Min(float x, float y)
        {
            float result = x - y;
            ViewBag.Result = result;
            ViewBag.CurrentAction = "Min";
            return View("Index");
        }
        public IActionResult Min()
        {
            ViewBag.CurrentAction = "Min";
            return View("Index");
        }

        [HttpPost]
        public IActionResult Mul(float x, float y)
        {
            float result = x * y;
            ViewBag.Result = result;
            ViewBag.CurrentAction = "Mul";
            return View("Index");
        }

        public IActionResult Mul()
        {
            ViewBag.CurrentAction = "Mul";
            return View("Index");
        }

        [HttpPost]
        public IActionResult Div(float x, float y)
        {
            if (y != 0)
            {
                float result = x / y;
                ViewBag.Result = result;
                ViewBag.CurrentAction = "Div";
            }
            else
            {
                ViewBag.Error = "Division by zero is not allowed.";
                ViewBag.CurrentAction = "Div";
            }
            return View("Index");
        }
        public IActionResult Div()
        {
            ViewBag.CurrentAction = "Div";
            return View("Index");
        }
    }
}
