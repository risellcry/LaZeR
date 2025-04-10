#include <process.h>

int main()
{
    system("g++ editor.cpp -o LaZeR");
    system("g++ language.cpp -o LaZecript");
    system("rcedit LaZecript.exe --set-icon Logo.ico");
    return 0;
}