var builder = WebApplication.CreateBuilder(args); 
var app = builder.Build();

app.MapGet("/getSVA", (string ParamA, string ParamB) => $"GET-Http-XYZ:ParmA = {ParamA},ParmB = {ParamB}"); 



//задание 2
app.MapPost("/postSVA", (string ParamA, string ParamB) => $"POST-Http-XYZ:ParmA = {ParamA},ParmB = {ParamB}");


//задание 3
app.MapPut("/putSVA", (string ParamA, string ParamB) => $"PUT-Http-XYZ:ParmA = {ParamA},ParmB = {ParamB}");


//задание 4
app.MapPost("/getSum", (int ParamA, int ParamB) => ParamA+ParamB);


//задание 5
app.MapGet("/SVAmultiply", () =>
{
    string html = @"
                <html>
                <body>
                    <input type='number' id='x' placeholder='Enter X'>
                    <input type='number' id='y' placeholder='Enter Y'>
                    <button onclick='multiply()'>Multiply</button>
                    <p id='result'></p>
                    <script>
                        function multiply() {
                            var x = document.getElementById('x').value;
                            var y = document.getElementById('y').value;
                            var xhr = new XMLHttpRequest(); 
                            xhr.open('POST', '/SVAmultiply', true);
                            xhr.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
                            xhr.onreadystatechange = function () {
                                if (xhr.status == 200) {
                                    document.getElementById('result').innerText = xhr.responseText;
                                }
                            };
                            xhr.send('x=' + x + '&y=' + y);
                        }
                    </script>
                </body>
                </html>";
    return Results.Text(html, "text/html");
});

app.MapPost("/SVAmultiply", async (HttpRequest request) =>
{
    var form = await request.ReadFormAsync();
    string? X = form["x"];
    string? Y = form["y"];

    if (int.TryParse(X, out int xValue) && int.TryParse(Y, out int yValue))
    {
        int product = xValue * yValue;
        return Results.Text($"Result: {product}", "text/plain");
    }
    else
    {
        return Results.Text("Invalid input. Please enter valid integers.", "text/plain");
    }
});


//задание 6
app.MapGet("/SVAmultiplyform", () =>
{
    string html = @"
                <html>
                <body>
                    <form action='/SVAmultiplyform' method='post'>
                        <input type='number' name='x' placeholder='Enter X'>
                        <input type='number' name='y' placeholder='Enter Y'>
                        <button type='submit'>Multiply</button>
                    </form>
                </body>
                </html>";
    return Results.Text(html, "text/html");
});

app.MapPost("/SVAmultiplyform", async (HttpRequest request) =>
{
    var form = await request.ReadFormAsync();
    string? X = form["x"];
    string? Y = form["y"];

    if (int.TryParse(X, out int xValue) && int.TryParse(Y, out int yValue))
    {
        int product = xValue * yValue;
        return Results.Text($"Result: {product}", "text/plain");
    }
    else
    {
        return Results.Text("Invalid input. Please enter valid integers.", "text/plain");
    }
});



app.Run();
