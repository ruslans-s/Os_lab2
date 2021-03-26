
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

void setWayToDll(char strt[256]) {
  
    TCHAR fileDll[64];
    HKEY hKey;
    DWORD dwDisposition;
    
    

    TCHAR Reget[256] = { 0 };
    DWORD RegetPath = sizeof(Reget);
    TCHAR chekDll();
    bool toCreate(TCHAR fileDll[64]);

    //Поиск DLL и ввод если нет
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\lab", 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) {
       
    }
    else
    {
            if (RegSetValueEx(hKey, TEXT("Way to Dll"), NULL, REG_SZ, (BYTE*)strt, strlen(strt)) == ERROR_SUCCESS)
            {
                cout << "путь записан";
            } 
        }
 
    RegCloseKey(hKey);
}

std::string make_string(LPBYTE data, int size)
{
    return std::string(reinterpret_cast<char*>(data), reinterpret_cast<char*>(data + size));
}

int main()
{
     //D:\YandexDisk\C++\oc_lab2_static\oc_lab2_static\Dll3.dll

    setlocale(LC_ALL, "Russian");
    LPCWSTR result;
    std::wstring stemp;
    HMODULE hm = 0;

   // std::string fileWay;

    TCHAR fileDll[64];
    HKEY hKey;
    DWORD dwDisposition;
    char fileWay[256];
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
            if ((RegQueryValueEx(hKey, TEXT("Way to Dll"), NULL, NULL, (LPBYTE)&fileWay, &RegetPath)) == ERROR_SUCCESS)  {
                printf("Найденный путь к DLL");

                printf("%s", Reget);
               
                stemp = s2ws(fileWay);
                result = stemp.c_str();
                hm = LoadLibrary(result);
              

            }
            else {
                printf("%s", Reget);
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
