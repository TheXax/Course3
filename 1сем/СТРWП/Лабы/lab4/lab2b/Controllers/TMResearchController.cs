using lab2b.Models;
using Microsoft.AspNetCore.Mvc;
using System.Diagnostics;

namespace lab2b.Controllers
{
    public class TMResearchController : Controller
    {
        [HttpGet]
        public IActionResult M01(string? id = null)
        {
            var message = "GET:M01";
            if (!string.IsNullOrEmpty(id))
            {
                message += $" - {id}";
            }

            return Content(message);
        }

        [HttpGet]
        public IActionResult M02(string? id = null)
        {
            var message = "GET:M02";
            if (!string.IsNullOrEmpty(id))
            {
                message += $" - {id}";
            }

            return Content(message);
        }

        [HttpGet]
        public IActionResult M03(string? id = null)
        {
            var message = "GET:M03";
            if (!string.IsNullOrEmpty(id))
            {
                message += $" - {id}";
            }

            return Content(message);
        }

        [HttpGet]
        public IActionResult MXX()
        {
            return Content("GET:MXX");
        }
    }
}