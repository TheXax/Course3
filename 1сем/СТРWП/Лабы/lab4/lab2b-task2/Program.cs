using Microsoft.AspNetCore.Routing.Constraints;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddControllersWithViews();

var app = builder.Build();

//app.UseHttpsRedirection();
app.UseStaticFiles();

app.UseRouting();

//app.UseAuthorization();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");

app.Run();
/*
/it/n/5/pimpim

/it/b/true/pimpim
/it/b/false/pimpim

/it/f/3.14/abc
/it/f/3.4/pimpim

/it/pimpim/120
/it/ssjjitt@gmail.com
*/
