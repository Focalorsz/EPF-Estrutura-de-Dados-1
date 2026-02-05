#ifndef PORTABILIDADE_H
#define PORTABILIDADE_H

#ifdef _WIN32
    #include <windows.h>
    #define delay(x) Sleep((x)*1000)
    #define clear_screen() system("cls")
#else
    #include <unistd.h>
    #define delay(x) sleep(x)
    #define clear_screen() system("clear")
#endif

#endif