﻿#include <iostream>
#include "Winsock2.h"			   // Заголовок WS2_32.dll

#pragma comment(lib, "WS2_32.lib") // экспорт WS2_32.dll
#pragma warning(suppress : 4996)
#pragma warning(disable : 4996)

using namespace std;

string GetErrorMsgText(int code);
string SetErrorMsgText(string msgText, int code);

SOCKET serverSocket;
char name[] = "Hello";
char checkServName[] = "CheckServ";
//char servAk[] = "Hello";

//получение запроса от клиента
bool GetRequestFromClient(char* name, short port, sockaddr* from, int* flen)
{
	//char nameServer[50];
	memset(from, 0, sizeof(flen));

	if ((serverSocket = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)//UDP сокет для IPv4
	{
		throw  SetErrorMsgText("socket:", WSAGetLastError());
	}

	SOCKADDR_IN serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(port);
	serv.sin_addr.s_addr = INADDR_ANY;

	//связать пар-ры сокета
	if (bind(serverSocket, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR)
	{
		throw  SetErrorMsgText("Походу такой сервер уже есть:", WSAGetLastError());
	}

	char* message = new char[strlen(name)]; //для хранения смс от клиента
	int buf = 0;

	SOCKADDR_IN client;
	int size = sizeof(client);
	while (strcmp(name, message))//выполняется, пока сообщение от клиента не совпадает с ожидаемым именем сервера
	{
		memset(&client, 0, size);
		buf = recvfrom(serverSocket, message, strlen(message), NULL, (sockaddr*)&client, &size);	//индик.режима маршрутизации
		char* addr = (char*)&client.sin_addr;//получение адреса клиента

		hostent* cl = gethostbyaddr(addr, 4, AF_INET);//инфа о хосте по IP
		cout << "\nClient name : " << cl->h_name << endl;
		switch (buf)
		{
		case SOCKET_ERROR:
			throw SetErrorMsgText("recvfrom:", WSAGetLastError());
			break;
		case WSAETIMEDOUT://истекло время ожиания
			return false;
		default:
			break;
		}
		message[buf] = 0x00;
	}
	//сохранение информации о клиенте
	*from = *((sockaddr*)&client);
	*flen = sizeof(client);
	return true;
}

bool PutAnswerToClient(const char* name, sockaddr* to, int* lto)
{
	if ((sendto(serverSocket, name, strlen(name) + 1, NULL, to, *lto)) == SOCKET_ERROR)
	{
		throw  SetErrorMsgText("send:", WSAGetLastError());
	}

	return true;
}

//проверка наличия других серверов
void CheckServer() {

	char checkServ[] = "CheckServ";

	int checkServer;
	if ((checkServer = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
		throw  SetErrorMsgText("socket:", WSAGetLastError());

	int optval = 1; //  для установки опции сокета		

	//широковещательная рассылка
	if (setsockopt(checkServer, SOL_SOCKET,		
		SO_BROADCAST,	//режим сокета для исп-ния широковещ.адреса
		(char*)&optval, 
		sizeof(int)) == SOCKET_ERROR)
	{
		throw  SetErrorMsgText("opt:", WSAGetLastError());
	}

	SOCKADDR_IN all;
	all.sin_family = AF_INET;
	all.sin_port = htons(2000);
	all.sin_addr.s_addr = INADDR_BROADCAST;

	if ((sendto(checkServer, checkServ, strlen(checkServ) + 1, NULL, (sockaddr*)&all, sizeof(all))) == SOCKET_ERROR)
		throw  SetErrorMsgText("sendto:", WSAGetLastError());

	if (closesocket(checkServer) == SOCKET_ERROR)
		throw  SetErrorMsgText("closesocket:", WSAGetLastError());
}

int main() {
	setlocale(LC_ALL, "rus");
	WSADATA wsaData;
	try {

		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)                   // инициализация библиотеки
			throw  SetErrorMsgText("Startup:", WSAGetLastError());

		CheckServer();

		char Sname[100];//для хранения имени сервера

		//получение имени текущего хоста
		if (gethostname(Sname, sizeof(Sname)) == SOCKET_ERROR)
			throw SetErrorMsgText("gethostname:", WSAGetLastError());

		cout << "Hello, I'm server. Мое имя - " << Sname << endl;

		while (true) {
			SOCKADDR_IN clnt;
			int lc = sizeof(clnt);

			if (GetRequestFromClient(name, 2000, (sockaddr*)&clnt, &lc))
			{
				if (PutAnswerToClient(name, (sockaddr*)&clnt, &lc))
					std::cout <<"Ответ отправлен"<< std::endl;
			}
			

			SOCKADDR_IN* addr = (SOCKADDR_IN*)&clnt;
			std::cout << std::endl << "Порт клиента: " << addr->sin_port;
			std::cout << std::endl << "IP-адрес клиента: " << inet_ntoa(addr->sin_addr);



			if (closesocket(serverSocket) == SOCKET_ERROR)							// закрыть сокет
				throw  SetErrorMsgText("closesocket:", WSAGetLastError());

		}


		if (WSACleanup() == SOCKET_ERROR)							    // завершить работу с библиотекой
			throw  SetErrorMsgText("Cleanup:", WSAGetLastError());

	}
	catch (string errorMsgText) {
		{ cout << endl << "WSAGetLastError: " << errorMsgText; }
	}
	system("pause");
	return 0;
}


string GetErrorMsgText(int code) // Функция позволяет получить сообщение ошибки
{
	switch (code)           
	{
	case WSAEINTR: return "WSAEINTR: Работа функции прервана ";
	case WSAEACCES: return "WSAEACCES: Разрешение отвергнуто";
	case WSAEFAULT:	return "WSAEFAULT: Ошибочный адрес";
	case WSAEINVAL:	return "WSAEINVAL: Ошибка в аргументе";
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
	case WSAEOPNOTSUPP:	return "WSAEOPNOTSUPP: Операция не поддерживается";
	case WSAEPFNOSUPPORT: return "WSAEPFNOSUPPORT: Тип протоколов не поддерживается";
	case WSAEAFNOSUPPORT: return "WSAEAFNOSUPPORT: Тип адресов не поддерживается протоколом";
	case WSAEADDRINUSE:	return "WSAEADDRINUSE: Адрес уже используется";
	case WSAEADDRNOTAVAIL: return "WSAEADDRNOTAVAIL: Запрошенный адрес не может быть использован";
	case WSAENETDOWN: return "WSAENETDOWN: Сеть отключена";
	case WSAENETUNREACH: return "WSAENETUNREACH: Сеть не достижима";
	case WSAENETRESET: return "WSAENETRESET: Сеть разорвала соединение";
	case WSAECONNABORTED: return "WSAECONNABORTED: Программный отказ связи";
	case WSAECONNRESET:	return "WSAECONNRESET: Связь восстановлена";
	case WSAENOBUFS: return "WSAENOBUFS: Не хватает памяти для буферов";
	case WSAEISCONN: return "WSAEISCONN: Сокет уже подключен";
	case WSAENOTCONN: return "WSAENOTCONN: Сокет не подключен";
	case WSAESHUTDOWN: return "WSAESHUTDOWN: Нельзя выполнить send : сокет завершил работу";
	case WSAETIMEDOUT: return "WSAETIMEDOUT: Закончился отведенный интервал  времени";
	case WSAECONNREFUSED: return "WSAECONNREFUSED: Соединение отклонено";
	case WSAEHOSTDOWN: return "WSAEHOSTDOWN: Хост в неработоспособном состоянии";
	case WSAEHOSTUNREACH: return "WSAEHOSTUNREACH: Нет маршрута для хоста";
	case WSAEPROCLIM: return "WSAEPROCLIM: Слишком много процессов";
	case WSASYSNOTREADY: return "WSASYSNOTREADY: Сеть не доступна";
	case WSAVERNOTSUPPORTED: return "WSAVERNOTSUPPORTED: Данная версия недоступна";
	case WSANOTINITIALISED:	return "WSANOTINITIALISED: Не выполнена инициализация WS2_32.DLL";
	case WSAEDISCON: return "WSAEDISCON: Выполняется отключение";
	case WSATYPE_NOT_FOUND: return "WSATYPE_NOT_FOUND: Класс не найден";
	case WSAHOST_NOT_FOUND:	return "WSAHOST_NOT_FOUND: Хост не найден";
	case WSATRY_AGAIN: return "WSATRY_AGAIN: Неавторизированный хост не найден";
	case WSANO_RECOVERY: return "WSANO_RECOVERY: Неопределенная ошибка";
	case WSANO_DATA: return "WSANO_DATA: Нет записи запрошенного типа";
	case WSA_INVALID_HANDLE: return "WSA_INVALID_HANDLE: Указанный дескриптор события с ошибкой";
	case WSA_INVALID_PARAMETER: return "WSA_INVALID_PARAMETER: Один или более параметров с ошибкой";
	case WSA_IO_INCOMPLETE:	return "WSA_IO_INCOMPLETE: Объект ввода - вывода не в сигнальном состоянии";
	case WSA_IO_PENDING: return "WSA_IO_PENDING: Операция завершится позже";
	case WSA_NOT_ENOUGH_MEMORY: return "WSA_NOT_ENOUGH_MEMORY: Не достаточно памяти";
	case WSA_OPERATION_ABORTED: return "WSA_OPERATION_ABORTED: Операция отвергнута";
	case WSASYSCALLFAILURE: return "WSASYSCALLFAILURE: Аварийное завершение системного вызова";
	default: return "**ERROR**";
	};
}


string SetErrorMsgText(string msgText, int code) // Функция возвращает сообщение ошибки
{
	return msgText + GetErrorMsgText(code);
}