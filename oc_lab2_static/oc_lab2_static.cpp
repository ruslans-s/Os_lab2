#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include "tchar.h"
#include <atlstr.h>
#include <regex>


using namespace std;

typedef double (*function)(double a, double b);

__declspec(dllimport) double func(double a, double b);

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


int main()
{
    
   setlocale(LC_ALL, "Russian");
    LPCWSTR result;
    std::wstring stemp;
    HMODULE hm = LoadLibrary(L"Dll3.dll");

    std::string fileWay;

    while(hm == NULL)
    {

        printf("Ошибка загрузки Dll\n");

        resetWay:   
        printf("Укажите путь к файлу Dll\n");
        std::cin >> fileWay;

        stemp = s2ws(fileWay);
        result = stemp.c_str();
        hm = LoadLibrary(result);

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
