using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Mvc;
using ASPCMVC08.Models;
using Microsoft.Extensions.Logging;

namespace ASPCMVC08.Controllers
{
    public class AdminController : Controller
    {
        //поля для управления
        private readonly UserManager<IdentityUser> _userManager; //UserManager предоставляет методы для работы с пользователями (создание, обновление и удаление)
        private readonly RoleManager<IdentityRole> _roleManager; //RoleManager предоставляет методы для работы с ролями (создание и удаление)
        private readonly SignInManager<IdentityUser> _signInManager; //Предоставляет методы для аутентификации пользователей
        private readonly ILogger<AdminController> _logger; //позволяет записывать действия и ошибки

        //конструктор
        public AdminController(
            ILogger<AdminController> logger,
            UserManager<IdentityUser> userManager,
            RoleManager<IdentityRole> roleManager,
            SignInManager<IdentityUser> signInManager)
        { //инициализация полей
            _logger = logger;
            _userManager = userManager;
            _roleManager = roleManager;
            _signInManager = signInManager;
        }
        [AllowAnonymous] //также и для не авторизованных пользователей
        //метод сохранения смс об ошибке
        public IActionResult Error(string message, string returnController = "Home", string returnAction = "Index")
        {
            //сохранение значений в ViewBag, чтобы передать в представление
            ViewBag.Message = message;
            ViewBag.ReturnController = returnController;
            ViewBag.ReturnAction = returnAction;
            return View();
        }
        // GET: Admin/Index
        [Authorize(Roles = "Administrator")] //для админа
        public async Task<IActionResult> Index()
        {
            var users = _userManager.Users.ToList(); //получили массив/список пользователей и их ролей
            var userRolesViewModel = new List<UserRolesViewModel>(); //создали список для хранения

            foreach (var user in users)
            {
                var roles = await _userManager.GetRolesAsync(user); //получение роли
                userRolesViewModel.Add(new UserRolesViewModel //добавление информации в список
                {
                    UserId = user.Id,
                    UserName = user.UserName,
                    Roles = roles
                });
            }

            ViewBag.CurrentUserName = User.Identity.Name;
            ViewBag.CurrentUserRoles = await _userManager.GetRolesAsync(await _userManager.GetUserAsync(User));

            return View(userRolesViewModel);
        }
        // Home [GET]
        [AllowAnonymous] //для всех пользователей
        [HttpGet]
        public IActionResult Register(string returnController = "Home", string returnAction = "Index") //Метод для отображения формы регистрации
        {
            ViewBag.ReturnController = returnController;
            ViewBag.ReturnAction = returnAction;
            return View();
        }

        [AllowAnonymous]
        [HttpPost]
        public async Task<IActionResult> Register(string userName, string password, string returnController = "Home", string returnAction = "Index")
        {
            var user = new IdentityUser { UserName = userName }; //создание
            var result = await _userManager.CreateAsync(user, password); //добавление пользователя с указанным паролем в бд

            if (result.Succeeded) //успешна ли регистрация
            {
                await _signInManager.SignInAsync(user, isPersistent: false); //аутентифицирует пользователя
                return RedirectToAction(returnAction, returnController); //перенаправляет на новое действие Humster_12345_password - старый пароль, Humster@12345 - новый
            }
            else
            {
                foreach (var error in result.Errors)
                {
                    ModelState.AddModelError("", error.Description); //добавляет ошибку в модель
                }
                ViewBag.ReturnController = returnController;
                ViewBag.ReturnAction = returnAction;
                return View();
            }
        }

        [AllowAnonymous]
        [HttpGet]
        public IActionResult SignIn(string returnController = "Home", string returnAction = "Index") //форма представления входа
        {
            ViewBag.ReturnController = returnController;
            ViewBag.ReturnAction = returnAction;
            return View();
        }


        [AllowAnonymous]
        [HttpPost]
        public async Task<IActionResult> SignIn(string userName, string password, string returnController = "Home", string returnAction = "Index") //обработка входа
        {
            var result = await _signInManager.PasswordSignInAsync(userName, password, isPersistent: false, lockoutOnFailure: false); //попытка аутентификаиции пользователя с указанными именем и паролем

            if (result.Succeeded)
            {
                return RedirectToAction(returnAction, returnController); //перенаправление
            }
            else
            {
                ModelState.AddModelError("", "Invalid login attempt.");
                ViewBag.ReturnController = returnController;
                ViewBag.ReturnAction = returnAction;
                return View();
            }
        }


