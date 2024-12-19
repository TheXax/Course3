internal class Program
{
    private static void Main(string[] args)
    {
        var builder = WebApplication.CreateBuilder(args);
        builder.Services.AddControllersWithViews(); //контролле с представлением
        var app = builder.Build();

        app.UseStaticFiles();

        app.MapGet("/", async context =>
        {
            context.Response.Redirect("/Index.html"); // Перенаправляем на Index.html
        });

        app.MapControllerRoute( //то, как вызывается метод из контроллера
            name: "default",
            pattern: "{controller=Home}/{action=Index}");

        app.Run();
    }
}