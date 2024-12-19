using Microsoft.AspNetCore.Mvc;

namespace ASPCMVC04.Controllers
{
    public class StatusController : Controller
    {
        public IActionResult S200()
        {
            int status = new Random().Next(200, 299);
            return StatusCode(status);
        }

        public IActionResult S300()
        {
            int status = new Random().Next(300, 399);
            return StatusCode(status);
        }

        public IActionResult S500()
        {
            try
            {
                int x = 0;
                int result = 10 / x;
            }
            catch (DivideByZeroException)
            {
                return StatusCode(500, "Internal Server Error (500)");
            }

            return Ok();
        }
    }
}
