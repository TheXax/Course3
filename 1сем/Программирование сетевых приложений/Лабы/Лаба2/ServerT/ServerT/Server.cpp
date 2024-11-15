#include <iostream>
#include <winsock2.h> //Заголовок WS2_32.dll
#include <ws2tcpip.h> // Для inet_ntoa
#include <string>

#pragma comment(lib, "WS2_32.lib") // Подключение библиотеки WS2_32

using namespace std;

string GetErrorMsgText(int code);
string SetErrorMsgText(string msgText, int code);

int main() {
    setlocale(LC_ALL, "rus");

    try {
        WSADATA wsaData; //шаблон структуры

        // Инициализация библиотеки Winsock
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw SetErrorMsgText("WSAStartup:", WSAGetLastError());
        }

        SOCKET serverSocket; // сервенрный сокет, дескриптер сокета

        // Создание сокета
        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (serverSocket == INVALID_SOCKET) {
            throw SetErrorMsgText("socket:", WSAGetLastError());
        }

        // Настройка адреса
        SOCKADDR_IN serv; //структура для хранения информации о сервере
        serv.sin_family = AF_INET; //используется IP-адресация
        serv.sin_port = htons(2000); // Порт 2000
        serv.sin_addr.s_addr = INADDR_ANY; // Принимаем соединения на любом IP

        // Привязка сокета
        if (bind(serverSocket, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR) {
            throw SetErrorMsgText("bind:", WSAGetLastError());
        }

        // Перевод сокета в режим прослушивания
        if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
            throw SetErrorMsgText("listen:", WSAGetLastError());
        }

        cout << "Сервер начал прослушку на порту 2000..." << endl;

        // Принятие входящего соединения
        SOCKADDR_IN clientAddr; //для обмена данными  с клиентом
        int clientAddrSize = sizeof(clientAddr); //размер SOCKADDR_IN
        //функция accept создаёт канал на стороне сервероа и создаёт сокет для обмена данными по этому каналу
        SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == INVALID_SOCKET) {
            throw SetErrorMsgText("accept:", WSAGetLastError());
        }

        cout << "Клиент подключен: " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << endl;//

        char buffer[256];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            cout << "Сообщение от клиента: " << buffer << endl;
        }

        // Закрытие сокетов
        closesocket(clientSocket);
        closesocket(serverSocket);

        // Завершение работы Winsock
        WSACleanup();
    }
    catch (string errorMsgText) {
        cout << "Ошибка: " << errorMsgText << endl;
    }

    return 0;
}

//функция позволяет получить сообщение об ошибке
string GetErrorMsgText(int code) {
    string msgText;
    switch (code) {
    case WSAEINTR: msgText = "Работа функции прервана"; break;
    case WSAEACCES: msgText = "Разрешение отвергнуто"; break;
    case WSAEFAULT: msgText = "Ошибочный адрес"; break;
    case WSASYSCALLFAILURE: msgText = "Аварийное завершение системного вызова"; break;
    default: msgText = "Неизвестная ошибка"; break;
    }
    //TODO: добавить коды
    return msgText;
}
//функция возвращает сообщение ошибки
string SetErrorMsgText(string msgText, int code) {
    return msgText + GetErrorMsgText(code);
}