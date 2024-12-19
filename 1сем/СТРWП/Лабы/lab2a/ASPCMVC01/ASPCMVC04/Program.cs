internal class Program
{
    private static void Main(string[] args)
    {
        var builder = WebApplication.CreateBuilder(args);
        builder.Services.AddControllersWithViews();
        var app = builder.Build();

        app.MapControllerRoute(
            name: "status",
            pattern: "{controller=Status}/{action=S200}");

        app.Run();
    }
}