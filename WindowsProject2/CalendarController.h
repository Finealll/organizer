#pragma once
#include "Global.h"

//Инициализирует дескрипторы окон календаря
void CreateCalendarControls(HWND hwnd) {

    hCalendar = CreateWindowW(MONTHCAL_CLASSW, L"",     //Инициализируем дескриптор календарь
        WS_BORDER | WS_CHILD | WS_VISIBLE | MCS_NOTODAYCIRCLE,
        0, 0, 0, 0, hwnd, (HMENU)IDC_CALENAR_BODY, NULL, NULL);
}


void HideCalendar() {       //Функция скрывает все окна календаря
    ShowWindow(hCalendar, SW_HIDE);
}

void ShowCalendar() {       //Функция показывает все окна календаря
    ShowWindow(hCalendar, SW_SHOW);
}