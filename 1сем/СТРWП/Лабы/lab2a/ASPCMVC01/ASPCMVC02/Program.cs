internal class Program
{
    private static void Main(string[] args)
    {
        var builder = WebApplication.CreateBuilder(args);
        builder.Services.AddControllersWithViews(); //��������� � ��������������
        var app = builder.Build();

        app.UseStaticFiles();

        app.MapGet("/", async context =>
        {
            context.Response.Redirect("/Index.html"); // �������������� �� Index.html
        });

        app.MapControllerRoute( //��, ��� ���������� ����� �� �����������
            name: "default",
            pattern: "{controller=Home}/{action=Index}");

        app.Run();
    }
}