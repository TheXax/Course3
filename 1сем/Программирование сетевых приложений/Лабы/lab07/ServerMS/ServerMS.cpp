#include <iostream>
#include "windows.h"
#include <string>

using namespace std;

string GetErrorMail(int code)
{
	string msgText = "";
	switch (code)
	{
	case WSAEINTR: msgText = "Операция была прервана"; break;
	case WSAEACCES:	msgText = "Доступ запрещен"; break; //попытка выполнить операцию, к которой нет разрешения
	case WSAEFAULT:	msgText = "Ошибочный адрес"; break;
	default: msgText = "Error";
	};
	return msgText;
}

string SetErrorMail(string msgText, int code)
{
	return msgText + GetErrorMail(code);
}

int main()
{
	setlocale(LC_ALL, "rus");

	try {
		HANDLE serverMailSlot; //дескриптор почтового слота
		int i = 0;
		double t1, t2;

		//создание почтового слота
		if ((serverMailSlot = CreateMailslot(L"\\\\.\\mailslot\\Box",
			300, //байты
			MAILSLOT_WAIT_FOREVER,//функция будет ожидать неограниченное время, пока не будет доступно сообщение
			NULL)) == INVALID_HANDLE_VALUE)
			throw SetErrorMail("CreateMailslot", GetLastError());

		cout << "Hello I'm server" << endl;

		char readBuf[50]; //буфер прочитанных смс
		DWORD readMsg; //хранение прочитанных байт
		do {
			i++;
			//чтение из почтового слота
			if (!ReadFile(serverMailSlot, readBuf, sizeof(readBuf), &readMsg, NULL))
				throw SetErrorMail("ReadFile", GetLastError());
			SetMailslotInfo(serverMailSlot, 5000);//таймаут для почтового слота (если ожидает больше 5с, то ошибка)
			if (i == 1) //если смс первое, то сохраняем время в t1
				t1 = clock();
			cout << readBuf << " " << i << endl;
			
		} while (strcmp(readBuf, " ") != 0); //пока смс не равно пробелу

		t2 = clock();

		cout << "Время передачи: " << (t2 - t1) / 1000 << " сек." << endl;
		cout << "Количество сообщений: " << i - 1 << endl << endl;// -1, потому что последнее пробел

		if (!CloseHandle(serverMailSlot))
			throw "Error: CloseHandle";

		system("pause");
	}
	catch (string e) { 
		if (e == "ReadFileError") {
			cout << e << ": Timeout";
			return 0;
		}
		cout << e << endl;
	}
	return 0;
}