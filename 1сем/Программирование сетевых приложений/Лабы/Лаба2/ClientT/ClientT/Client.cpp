#include <iostream>
#include <winsock2.h> //заголовок WS2_32.dll
#include <ws2tcpip.h> // Для inet_addr
#include <string>

#pragma comment(lib, "WS2_32.lib") // Подключение библиотеки WS2_32

using namespace std;

string GetErrorMsgText(int code);
string SetErrorMsgText(string msgText, int code);

int main() {
    setlocale(LC_ALL, "rus");

    try {
        WSADATA wsaData;

        // Инициализация библиотеки Winsock
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw SetErrorMsgText("WSAStartup:", WSAGetLastError());
        }

        SOCKET clientSocket; //клиентский сокет

        // Создание сокета
        clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
        if (clientSocket == INVALID_SOCKET) {
            throw SetErrorMsgText("socket:", WSAGetLastError());
        }

        // Настройка адреса сервера
        SOCKADDR_IN serverAddr; //хранение информации о сервере
        serverAddr.sin_family = AF_INET; //используетяся IP-адресация
        serverAddr.sin_port = htons(2000); // TCP-порт 2000
        inet_pton(AF_INET, "127.0.0.1", &(serverAddr.sin_addr)); // адрес сервера
       // serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Локальный адрес

        // Подключение к серверу
        if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            throw SetErrorMsgText("connect:", WSAGetLastError());
        }


        //---------Одно смс----------
        //cout << "Подключение к серверу успешно!" << endl;

        //// После успешного подключения клиент отправляет смс
        //const char* message = "Hello from Client";
        //send(clientSocket, message, strlen(message) + 1, 0);
        //cout << "Сообщение отправлено: " << message << endl;

        //// Закрытие сокета
        //closesocket(clientSocket);

        //// Завершение работы Winsock
        //WSACleanup();



        //------------Задание кол-ва смс---------------
        char ibuf[24],
            obuf[24] = "Hello from Client";
        int count;
        cout << "Enter number of messages:\n";
        cin >> count;

        int time = clock();
        for (int i = 0; i < count; i++)
        {
            if (SOCKET_ERROR == send(clientSocket, obuf, sizeof(obuf), NULL))
                cout << "send:" << GetLastError() << endl;;
            if (SOCKET_ERROR == recv(clientSocket, ibuf, sizeof(ibuf), NULL))
                cout << "recv:" << GetLastError() << endl;
            cout << ibuf << " " << (i + 1) << endl;
        }
        cout << "\nProgram was running for " << time << " ticks or " << ((float)time) / CLOCKS_PER_SEC << " seconds.\n";

        if (closesocket(clientSocket) == SOCKET_ERROR)
            throw  SetErrorMsgText("closesocket:", WSAGetLastError());
        if (WSACleanup() == SOCKET_ERROR)
            throw SetErrorMsgText("Cleanup: ", WSAGetLastError());

    }
    catch (string errorMsgText) {
        cout << "Ошибка: " << errorMsgText << endl;
    }

    return 0;
}

//функция позволяет получить сообщение ошиибки
string GetErrorMsgText(int code) {
    string msgText;
    switch (code) {
    case WSAEINTR: msgText = "Работа функции прервана"; break;
    case WSAEACCES: msgText = "Разрешение отвергнуто"; break;
    case WSAEFAULT: msgText = "Ошибочный адрес"; break;
    case WSASYSCALLFAILURE: msgText = "Аварийное завершение системного вызова"; break;
    case WSAENETUNREACH: msgText = "Сеть недоступна"; break;
    case WSAETIMEDOUT: msgText = "Время ожидания соединения истекло"; break;
    default: msgText = "Неизвестная ошибка"; break;
    }
    //TODO: добавить коды
    return msgText;
}

//функция возвращает сообщение ошибки
string SetErrorMsgText(string msgText, int code) {
    return msgText + GetErrorMsgText(code);
}