        [Authorize] //для аутентифицированных
        [HttpGet]
        public IActionResult SignOut() //получение представления выхода
        {
            ViewBag.ReturnController = "Home";
            ViewBag.ReturnAction = "Index";
            return View();
        }

        [Authorize]
        [HttpPost]
        public async Task<IActionResult> SignOut(string returnController = "Home", string returnAction = "Index") //метод обработки выхода
        {
            await _signInManager.SignOutAsync(); //асинхронно выполняет выход пользователя из системы
            return RedirectToAction(returnAction, returnController); //перенаправление
        }

        [Authorize]
        [HttpGet]
        public IActionResult ChangePassword(string returnController = "Home", string returnAction = "Index") //представление/форма смены пароля
        {
            ViewBag.ReturnController = returnController;
            ViewBag.ReturnAction = returnAction;
            return View();
        }

        [Authorize]
        [HttpPost] //логика смены пароля
        public async Task<IActionResult> ChangePassword(string currentPassword, string newPassword, string returnController = "Home", string returnAction = "Index")
        {
            _logger.LogInformation("ChangePassword called with currentPassword: {currentPassword}, newPassword: {newPassword}", currentPassword, newPassword); //запись о попытке смены пароля

            var user = await _userManager.GetUserAsync(User); //получение текущего пользователя
            if (user == null)
            {
                _logger.LogError("User is null");
                return RedirectToAction("Login", "Account");
            }

            var result = await _userManager.ChangePasswordAsync(user, currentPassword, newPassword); //изменение пароля
            if (result.Succeeded)
            {
                _logger.LogInformation("Password changed successfully for user: {userId}", user.Id);
                await _signInManager.RefreshSignInAsync(user);//обновление аутентификации
                return RedirectToAction(returnAction, returnController);
            }
            else
            {
                foreach (var error in result.Errors)
                {
                    _logger.LogError("Error changing password: {errorDescription}", error.Description);
                    ModelState.AddModelError("", error.Description);
                }
                ViewBag.ReturnController = returnController;
                ViewBag.ReturnAction = returnAction;
                return View();
            }
        }



        [Authorize(Roles = "Administrator")]
        [HttpGet]
        public IActionResult CreateUser(string returnController = "Admin", string returnAction = "Index") //форма создания
        {
            ViewBag.ReturnController = returnController;
            ViewBag.ReturnAction = returnAction;
            return View();
        }

        [Authorize(Roles = "Administrator")]
        [HttpPost]
        public async Task<IActionResult> CreateUser(string userName, string password, string returnController = "Admin", string returnAction = "Index") //метод
        {
            var user = new IdentityUser { UserName = userName }; //создание
            var result = await _userManager.CreateAsync(user, password); //создание в бд

            if (result.Succeeded)
            {
                return RedirectToAction(returnAction, returnController);
            }
            else
            {
                foreach (var error in result.Errors)
                {
                    ModelState.AddModelError("", error.Description);
                }
                ViewBag.ReturnController = returnController;
                ViewBag.ReturnAction = returnAction;
                return View();
            }
        }

        [Authorize(Roles = "Administrator")]
        [HttpGet] //форма удаления
        public IActionResult DeleteUser(string returnController = "Admin", string returnAction = "Index")
        {
            ViewBag.ReturnController = returnController;
            ViewBag.ReturnAction = returnAction;
            return View();
        }

        [Authorize(Roles = "Administrator")]
        [HttpPost] //логика удаления
        public async Task<IActionResult> DeleteUser(string userName, string returnController = "Admin", string returnAction = "Index")
        {
            var user = await _userManager.FindByNameAsync(userName); //поиск по имени

            if (user != null) //есть
            {
                var result = await _userManager.DeleteAsync(user); //асинхронно удаляет из бд

                if (result.Succeeded)
                {
                    return RedirectToAction(returnAction, returnController); //перенаправление на главную страницу
                }
                else
                {
                    foreach (var error in result.Errors)
                    {
                        ModelState.AddModelError("", error.Description);
                    }
                    ViewBag.ReturnController = returnController;
                    ViewBag.ReturnAction = returnAction;
                    return View();
                }
            }
            else //пользователь не найден
            {
                ModelState.AddModelError("", "User not found.");
                ViewBag.ReturnController = returnController;
                ViewBag.ReturnAction = returnAction;
                return View();
            }
        }

