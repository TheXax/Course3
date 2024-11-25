using System.Net.WebSockets;
using System.Text;

var builder = WebApplication.CreateBuilder(args);
var app = builder.Build();

app.UseDefaultFiles(); //��������� ���������� ��� ������ � �������������� ������ �� ��������� (html)
app.UseStaticFiles(); //����� ������������ ����������� ����� � ������� (html, css, js �� wwwroot)


var webSocketOptions = new WebSocketOptions //��� �������� WebSocket
{
    KeepAliveInterval = TimeSpan.FromSeconds(120), //����� ��������� 120�; �������� ��� ����������� �������� ����������� ��������� ��� ����������� ���������� ��������
};
app.UseWebSockets(webSocketOptions); //��������� middleware ��� ��������� webSocket-���������� � �����������

 //��������� ����������� ��� URL, �������������� ��� ����������
app.Map("/ws", async context =>
{
    if (context.WebSockets.IsWebSocketRequest)
    {
        using var webSocket = await context.WebSockets.AcceptWebSocketAsync(); //��������� WebSocket-������ � ������ ��������� ��� ��������������
        await Echo(webSocket); //����� ���������� ������ ��� ��������� ���
    }
    else
    {
        context.Response.StatusCode = 400;
    }
});

app.Run();

async Task Echo(WebSocket webSocket)
{
    var buffer = new byte[1024 * 4]; //��� �������� ���� �� WebSocket'�
    bool sendMessages = false; //���� ���������� ������������, �� ��������������� ��� true; ���������� ��������� ��� �������
    CancellationTokenSource cts = new CancellationTokenSource(); //�����, ����������� �����; CancellationTokenSource - ����� ������, �������������� ��� ���������� ������������ ��������


    var sendTask = Task.Run(async () => //���� ����� ������
    {
        while (!cts.Token.IsCancellationRequested) //�����������, ���� �� ������������� ������
        {
            if (sendMessages) //���� true, �� ��� ������������
            {
                var message = DateTime.Now.ToString("HH:mm:ss");
                var msgBytes = Encoding.UTF8.GetBytes(message); //����������� � ������ ������; ��� ������ � WebSocket'�� ����������� ��� - �����
                await webSocket.SendAsync(new ArraySegment<byte>(msgBytes), WebSocketMessageType.Text, true, CancellationToken.None); //�������� �������; ArraySegment ��������� ���������� ������ ����� �������, ���� ��� ����������; CancellationToken.None - ��������, ������� ���������, ����� �� �������� ��������. � ������ ������ ���
            }
            await Task.Delay(2000); //�������� ����� ��� 2�
        }
    });

    try
    {
        while (webSocket.State == WebSocketState.Open) //���� ����� ������
        {
            var result = await webSocket.ReceiveAsync(new ArraySegment<byte>(buffer), CancellationToken.None); //��� �������� ������, ���������� �� �������
            if (result.MessageType == WebSocketMessageType.Text) //�������� �� ���������� ��� ���������
            {
                var receivedMessage = Encoding.UTF8.GetString(buffer, 0, result.Count); //�������������� ����������� ������� ������ � ������
                if (receivedMessage == "start")//���� � html
                {
                    sendMessages = true; //��������� ������������
                }
                else if (receivedMessage == "stop")
                {
                    sendMessages = false;
                }
            }
            else if (result.MessageType == WebSocketMessageType.Close)
            {
                await webSocket.CloseAsync(WebSocketCloseStatus.NormalClosure, "Closing", CancellationToken.None); //�������� WebSocket-����������
            }
        }
    }
    catch (Exception ex)
    {
        Console.WriteLine($"WebSocket error: {ex.Message}");
    }
    finally
    {
        cts.Cancel(); //������ �� ������ �������� ���
        await sendTask; //������� ���������� ������ �������� ���
    }
}
