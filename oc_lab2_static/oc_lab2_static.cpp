
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include "tchar.h"
#include <atlstr.h>
#include <regex>
#include "atlconv.h" 

using namespace std;

typedef double (*function)(double a, double b);

std::wstring s2ws(const std::string& s)
{
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    wchar_t* buf = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
    std::wstring r(buf);
    delete[] buf;
    return r;
}

bool wayDllInReg() {
    setlocale(LC_ALL, ("Russian"));
    HKEY hKey;
    TCHAR Reget[256] = { 0 };
    DWORD RegetPath = sizeof(Reget);
    TCHAR chekDll();
    bool toCreate(TCHAR fileDll[64]);

    //Поиск DLL
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\lab", 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) {
        cout << " Папка не найдена";
    }
    else
    {
        if ((RegQueryValueEx(hKey, TEXT("String Value"), NULL, NULL, (LPBYTE)&Reget, &RegetPath)) == ERROR_SUCCESS)
        {
            return true;
        }
        else 
        {
            return false;
        }
    }
    RegCloseKey(hKey);
}

void getWayDllFromReg() {
  

    TCHAR fileDll[64];
    HKEY hKey;
    DWORD dwDisposition;
    char strt[256];
    TCHAR Reget[256] = { 0 };
    DWORD RegetPath = sizeof(Reget);
    TCHAR chekDll();
    bool toCreate(TCHAR fileDll[64]);

    //Ишем папку
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\lab", 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) {
        cout << " Папка не найдена";
    }
    else
    {
        //Проверяем файл
        if ((RegQueryValueEx(hKey, TEXT("Way to Dll"), NULL, NULL, (LPBYTE)&Reget, &RegetPath)) == ERROR_SUCCESS)
        {
            //ВЫвод пути
          //  return Reget;
        }
        
    }
    RegCloseKey(hKey);
}

void setWayToDll(string Way) {
  
    TCHAR fileDll[64];
    HKEY hKey;
    DWORD dwDisposition;
    
    char strt[256];
      
    for (int i = 0; i < Way.size(); i++) {
        strt[i] = Way[i];
    }

    TCHAR Reget[256] = { 0 };
    DWORD RegetPath = sizeof(Reget);
    TCHAR chekDll();
    bool toCreate(TCHAR fileDll[64]);

    //Поиск DLL и ввод если нет
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\lab", 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) {
       
    }
    else
    {
            if (RegSetValueEx(hKey, TEXT("String Value"), NULL, REG_SZ, (BYTE*)strt, strlen(strt)) == ERROR_SUCCESS)
            {
                cout << "путь записан";
            } 
        }
 
    RegCloseKey(hKey);
}

int main()
{
     //D:\YandexDisk\C++\oc_lab2_static\oc_lab2_static\Dll3.dll

    setlocale(LC_ALL, "Russian");
    LPCWSTR result;
    std::wstring stemp;
    HMODULE hm = 0;

    std::string fileWay;

    TCHAR fileDll[64];
    HKEY hKey;
    DWORD dwDisposition;
    char strt[256];
    TCHAR Reget[256] = { 0 };
    DWORD RegetPath = sizeof(Reget);
    TCHAR chekDll();
    bool toCreate(TCHAR fileDll[64]);

resetChekWay:

        if (wayDllInReg) 
        {
        //Ишем папку
        if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\lab", 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) {
            cout << " Папка не найдена";
        }
        else
        {
            //Проверяем файл
            if ((RegQueryValueEx(hKey, TEXT("Way to Dll"), NULL, NULL, (LPBYTE)&Reget, &RegetPath)) == ERROR_SUCCESS)
            {
                printf("Найденный путь к DLL");
                printf("%s", Reget);
                hm = LoadLibrary(Reget);

                

            }
        }
        RegCloseKey(hKey);
        }
        else 
        {
        //Записываем адрес и перезапускаем проверку
        printf("Укажите путь к файлу Dll\n");
        std::cin >> fileWay;
        setWayToDll(fileWay);
        goto resetChekWay;
        }


        while (hm == NULL)
        {

            printf("Ошибка загрузки Dll\n");
        resetWay:
            printf("Укажите путь к файлу Dll\n");
            std::cin >> fileWay;

            stemp = s2ws(fileWay);
            result = stemp.c_str();
            hm = LoadLibrary(result);
            setWayToDll(fileWay);
        }
    
    
        function fx = (function)GetProcAddress(hm, "func");
       

        if (fx == NULL)
        {
            printf("Ошибка загрузки функции\n");
            goto resetWay;
        }
        else
        {
            double x, y;

            std::cout << "X = ";
            std::cin >> x;

            std::cout << "Y = ";
            std::cin >> y;

            std::cout << fx(x, y);

            std::cin.get();
        }
    
    
    FreeLibrary(hm);
    

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
