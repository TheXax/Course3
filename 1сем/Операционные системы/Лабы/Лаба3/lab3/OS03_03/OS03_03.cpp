#include <iostream>
#include <Windows.h>
#include <TlHelp32.h> //содержит PROCESSENTRY32, структуру, используемую для хранения информации о процессе.


int main()
{

    DWORD pid = GetCurrentProcessId(); //идентификатор текукщего процесса(выделит в списке процессов)
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);// создает снимок состояния процессов, потоков и других объектов в системе
    //TH32CS_SNAPALL: Флаг, указывающий, что мы хотим получить снимок всех объектов, включая процессы и модули.
    PROCESSENTRY32 peProcessEntry;// Структура, содержащая информацию о процессе, такую как его имя, идентификатор и идентификатор родительского процесса.
    peProcessEntry.dwSize = sizeof(PROCESSENTRY32); //dwSize - устанавливает размер структуры в байтах

    std::wcout << L"Current pid: " << pid << "\n"; //Используется для вывода строк с широкими символами
    std::wcout << L"------------------------------------------------------\n";
    try
    {
        if (!Process32First(snap, &peProcessEntry)) throw L"Process32First";
        do
        {
            std::wcout << L"Name: " << peProcessEntry.szExeFile << "\n"
                << L"Pid: " << peProcessEntry.th32ProcessID << "\n"
                << L"Ppid: " << peProcessEntry.th32ParentProcessID;
            if (peProcessEntry.th32ProcessID == pid) std::wcout << "---> current process";
            std::wcout << L"\n----------------------------------------------------------------\n";
        } while (Process32Next(snap, &peProcessEntry));
    }
    catch (char* msg) {
        std::wcout << L"ERROR: " << msg << "\n";
    }
    system("pause");
    return 0;
}