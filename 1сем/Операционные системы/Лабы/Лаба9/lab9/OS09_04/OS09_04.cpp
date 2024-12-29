#define _CRT_NON_CONFORMING_WCSTOK //отключают предупреждения о небезопасных функциях
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <ctime>

using namespace std;

#define FOLDER_PATH L"C:/Лабы/Операционные системы/Лабы/Лаба9/lab9"
#define FILE_PATH L"C:/Лабы/Операционные системы/Лабы/Лаба9/lab9/OS09_01.txt"

int rowC = 0; //кол-во строк в файле
HANDLE mutex; //Дескриптор мьютекса для управления доступом к файлу
// это объект синхронизации, который используется для управления доступом к общему ресурсу в многопоточной среде. Он позволяет гарантировать, что только один поток в любой момент времени имеет доступ к ресурсу, защищенному мьютексом.

BOOL printWatchRowFileTxt(LPWSTR FileName, DWORD mlsec, DWORD maxDuration)
{
    LARGE_INTEGER fileSize = { 0 }; //размер файла
    int rowCount = 0; //счётчик строк

    try {
        //создание уведомлений
        HANDLE notif = FindFirstChangeNotification(FOLDER_PATH, FALSE, FILE_NOTIFY_CHANGE_LAST_WRITE);
        if (notif == INVALID_HANDLE_VALUE) {
            cout << "Ошибка при инициализации уведомления о изменениях." << endl;
            return FALSE;
        }

        DWORD dwWaitStatus; //для статуса ожидания
        DWORD startTime = GetTickCount(); //текущее время с момента запуска системы

        while (true) {
            if ((GetTickCount() - startTime) >= maxDuration) {
                cout << "\nВремя слежения истекло." << endl;
                break;
            }

            dwWaitStatus = WaitForSingleObject(notif, mlsec); //ожидает изменения в папке; ждёт уведовления о событии

            switch (dwWaitStatus) {
            case WAIT_OBJECT_0: {
                if (FindNextChangeNotification(notif) == FALSE) { //если не найдено next изменения, выходим из цикла
                    break;
                }

                WaitForSingleObject(mutex, INFINITE); //ожидает пока мьютекс булет доступен

                HANDLE of = CreateFile(
                    FileName,
                    GENERIC_READ,
                    FILE_SHARE_READ,
                    NULL,
                    OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL,
                    NULL
                );

                if (of == INVALID_HANDLE_VALUE) {
                    DWORD dwError = GetLastError();
                    //cout << "Ошибка: не удалось открыть файл. Код ошибки: " << dwError << endl;
                }
                else if (GetFileSizeEx(of, &fileSize)) { //получает размер файла
                    //для буфера, куда будут считываться данные
                    char* buf = new char[(fileSize.QuadPart + 1) * sizeof(char)];
                    ZeroMemory(buf, (fileSize.QuadPart + 1) * sizeof(char));
                    DWORD n = 0;
                    if (ReadFile(of, buf, fileSize.QuadPart, &n, NULL)) {
                        int position = 0; //текущая позиция в буфере
                        rowCount = 0; //кол-во строк
                        bool lastLineIsEmpty = false; //флаг была ли последняя строка пустой
                        while (buf[position] != '\0') {
                            if (buf[position] == '\n') { //если встречается данный символ, то увеличиваем кол-во строк
                                rowCount++;
                                lastLineIsEmpty = false; //false, тк строка завершается символом переноса
                            }
                            else {
                                lastLineIsEmpty = true; //иначе флаг в состояние, когда строка не пустая
                            }
                            position++;
                        }
                        //Если последняя строка не пустая и не заканчивается символом новой строки, увеличиваем счетчик строк
                        if (lastLineIsEmpty && position > 0 && buf[position - 1] != '\n') {
                            rowCount++;
                        }
                    }
                    delete[] buf; //освобождение памяти
                    CloseHandle(of);
                }
                else {
                    cout << "Ошибка при чтении файла." << endl;
                }

                ReleaseMutex(mutex);
                if (rowC != rowCount) { //если кол-во строк изменилось
                    cout << "\nКоличество строк: " << rowCount;
                    if (rowCount > rowC) {
                        cout << " (Строки добавлены)" << endl;
                    }
                    else if (rowCount < rowC) {
                        cout << " (Строки удалены)" << endl;
                    }
                    rowC = rowCount;
                }
                break;
            }
            default:
                break;
            }
        }
        CloseHandle(notif);
    }
    catch (const char* err) {
        cout << "Ошибка: " << err << "\n";
        return false;
    }
    return true;
}

int main()
{
    setlocale(LC_ALL, "ru");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    mutex = CreateMutex(NULL, FALSE, L"FileAccessMutex"); //создание мьютекса для управления доступом к файлу
    if (mutex == NULL) {
        cout << "Ошибка создания мьютекса." << endl;
        return 1;
    }

    LPWSTR fileName = (LPWSTR)FILE_PATH; //сохраняет путь к файлу
    DWORD waitTime = 1000; //время ожидания
    DWORD maxDuration = 10000; //max время слежения

    if (!printWatchRowFileTxt(fileName, waitTime, maxDuration)) {
        cout << "Ошибка при отслеживании изменений в файле." << endl;
    }

    CloseHandle(mutex);
    return 0;
}