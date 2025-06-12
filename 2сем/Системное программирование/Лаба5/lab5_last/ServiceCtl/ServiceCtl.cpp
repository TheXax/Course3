#include <windows.h>
#include <iostream>
#include <string>

void PrintUsage() { //вывод конструкций по использованию
    std::cout
        << " Usage: ServiceCtl <ServiceName> create <path_to_DemoService>\n"
        << "        ServiceCtl <ServiceName> start <path_to_config>\n"
        << "        ServiceCtl <ServiceName> stop\n"
        << "        ServiceCtl <ServiceName> delete\n"
        << "        ServiceCtl <ServiceName> pause\n"
        << "        ServiceCtl <ServiceName> continue\n"
        << "        ServiceCtl <ServiceName> info\n"
        << "        ServiceCtl <ServiceName> test\n"
        << "        ServiceCtl <ServiceName> reload    <-- Reload configuration\n";
}

void PrintServiceInfo(SC_HANDLE service) { //запрашивает и выводит инфу о состоянии сервиса
    SERVICE_STATUS status;
    if (QueryServiceStatus(service, &status)) {
        std::cout << "Service Status:\n";
        std::cout << "  Current State: " << status.dwCurrentState << "\n";
        std::cout << "  Exit Code: " << status.dwWin32ExitCode << "\n";
        std::cout << "  Service Type: " << status.dwServiceType << "\n";
    }
    else {
        DWORD err = GetLastError();
        std::cerr << "Failed to retrieve service information. Error Code: " << err << "\n";
    }
}

int main(int argc, char* argv[]) {
    SetConsoleOutputCP(CP_UTF8);

    if (argc < 3) { //строка должна содержать не менее 3 аргументов, иначе выводит позказку вывода
        PrintUsage();
        return 1;
    }

    std::string serviceName = argv[1]; //для аргумента (второго) - имя сервиса
    std::string command = argv[2]; //для аргумента (третьего) - команда

    SC_HANDLE scm = OpenSCManager(nullptr, nullptr, SC_MANAGER_ALL_ACCESS); //открытие дескриптора
    if (!scm) {
        std::cerr << "Error: Failed to open Service Control Manager.\n";
        return 1;
    }

    if (command == "create") {
        if (argc < 4) { //4 - путь к исполняемому файлу - ServiceCtl DemoService create C:\path\to\DemoService.exe
            std::cerr << "Error: Specify the path to DemoService.exe.\n";
            return 1;
        }

        std::string path = argv[3]; //присваимаем путь

        SC_HANDLE service = CreateService(
            scm,
            serviceName.c_str(),
            serviceName.c_str(),
            SERVICE_ALL_ACCESS,
            SERVICE_WIN32_OWN_PROCESS,
            SERVICE_DEMAND_START,
            SERVICE_ERROR_NORMAL,
            path.c_str(),
            nullptr, nullptr, nullptr, nullptr, nullptr
        );

        if (!service) {
            std::cerr << "Error: Failed to create the service.\n";
        }
        else {
            std::cout << "Service successfully created.\n";
            CloseServiceHandle(service);
        }

    }
    else if (command == "delete") {
        SC_HANDLE service = OpenService(scm, serviceName.c_str(), DELETE);
        if (service) {
            DeleteService(service);
            CloseServiceHandle(service);
            std::cout << "Service successfully deleted.\n";
        }
        else {
            std::cerr << "Error: Failed to open the service for deletion.\n";
        }
  

    }
    else {
        DWORD access = SERVICE_QUERY_STATUS | SERVICE_START | SERVICE_STOP | SERVICE_PAUSE_CONTINUE |
            SERVICE_USER_DEFINED_CONTROL | SERVICE_CHANGE_CONFIG;

        SC_HANDLE service = OpenService(scm, serviceName.c_str(), access); //задаём права доступа access
        if (!service) {
            std::cerr << "Error: Failed to open the service.\n";
            return 1;
        }

        if (command == "start") {
            bool useConfig = false;
            std::string configPath;

            if (argc >= 4) {
                configPath = argv[3];
                DWORD fileAttr = GetFileAttributesA(configPath.c_str());
                if (fileAttr != INVALID_FILE_ATTRIBUTES && !(fileAttr & FILE_ATTRIBUTE_DIRECTORY)) {
                    useConfig = true;
                }
            }

            if (useConfig) {
                LPCSTR args[] = { configPath.c_str(), nullptr };
                if (StartServiceA(service, 1, args)) {
                    std::cout << "Service started with configuration: " << configPath << "\n";
                }
                else {
                    std::cerr << "Error: Failed to start the service. Error Code: " << GetLastError() << "\n";
                }
            }
            else {
                if (StartServiceA(service, 0, nullptr)) {
                    std::cout << "use def\n";
                }
                else {
                    std::cerr << "Error: Failed to start the service. Error Code: " << GetLastError() << "\n";
                }
            }
        }


        /*if (command == "start") {
            if (argc < 4) { //проверка наличия пути к конфигурации
                std::cerr << "Error: Specify the path to the configuration file.\n";
                return 1;
            }

            std::string configPath = argv[3]; //сохраняем путь
            LPSTR args[] = { (LPSTR)configPath.c_str() };
            StartServiceA(service, 1, (LPCSTR*)args);
            std::cout << "Service started with configuration: " << configPath << "\n";

        }*/
        else if (command == "stop") {
            SERVICE_STATUS status;
            ControlService(service, SERVICE_CONTROL_STOP, &status);
            std::cout << "Service stopped.\n";

        }
        else if (command == "pause") {
            SERVICE_STATUS status;
            ControlService(service, SERVICE_CONTROL_PAUSE, &status);
            std::cout << "Service paused.\n";

        }
        else if (command == "continue") {
            SERVICE_STATUS status;
            ControlService(service, SERVICE_CONTROL_CONTINUE, &status);
            std::cout << "Service continued.\n";

        }
        else if (command == "info") {
            PrintServiceInfo(service);

        }
        else if (command == "test") {
            SERVICE_STATUS status;
            ControlService(service, 138, &status);
            std::cout << "Custom control signal sent.\n";

        }
        else if (command == "reload") {
            SERVICE_STATUS status;
            ControlService(service, SERVICE_CONTROL_PARAMCHANGE, &status);
            std::cout << "Configuration reload signal sent.\n";
        }
        else {
            PrintUsage();
        }

        CloseServiceHandle(service);
    }

    CloseServiceHandle(scm);
    return 0;
}
