#include <iostream>
#include <WinSock2.h>
#include <string>
using namespace std;


#define PIPE TEXT("\\\\.\\pipe\\Tube")
#define MAX_SIZE_OF_BUFFER 64

string GetErrorMsgText(int code);
string SetPipeError(string msgText, int code);

int main()
{
	try {
		setlocale(LC_ALL, "rus");
		HANDLE sH; //дескриптор именованного канала

		//создаём именованный канал
		if ((sH = CreateNamedPipe(
			PIPE, // Имя канала
			PIPE_ACCESS_DUPLEX, //разрешает чтение и запись в канал
			PIPE_TYPE_MESSAGE | PIPE_WAIT, //данные передаются смс в синхронном режиме
			1, // максимальное кол-во экземпляров канала
			NULL, // размер выходного буфера
			NULL, // размер входного буфера
			INFINITE, // время ожидания связи с клиентом
			NULL)) == INVALID_HANDLE_VALUE) // атрибуты безопасности 
		{
			throw SetPipeError("CreateNamedPipe:", GetLastError());

		}

		if (!ConnectNamedPipe(sH, NULL)) {
			throw SetPipeError("ConnectNamedPipe:", GetLastError());
		}

		cout << "Начинаем прослушку" << endl;

		DWORD dwRead;//кол-во байт
		char buffer[50];//буфер для входящих смс

		while (ReadFile(sH, buffer, sizeof(buffer), &dwRead, NULL) != FALSE)
		{
			cout << "Клиент прислал СМС: " << buffer << endl;
			WriteFile(sH, &buffer, sizeof(buffer), &dwRead, NULL);//отправка смс клиенту
		}

		//отключение какнала от клиента
		if (!DisconnectNamedPipe(sH)) {
			throw SetPipeError("DisconnectNamedPipe:", GetLastError());
		}
		if (!CloseHandle(sH)) {
			throw SetPipeError("CloseHandle:", GetLastError());
		}
	}
	catch (string ErrorPipeText) {
		cout << endl << ErrorPipeText;
	}
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

string SetPipeError(string msgText, int code) // Функция возвращает сообщение ошибки
{
	return msgText + GetErrorMsgText(code);
}