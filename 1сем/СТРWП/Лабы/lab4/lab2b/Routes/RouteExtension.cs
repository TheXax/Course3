namespace lab2b.Routes;

    public static class RouteExtensions
    {
        public static void ConfigureRoutes(this WebApplication app)
        {
            
            app.MapControllerRoute(
                name: "M01",
                pattern: "{controller=TMResearch}/{action=M01}/{id?}");

            app.MapControllerRoute(
                name: "MO2",
                pattern: "V2/{controller=TMResearch}/{action=M02}/{id?}",
                constraints: new { action = "M01|M02" });

            app.MapControllerRoute(
                name: "M03",
                pattern: "V3/{controller=TMResearch}/{id?}/{action=M03}",
                constraints: new { action = "M01|M02|M03" });

            app.MapControllerRoute(
                name: "MXX",
                pattern: "{*url}",
                defaults: new { controller = "TMResearch", action = "MXX" });
        } 
    }


//строка из букв, что объединили в паттерне, отображение метода (delete, get)