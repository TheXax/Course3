using lab2b;
using lab2b.Routes;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddControllersWithViews();

var app = builder.Build();

/*if (!app.Environment.IsDevelopment())
{
    app.UseExceptionHandler("/Home/Error");
    app.UseHsts();
}*/

//app.UseHttpsRedirection(); //для перенаправления на другой ресурс
app.UseStaticFiles();

app.ConfigureRoutes(); //связывает URL-адреса с конкретными контроллерами и действиями

app.UseRouting();

//app.UseAuthorization();



app.Run();

/*
http://localhost:5109/MResearch/M01
http://localhost:5109/V2/MResearch/M02
http://localhost:5109/V3
http://localhost:5109/pimpim
 */