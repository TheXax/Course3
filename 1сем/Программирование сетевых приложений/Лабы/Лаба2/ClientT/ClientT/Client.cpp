#include <iostream>
#include <winsock2.h> //��������� WS2_32.dll
#include <ws2tcpip.h> // ��� inet_addr
#include <string>

#pragma comment(lib, "WS2_32.lib") // ����������� ���������� WS2_32

using namespace std;

string GetErrorMsgText(int code);
string SetErrorMsgText(string msgText, int code);

int main() {
    setlocale(LC_ALL, "rus");

    try {
        WSADATA wsaData;

        // ������������� ���������� Winsock
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw SetErrorMsgText("WSAStartup:", WSAGetLastError());
        }

        SOCKET clientSocket; //���������� �����

        // �������� ������
        clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
        if (clientSocket == INVALID_SOCKET) {
            throw SetErrorMsgText("socket:", WSAGetLastError());
        }

        // ��������� ������ �������
        SOCKADDR_IN serverAddr; //�������� ���������� � �������
        serverAddr.sin_family = AF_INET; //������������� IP-���������
        serverAddr.sin_port = htons(2000); // TCP-���� 2000
        inet_pton(AF_INET, "127.0.0.1", &(serverAddr.sin_addr)); // ����� �������
       // serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // ��������� �����

        // ����������� � �������
        if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            throw SetErrorMsgText("connect:", WSAGetLastError());
        }


        //---------���� ���----------
        //cout << "����������� � ������� �������!" << endl;

        //// ����� ��������� ����������� ������ ���������� ���
        //const char* message = "Hello from Client";
        //send(clientSocket, message, strlen(message) + 1, 0);
        //cout << "��������� ����������: " << message << endl;

        //// �������� ������
        //closesocket(clientSocket);

        //// ���������� ������ Winsock
        //WSACleanup();



        //------------������� ���-�� ���---------------
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
        cout << "������: " << errorMsgText << endl;
    }

    return 0;
}

//������� ��������� �������� ��������� �������
string GetErrorMsgText(int code) {
    string msgText;
    switch (code) {
    case WSAEINTR: msgText = "������ ������� ��������"; break;
    case WSAEACCES: msgText = "���������� ����������"; break;
    case WSAEFAULT: msgText = "��������� �����"; break;
    case WSASYSCALLFAILURE: msgText = "��������� ���������� ���������� ������"; break;
    case WSAENETUNREACH: msgText = "���� ����������"; break;
    case WSAETIMEDOUT: msgText = "����� �������� ���������� �������"; break;
    default: msgText = "����������� ������"; break;
    }
    //TODO: �������� ����
    return msgText;
}

//������� ���������� ��������� ������
string SetErrorMsgText(string msgText, int code) {
    return msgText + GetErrorMsgText(code);
}