        [Authorize(Roles = "Administrator")]
        [HttpGet] //назначения роли
        public IActionResult Assign(string returnController = "Admin", string returnAction = "Index")
        {
            ViewBag.ReturnController = returnController;
            ViewBag.ReturnAction = returnAction;
            return View();
        }

        [Authorize(Roles = "Administrator")]
        [HttpPost]
        public async Task<IActionResult> Assign(string userName, string roleName, string returnController = "Admin", string returnAction = "Index")
        {
            var user = await _userManager.FindByNameAsync(userName);
            var roleExists = await _roleManager.RoleExistsAsync(roleName); //существует ли указанная роль

            if (user != null && roleExists) //всё есть
            {
                var result = await _userManager.AddToRoleAsync(user, roleName); //добавляет пользователя в указанную роль

                if (result.Succeeded)
                {
                    return RedirectToAction(returnAction, returnController);
                }
                else
                {
                    foreach (var error in result.Errors)
                    {
                        ModelState.AddModelError("", error.Description);
                    }
                    ViewBag.ReturnController = returnController;
                    ViewBag.ReturnAction = returnAction;
                    return View();
                }
            }
            else //пользователь и роль не найдены
            {
                ModelState.AddModelError("", "User or Role not found.");
                ViewBag.ReturnController = returnController;
                ViewBag.ReturnAction = returnAction;
                return View();
            }
        }


        [Authorize(Roles = "Administrator")]
        [HttpGet] //создание роли
        public IActionResult CreateRole(string returnController = "Admin", string returnAction = "Index")
        {
            ViewBag.ReturnController = returnController;
            ViewBag.ReturnAction = returnAction;
            return View();
        }


        [Authorize(Roles = "Administrator")]
        [HttpPost]
        public async Task<IActionResult> CreateRole(string roleName, string returnController = "Admin", string returnAction = "Index")
        {
            var roleExists = await _roleManager.RoleExistsAsync(roleName); //есть ли уже такая роль

            if (!roleExists) //нет
            {
                var result = await _roleManager.CreateAsync(new IdentityRole(roleName)); //асинхронное создание

                if (result.Succeeded)
                {
                    return RedirectToAction(returnAction, returnController);
                }
                else
                {
                    foreach (var error in result.Errors)
                    {
                        ModelState.AddModelError("", error.Description);
                    }
                    ViewBag.ReturnController = returnController;
                    ViewBag.ReturnAction = returnAction;
                    return View();
                }
            }
            else //роль уже есть
            {
                ModelState.AddModelError("", "Role already exists.");
                ViewBag.ReturnController = returnController;
                ViewBag.ReturnAction = returnAction;
                return View();
            }
        }

        [Authorize(Roles = "Administrator")]
        [HttpGet]
        public IActionResult DeleteRole(string returnController = "Admin", string returnAction = "Index")
        {
            ViewBag.ReturnController = returnController;
            ViewBag.ReturnAction = returnAction;
            return View();
        }

        [Authorize(Roles = "Administrator")]
        [HttpPost]
        public async Task<IActionResult> DeleteRole(string roleName, string returnController = "Admin", string returnAction = "Index")
        {
            var role = await _roleManager.FindByNameAsync(roleName);

            if (role != null)
            {
                var result = await _roleManager.DeleteAsync(role);

                if (result.Succeeded)
                {
                    return RedirectToAction(returnAction, returnController);
                }
                else
                {
                    foreach (var error in result.Errors)
                    {
                        ModelState.AddModelError("", error.Description);
                    }
                    ViewBag.ReturnController = returnController;
                    ViewBag.ReturnAction = returnAction;
                    return View();
                }
            }
            else
            {
                ModelState.AddModelError("", "Role not found.");
                ViewBag.ReturnController = returnController;
                ViewBag.ReturnAction = returnAction;
                return View();
            }
        }
    }
}