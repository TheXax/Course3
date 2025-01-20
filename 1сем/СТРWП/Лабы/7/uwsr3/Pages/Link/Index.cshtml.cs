using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authentication;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.EntityFrameworkCore;
using UWSR.Data;
using UWSR.Models;
using UWSR.Utils;

namespace UWSR.Pages.Lnk
{
    public class IndexModel : PageModel
    {
        private readonly UWSR.Data.AppDbContext _context;
        [BindProperty] //автоматически связывать данные из формы с этими свойствами
        public string LinksFindText { get; set; }
        [BindProperty]
        public Link CreateLink { get; set; } = default!;
        [BindProperty]
        public Link EditLink { get; set; } = default!;

        public IndexModel(AppDbContext context)
        {
            _context = context;
        }

        public IList<Link> Link { get;set; } = default!;
        public IList<Link> FindLinks { get; set; } = default!; //ссылки, соответствующие поиску

       

        public async Task<IActionResult> CheckSecretWord(string secretWord)
        {
            if (_context.Links != null)
            {
                Link = await _context.Links.ToListAsync();
                FindLinks = Link;
            }

            if (secretWord == "VerySecretPassword")
            {
                HttpContext.Session.Set("isAdmin", Encoding.UTF8.GetBytes("true"));
                ViewData["Message"] = "Введено секретное слово";
            }

            return Page();
        }

public async Task<IActionResult> GetFilterLinks()
    {
        if (!string.IsNullOrWhiteSpace(LinksFindText))
        {
            var searchWords = LinksFindText.Split(new[] { ' ', ',' }, StringSplitOptions.RemoveEmptyEntries); //разделение текста поиска

            IQueryable<Link> query = _context.Links; //запрос на получение всех ссылок из БД

            if (searchWords.Length > 0)
            {
                // Начинаем с выражения, которое всегда возвращает false
                Expression<Func<Link, bool>> predicate = l => false;

                foreach (var word in searchWords)
                {
                    string tempWord = word;
                                            // Создаем новое выражение для каждого слова
                    Expression<Func<Link, bool>> expr = l => EF.Functions.Like(l.Description, $"%{tempWord}%");
                    // Объединяем с существующим выражением с помощью OrElse
                    predicate = CombineOr(predicate, expr);
                }

                query = query.Where(predicate); //применение фильтрации
            }

            FindLinks = await query.ToListAsync();
        }
        else
        {
            FindLinks = await _context.Links.ToListAsync();
        }

        return Page();
    }

    // Вспомогательный метод для объединения двух выражений с помощью OrElse
    private Expression<Func<T, bool>> CombineOr<T>(
        Expression<Func<T, bool>> expr1,
        Expression<Func<T, bool>> expr2)
    {
        var parameter = Expression.Parameter(typeof(T));

        var leftVisitor = new ReplaceParameterVisitor(expr1.Parameters[0], parameter);
        var left = leftVisitor.Visit(expr1.Body);

        var rightVisitor = new ReplaceParameterVisitor(expr2.Parameters[0], parameter);
        var right = rightVisitor.Visit(expr2.Body);

        var body = Expression.OrElse(left, right);

        return Expression.Lambda<Func<T, bool>>(body, parameter);
    }

    private class ReplaceParameterVisitor : ExpressionVisitor
    {
        private readonly ParameterExpression _oldParameter;
        private readonly ParameterExpression _newParameter;

        public ReplaceParameterVisitor(ParameterExpression oldParameter, ParameterExpression newParameter)
        {
            _oldParameter = oldParameter;
            _newParameter = newParameter;
        }

        protected override Expression VisitParameter(ParameterExpression node)
        {
            return node == _oldParameter ? _newParameter : base.VisitParameter(node);
        }
    }

        //выход из системы
    public async Task<IActionResult> OnPostLogout()
        {
            if (_context.Links != null)
            {
                Link = await _context.Links.ToListAsync();
                FindLinks = Link;
            }
            ViewData["Message"] = "Вы вошли в режим клиента";
            int[] myArray = {-1};
            HttpContext.Session.Set("MyArray", myArray);
            HttpContext.Session.Set("NewMessage", Encoding.UTF8.GetBytes("true"));
            HttpContext.Session.Set("isAdmin", Encoding.UTF8.GetBytes("false"));
            return Page();
        }

        //новая ссылка
        public async Task<IActionResult> CreateLinkForm()
        {
            CreateLink.Plus = 0;
            CreateLink.Minus = 0;
            if (_context.Links == null || CreateLink == null)
            {
                Link = await _context.Links.ToListAsync();
                FindLinks = Link;
                return Page();
            }

            _context.Links.Add(CreateLink);
            await _context.SaveChangesAsync();
            Link = await _context.Links.ToListAsync();
            FindLinks = Link;
            return Page();
        }

        //удаление ссылки
        public async Task<IActionResult> DeleteLink(int linkId)
        {
            var link = await _context.Links.FindAsync(linkId);
            if (link != null)
            {
                _context.Links.Remove(link);
                await _context.SaveChangesAsync();
            }
            Link = await _context.Links.ToListAsync();
            FindLinks = Link;
            return Page();
        }

        //редактирование ссылки
        public async Task<IActionResult> EditLinkForm(int linkId)
        {
            var link = await _context.Links.FindAsync(linkId);

            if (link != null)
            {
                link.Url = EditLink.Url;
                link.Description = EditLink.Description;
                _context.Attach(link).State = EntityState.Modified;
                await _context.SaveChangesAsync();
            }
            Link = await _context.Links.ToListAsync();
            FindLinks = Link;
            return Page();
        }
        public async Task<IActionResult> OnPostAsync(string handler, string secretWord, int linkId)
        {
            switch (handler)
            {
                case "CheckSecretWord":
                    return await CheckSecretWord(secretWord);
                case "GetFilterLinks":
                    return await GetFilterLinks();
                case "CreateLink":
                    return await CreateLinkForm();
                case "DeleteLink":
                    return await DeleteLink(linkId);
                case "EditLink":
                    return await EditLinkForm(linkId);
                default:
                    return RedirectToPage("./Index");
            }
        }


        public async Task<IActionResult> OnGetAsync()
        {
            int[] retrievedArray = HttpContext.Session.Get<int[]>("MyArray");
            if(retrievedArray == null)
            {
                int[] myArray = { };
                HttpContext.Session.Set("MyArray", myArray);
            }
            if (_context.Links != null)
            {
                Link = await _context.Links.ToListAsync();
                FindLinks = Link;
            }

            return Page();
        }
    }
}
