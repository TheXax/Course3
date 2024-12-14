#include <Windows.h>
#include <iostream>

using namespace std;

//функция приоритета процесса
void printProcessPrty(HANDLE h)
{
    DWORD prty = GetPriorityClass(h);//приоритетный класс текущего процесса
    std::cout << " --- Current PID = " << GetCurrentProcessId() << " \n";
    switch (prty)//для определения класса приоритета
    {
    case IDLE_PRIORITY_CLASS:
        cout << " ----+ Priority of process = IDLE_PRIORITY_CLASS \n";
        break;
    case BELOW_NORMAL_PRIORITY_CLASS:
        cout << " ----+ Priority of process = BELOW_NORMAL_PRIORITY_CLASS \n";
        break;
    case NORMAL_PRIORITY_CLASS:
        cout << " ----+ Priority of process = NORMAL_PRIORITY_CLASS \n";
        break;
    case ABOVE_NORMAL_PRIORITY_CLASS:
        cout << " ----+ Priority of process = ABOVE_NORMAL_PRIORITY_CLASS \n";
        break;
    case HIGH_PRIORITY_CLASS:
        cout << " ----+ Priority of process = HIGH_PRIORITY_CLASS \n";
        break;
    case REALTIME_PRIORITY_CLASS:
        cout << " ----+ Priority of process = REALTIME_PRIORITY_CLASS \n";
        break;
    default:
        cout << " ----+ Priority of process = ? \n";
        break;
    }
    return;
}

//функция приоритета потока
void printThreadPrty(HANDLE h)
{
    DWORD icpu = SetThreadIdealProcessor(h, MAXIMUM_PROCESSORS);//Устанавливает идеальный процессор для потока. MAXIMUM_PROCESSORS указывает максимальное количество процессоров, доступных системе
    DWORD prty = GetThreadPriority(h);//приоритет потока
    std::cout << " --- Current Thread ID = " << GetCurrentThreadId() << "\n";
    std::cout << " ----+ priority = " << prty << " \n";
    switch (prty)
    {
    case THREAD_PRIORITY_LOWEST:
        cout << " ----+ Priority of thread     = THREAD_PRIORITY_LOWEST \n";
        break;
    case THREAD_PRIORITY_BELOW_NORMAL:
        cout << " ----+ Priority of thread = THREAD_PRIORITY_BELOW_NORMAL \n";
        break;
    case THREAD_PRIORITY_NORMAL:
        cout << " ----+ Priority of thread = THREAD_PRIORITY_NORMAL \n";
        break;
    case THREAD_PRIORITY_ABOVE_NORMAL:
        cout << " ----+ Priority of thread = THREAD_PRIORITY_ABOVE_NORMAL \n";
        break;
    case THREAD_PRIORITY_HIGHEST:
        cout << " ----+ Priority of thread = THREAD_PRIORITY_HIGHEST \n";
        break;
    case THREAD_PRIORITY_IDLE:
        cout << " ----+ Priority of thread = THREAD_PRIORITY_IDLE \n";
        break;
    case THREAD_PRIORITY_TIME_CRITICAL:
        cout << " ----+ Priority of thread = THREAD_PRIORITY_TIME_CRITICAL \n";
        break;
    default:
        cout << " ----+ Priority of thread = ? \n";
        break;
    }
    cout << " ----+ IdealProcessor = " << icpu << " \n"; //номер процессора, на который установлен идеальный процессор для потока
    return;
}

string toBinary(int n)
{
    std::string r;
    while (n != 0) { r = (n % 2 == 0 ? "0" : "1") + r; n /= 2; }
    return r;
}

// Функция для подсчета количества доступных процессоров
int countAvailableProcessors(DWORD_PTR affinityMask)
{
    int count = 0;
    while (affinityMask)
    {
        count += (affinityMask & 1); // Увеличиваем счетчик, если младший бит равен 1
        affinityMask >>= 1; // Сдвигаем маску вправо
    }
    return count;
}

int main()
{
    HANDLE hp = GetCurrentProcess();
    HANDLE ht = GetCurrentThread();

    printProcessPrty(hp);
    printThreadPrty(ht);

    try
    {
        {
            DWORD_PTR pa = NULL, sa = NULL, icpu = -1;//для масок процессоров
            if (!GetProcessAffinityMask(hp, &pa, &sa))//Получает маску процессоров, доступных для текущего процесса
                throw "GetProcessAffinityMask";
            cout << " Process Affinity Mask: " << toBinary(pa) << "\n";
            cout << " System Affinity Mask: " << toBinary(sa) << "\n";

            // Подсчет количества доступных процессоров для текущего процесса
            int availableProcessors = countAvailableProcessors(pa);
            cout << " ----+ Available Processors for current process = " << availableProcessors << " \n";
        }
    }
    catch (char* msg)
    {
        cout << "Error " << msg << "\n";
    }

    system("pause");
    return 0;
}