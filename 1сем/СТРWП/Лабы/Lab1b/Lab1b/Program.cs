using System.Net.WebSockets;
using System.Text;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.UseDefaultFiles(); //настройка приложения для поиска и предоставления файлов по умолчанию (html)
app.UseStaticFiles(); //чтобы использовать статические файлы в проекте (html, css, js из wwwroot)


var webSocketOptions = new WebSocketOptions //для настроек WebSocket
{
    KeepAliveInterval = TimeSpan.FromSeconds(120), //время прослушки 120с; интервал для отправления сервером контрольных сообщений для поддержания соединения активным
};
app.UseWebSockets(webSocketOptions); //добавляет middleware для обработки webSocket-соединений с параметрами

 //настройка обработчика для URL, использующийся для соединений
app.Map("/ws", async context =>
{
    if (context.WebSockets.IsWebSocketRequest)
    {
        using var webSocket = await context.WebSockets.AcceptWebSocketAsync(); //принимает WebSocket-запрос и создаёт экземпляр для взаимодействия
        await Echo(webSocket); //вызов созданного метода для обработки смс
    }
    else
    {
        context.Response.StatusCode = 400;
    }
});

app.Run();

async Task Echo(WebSocket webSocket)
{
    var buffer = new byte[1024 * 4]; //для хранения инфы из WebSocket'а
    bool sendMessages = false; //если отправляем пользователю, то устанавливается как true; управление отправкой смс клиенту
    CancellationTokenSource cts = new CancellationTokenSource(); //класс, закрывающий сокет; CancellationTokenSource - токен отмены, использующийся для управления асинхронными задачами


    var sendTask = Task.Run(async () => //пока сокет открыт
    {
        while (!cts.Token.IsCancellationRequested) //выполняется, пока не запрашивается отмена
        {
            if (sendMessages) //если true, то смс отправляется
            {
                var message = DateTime.Now.ToString("HH:mm:ss");
                var msgBytes = Encoding.UTF8.GetBytes(message); //конвертация в массив байтов; для работы с WebSocket'ом необходимый тип - байты
                await webSocket.SendAsync(new ArraySegment<byte>(msgBytes), WebSocketMessageType.Text, true, CancellationToken.None); //отправка клиенту; ArraySegment позволяет передавать только часть массива, если это необходимо; CancellationToken.None - параметр, который указывает, будет ли операция отменена. В данном случае НЕТ
            }
            await Task.Delay(2000); //интервал между смс 2с
        }
    });

    try
    {
        while (webSocket.State == WebSocketState.Open) //пока сокет открыт
        {
            var result = await webSocket.ReceiveAsync(new ArraySegment<byte>(buffer), CancellationToken.None); //для хранения данных, полученных от клиента
            if (result.MessageType == WebSocketMessageType.Text) //является ли полученное смс текстовым
            {
                var receivedMessage = Encoding.UTF8.GetString(buffer, 0, result.Count); //преобразование полученного массива байтов в строку
                if (receivedMessage == "start")//пуск в html
                {
                    sendMessages = true; //сообщения отправляются
                }
                else if (receivedMessage == "stop")
                {
                    sendMessages = false;
                }
            }
            else if (result.MessageType == WebSocketMessageType.Close)
            {
                await webSocket.CloseAsync(WebSocketCloseStatus.NormalClosure, "Closing", CancellationToken.None); //закрытие WebSocket-соединения
            }
        }
    }
    catch (Exception ex)
    {
        Console.WriteLine($"WebSocket error: {ex.Message}");
    }
    finally
    {
        cts.Cancel(); //запрос на отмену отправки смс
        await sendTask; //ожидает завершения задачи отправки смс
    }
}
