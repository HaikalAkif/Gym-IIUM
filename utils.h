#ifndef __UTILS_H
#define __UTILS_H

#include <Windows.h>
#include <conio.h>
#include <stdlib.h>

namespace utils {
    // Change the color of the font in the program
    // color var 1-14
    void fontColor(int Color){
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
    }
<<<<<<< Updated upstream
    // set font for the program
=======

    // Set the font for the program
>>>>>>> Stashed changes
    void setfont(){
        CONSOLE_FONT_INFOEX font;
        font.cbSize = sizeof(font);
        font.nFont = 0;
        font.dwFontSize.X = 0;
        font.dwFontSize.Y = 24;

        font.FontFamily = FF_DONTCARE;
        font.FontWeight = FW_NORMAL;

        wcscpy(font.FaceName, L"Consolas");

        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font);
    }
<<<<<<< Updated upstream
    // show=true disable=false
=======

    // true to show cursor, false to remove cursor
>>>>>>> Stashed changes
    void ShowConsoleCursor(bool showFlag){
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out,&cursorInfo);
        cursorInfo.bVisible = showFlag;
        SetConsoleCursorInfo(out,&cursorInfo);
    }

    // Create cursor location variable
    HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD CursorPosition;

<<<<<<< Updated upstream
    // x-direction, y-direction
=======
    // x for x-direction, y for y-direction
>>>>>>> Stashed changes
    void gotoxy(int x, int y){
        CursorPosition.X = x;
        CursorPosition.Y = y;
        SetConsoleCursorPosition(Console, CursorPosition);
    }
}

#endif
