using ASPCMVC08.Data;
using Microsoft.AspNetCore.Identity; //��������� ��� �����������
using Microsoft.EntityFrameworkCore; //��� ������ � ��


var builder = WebApplication.CreateBuilder(args);


// ��������� �������� ������
builder.Services.AddDbContext<ApplicationDbContext>(options => //��������� �������� ���� ������ (ApplicationDbContext) � ��������� ������������
    options.UseSqlServer(builder.Configuration.GetConnectionString("DefaultConnection"))); //���������, ��� �������� ����� ������������ SQL Server � �������� ���� ������

// ��������� Identity
builder.Services.AddIdentity<IdentityUser, IdentityRole>() //�������������� � �����������, ��������� ������ IdentityUser � IdentityRole
    .AddEntityFrameworkStores<ApplicationDbContext>(); //���������, ��� Identity ����� ������������ Entity Framework ��� �������� ������������� � ����� � ���� ������, ������������ � ApplicationDbContext

builder.Services.AddControllersWithViews();

var app = builder.Build();

//������������� ��
//������� ��������� (scope) ������������ ��� ���������� �������� ����� �������� � �� �������������.
using (var scope = app.Services.CreateScope()) //�������� ������� ��������� ��� ��������� ��������
{
    var services = scope.ServiceProvider; //�������� ��������� �����
    await DbInitializer.InitializeAsync(services); //����� ������ ������������� ��
}

//��� middleware �������������� � �����������
app.UseAuthentication();
app.UseAuthorization();

app.MapControllerRoute(
    name: "default",
    pattern: "{controller=Home}/{action=Index}/{id?}");

app.Run();