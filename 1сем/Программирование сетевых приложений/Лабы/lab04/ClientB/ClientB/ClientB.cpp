#include <iostream>
#include <cstring>
#include "Winsock2.h" // Заголовок WS2_32.dll

#pragma comment(lib, "WS2_32.lib") // экспорт WS2_32.dll
#pragma warning(suppress : 4996)
#pragma warning(disable : 4996)

using namespace std;

string GetErrorMsgText(int code);
string SetErrorMsgText(string msgText, int code);

SOCKET clientSocket;

bool GetServers(char* call, short port, sockaddr* from, int* flen) {
    memset(from, 0, sizeof(sockaddr)); // Исправлено

    if ((clientSocket = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET) {
        throw SetErrorMsgText("socket:", WSAGetLastError());
    }

    // Устанавливаем опцию сокета для разрешения широковещательной рассылки
    int optval = 1;
    if (setsockopt(clientSocket, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR) {
        throw SetErrorMsgText("opt:", WSAGetLastError());
    }

    // структура для указания адреса
    SOCKADDR_IN all;
    all.sin_family = AF_INET;
    all.sin_port = htons(port);
    all.sin_addr.s_addr = INADDR_BROADCAST;

    // отправка сообщения на сервер
    if ((sendto(clientSocket, call, strlen(call) + 1, NULL, (sockaddr*)&all, sizeof(all))) == SOCKET_ERROR) {
        throw SetErrorMsgText("sendto:", WSAGetLastError());
    }

    // ожидание ответа от серверов
    char nameServer[50];
    fd_set readfds;
    struct timeval timeout;
    int responses = 0;

    while (responses < 5) { // Максимум 5 ответов
        FD_ZERO(&readfds);
        FD_SET(clientSocket, &readfds);

        timeout.tv_sec = 2; // 2 секунды ожидания
        timeout.tv_usec = 0;

        int result = select(clientSocket + 1, &readfds, NULL, NULL, &timeout);
        if (result > 0) {
            if ((recvfrom(clientSocket, nameServer, sizeof(nameServer), NULL, from, flen)) == SOCKET_ERROR) {
                throw SetErrorMsgText("recv:", WSAGetLastError());
            }

            // вывод информации о сервере
            SOCKADDR_IN* addr = (SOCKADDR_IN*)from;
            std::cout << std::endl << "Порт сервера: " << ntohs(addr->sin_port);
            std::cout << std::endl << "IP-адрес сервера: " << inet_ntoa(addr->sin_addr);

            // проверка имени сервера
            if (!strcmp(nameServer, call)) {
                std::cout << std::endl << "Сервер с таким именем найден: " << nameServer << std::endl;
                responses++;
            }
            else {
                std::cout << std::endl << "Сервер с таким именем не найден.";
            }
        }
        else if (result == 0) {
            // Время ожидания истекло
            break;
        }
    }

    return responses > 0; // Вернуть true, если были ответы
}

int main() {
    setlocale(LC_ALL, "rus");
    try {
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0) {
            throw SetErrorMsgText("Startup:", WSAGetLastError());
        }

        char call[] = "MyServer";

        SOCKADDR_IN clnt;
        int lc = sizeof(clnt);

        while (true) {
            if (GetServers(call, 2000, (sockaddr*)&clnt, &lc)) {
                std::cout << "IP сервера: " << inet_ntoa(clnt.sin_addr) << std::endl;
                std::cout << "Порт сервера: " << ntohs(clnt.sin_port) << std::endl;
            }
            else {
                std::cout << "Сервера не найдены." << std::endl;
            }
        }

        if (closesocket(clientSocket) == SOCKET_ERROR) {
            throw SetErrorMsgText("closesocket:", WSAGetLastError());
        }
        if (WSACleanup() == SOCKET_ERROR) {
            throw SetErrorMsgText("Cleanup:", WSAGetLastError());
        }

    }
    catch (string errorMsgText) {
        cout << endl << "WSAGetLastError: " << errorMsgText;
    }
}

string GetErrorMsgText(int code) {
    switch (code) {
    case WSAEINTR: return "WSAEINTR: Работа функции прервана ";
    case WSAEACCES: return "WSAEACCES: Разрешение отвергнуто";
    case WSAEFAULT: return "WSAEFAULT: Ошибочный адрес";
    case WSAEINVAL: return "WSAEINVAL: Ошибка в аргументе";
    case WSAEMFILE: return "WSAEMFILE: Слишком много файлов открыто";
    case WSAEWOULDBLOCK: return "WSAEWOULDBLOCK: Ресурс временно недоступен";
    case WSAEINPROGRESS: return "WSAEINPROGRESS: Операция в процессе развития";
    case WSAEALREADY: return "WSAEALREADY: Операция уже выполняется";
    case WSAENOTSOCK: return "WSAENOTSOCK: Сокет задан неправильно";
    case WSAEDESTADDRREQ: return "WSAEDESTADDRREQ: Требуется адрес расположения";
    case WSAEMSGSIZE: return "WSAEMSGSIZE: Сообщение слишком длинное";
    case WSAEPROTOTYPE: return "WSAEPROTOTYPE: Неправильный тип протокола для сокета";
    case WSAENOPROTOOPT: return "WSAENOPROTOOPT: Ошибка в опции протокола";
    case WSAEPROTONOSUPPORT: return "WSAEPROTONOSUPPORT: Протокол не поддерживается";
    case WSAESOCKTNOSUPPORT: return "WSAESOCKTNOSUPPORT: Тип сокета не поддерживается";
    case WSAEOPNOTSUPP: return "WSAEOPNOTSUPP: Операция не поддерживается";
    case WSAEPFNOSUPPORT: return "WSAEPFNOSUPPORT: Тип протоколов не поддерживается";
    case WSAEAFNOSUPPORT: return "WSAEAFNOSUPPORT: Тип адресов не поддерживается протоколом";
    case WSAEADDRINUSE: return "WSAEADDRINUSE: Адрес уже используется";
    case WSAEADDRNOTAVAIL: return "WSAEADDRNOTAVAIL: Запрошенный адрес не может быть использован";
    case WSAENETDOWN: return "WSAENETDOWN: Сеть отключена";
    case WSAENETUNREACH: return "WSAENETUNREACH: Сеть не достижима";
    case WSAENETRESET: return "WSAENETRESET: Сеть разорвала соединение";
    case WSAECONNABORTED: return "WSAECONNABORTED: Программный отказ связи";
    case WSAECONNRESET: return "WSAECONNRESET: Связь восстановлена";
    case WSAENOBUFS: return "WSAENOBUFS: Не хватает памяти для буферов";
    case WSAEISCONN: return "WSAEISCONN: Сокет уже подключен";
    case WSAENOTCONN: return "WSAENOTCONN: Сокет не подключен";
    case WSAESHUTDOWN: return "WSAESHUTDOWN: Нельзя выполнить send : сокет завершил работу";
    case WSAETIMEDOUT: return "WSAETIMEDOUT: Закончился отведенный интервал времени";
    case WSAECONNREFUSED: return "WSAECONNREFUSED: Соединение отклонено";
    case WSAEHOSTDOWN: return "WSAEHOSTDOWN: Хост в неработоспособном состоянии";
    case WSAEHOSTUNREACH: return "WSAEHOSTUNREACH: Нет маршрута для хоста";
    case WSAEPROCLIM: return "WSAEPROCLIM: Слишком много процессов";
    case WSASYSNOTREADY: return "WSASYSNOTREADY: Сеть не доступна";
    case WSAVERNOTSUPPORTED: return "WSAVERNOTSUPPORTED: Данная версия недоступна";
    case WSANOTINITIALISED: return "WSANOTINITIALISED: Не выполнена инициализация WS2_32.DLL";
    case WSAEDISCON: return "WSAEDISCON: Выполняется отключение";
    case WSATYPE_NOT_FOUND: return "WSATYPE_NOT_FOUND: Класс не найден";
    case WSAHOST_NOT_FOUND: return "WSAHOST_NOT_FOUND: Хост не найден";
    case WSATRY_AGAIN: return "WSATRY_AGAIN: Неавторизированный хост не найден";
    case WSANO_RECOVERY: return "WSANO_RECOVERY: Неопределенная ошибка";
    case WSANO_DATA: return "WSANO_DATA: Нет записи запрошенного типа";
    case WSA_INVALID_HANDLE: return "WSA_INVALID_HANDLE: Указанный дескриптор события с ошибкой";
    case WSA_INVALID_PARAMETER: return "WSA_INVALID_PARAMETER: Один или более параметров с ошибкой";
    case WSA_IO_INCOMPLETE: return "WSA_IO_INCOMPLETE: Объект ввода - вывода не в сигнальном состоянии";
    case WSA_IO_PENDING: return "WSA_IO_PENDING: Операция завершится позже";
    case WSA_NOT_ENOUGH_MEMORY: return "WSA_NOT_ENOUGH_MEMORY: Не достаточно памяти";
    case WSA_OPERATION_ABORTED: return "WSA_OPERATION_ABORTED: Операция отвергнута";
    case WSASYSCALLFAILURE: return "WSASYSCALLFAILURE: Аварийное завершение системного вызова";
    default: return "**ERROR**";
    };
}

string SetErrorMsgText(string msgText, int code) {
    return msgText + GetErrorMsgText(code);
}