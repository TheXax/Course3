#include <iostream>
#include <winsock2.h> //��������� WS2_32.dll
#include <ws2tcpip.h> // ��� inet_ntoa
#include <string>

#pragma comment(lib, "WS2_32.lib") // ����������� ���������� WS2_32

using namespace std;

string GetErrorMsgText(int code);
string SetErrorMsgText(string msgText, int code);

int main() {
    setlocale(LC_ALL, "rus");

    try {
        WSADATA wsaData; //������ ���������

        // ������������� ���������� Winsock
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw SetErrorMsgText("WSAStartup:", WSAGetLastError());
        }

        SOCKET serverSocket; // ���������� �����, ���������� ������

        // �������� ������
        serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (serverSocket == INVALID_SOCKET) {
            throw SetErrorMsgText("socket:", WSAGetLastError());
        }

        // ��������� ������
        SOCKADDR_IN serv; //��������� ��� �������� ���������� � �������
        serv.sin_family = AF_INET; //������������ IP-���������
        serv.sin_port = htons(2000); // ���� 2000
        serv.sin_addr.s_addr = INADDR_ANY; // ��������� ���������� �� ����� IP

        // �������� ������
        if (bind(serverSocket, (LPSOCKADDR)&serv, sizeof(serv)) == SOCKET_ERROR) {
            throw SetErrorMsgText("bind:", WSAGetLastError());
        }

        // ������� ������ � ����� �������������
        if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
            throw SetErrorMsgText("listen:", WSAGetLastError());
        }

        cout << "������ ����� ��������� �� ����� 2000..." << endl;

        // �������� ��������� ����������
        SOCKADDR_IN clientAddr; //��� ������ �������  � ��������
        int clientAddrSize = sizeof(clientAddr); //������ SOCKADDR_IN
        //������� accept ������ ����� �� ������� �������� � ������ ����� ��� ������ ������� �� ����� ������
        SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == INVALID_SOCKET) {
            throw SetErrorMsgText("accept:", WSAGetLastError());
        }

        cout << "������ ���������: " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << endl;//

        char buffer[256];
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            cout << "��������� �� �������: " << buffer << endl;
        }

        // �������� �������
        closesocket(clientSocket);
        closesocket(serverSocket);

        // ���������� ������ Winsock
        WSACleanup();
    }
    catch (string errorMsgText) {
        cout << "������: " << errorMsgText << endl;
    }

    return 0;
}

//������� ��������� �������� ��������� �� ������
string GetErrorMsgText(int code) {
    string msgText;
    switch (code) {
    case WSAEINTR: msgText = "������ ������� ��������"; break;
    case WSAEACCES: msgText = "���������� ����������"; break;
    case WSAEFAULT: msgText = "��������� �����"; break;
    case WSASYSCALLFAILURE: msgText = "��������� ���������� ���������� ������"; break;
    default: msgText = "����������� ������"; break;
    }
    //TODO: �������� ����
    return msgText;
}
//������� ���������� ��������� ������
string SetErrorMsgText(string msgText, int code) {
    return msgText + GetErrorMsgText(code);
}