#include <iostream>
#include "windows.h"
#include <string>
#include "ClientMS.h"

using namespace std;

string GetErrorMail(int code)
{
	string msgText = "";
	switch (code)
	{
	case WSAEINTR: msgText = "Операция была прервана"; break;
	case WSAEACCES:	msgText = "Доступ запрещен"; break;
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
		HANDLE clientMailSlot; //дескриптор почтового слота
		double t1, t2;
		LPCTSTR name = TEXT("\\\\.\\mailslot\\Box");
		LPCTSTR NAME[] = {
			TEXT("\\\\DESKTOP-HPV9KK7\\mailslot\\Box"),
			TEXT("\\\\Karasik\\mailslot\\Box"),
			TEXT("\\\\.\\mailslot\\Box")
		};
		 //открытие почтового слота для записи
		//for (int i = 0; i < 3; i++) {
			if ((clientMailSlot = CreateFile(name, //NAME[i]
				GENERIC_WRITE,
				FILE_SHARE_READ | FILE_SHARE_WRITE, //позволяет другим процессам читать из и записывать в почтовый слот, пока он открыт
				NULL,
				OPEN_EXISTING, //указывает, что хотим открыть существующий почтовый слот
				NULL,
				NULL)) == INVALID_HANDLE_VALUE)
				throw SetErrorMail("CreateFile: ", GetLastError());
		
		cout << "Hello I'm Client" << endl;

		char writeBuf[50] = "Hello from Mailslot-client";
		DWORD writeMsg; //хранение кол-ва байт, фактически записанных в почтовый слот

		t1 = clock();

		for (int i = 1; i <= 1000; i++) {
			if(!WriteFile(clientMailSlot,writeBuf,sizeof(writeBuf),&writeMsg,NULL))
				throw SetErrorMail("WriteFile: ", GetLastError());

			cout << "Message " << i << " was sent" << endl;
		}

		t2 = clock();

		if (!CloseHandle(clientMailSlot))
			throw "Error: CloseHandle";
		//}
		cout << endl << "Время передачи: " << (t2 - t1) / 1000 << " сек." << endl << endl;
		system("pause");
	}
	catch (string e) {
		cout << e << endl;
	}
	
	return 0;
}
