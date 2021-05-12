#pragma once
#include "Global.h"



//Функция создает и возвращает дескриптор окна табов
HWND DoCreateTabControl(HWND hwndParent)
{
    TCITEM tie;         //Структура, описывающая вкладку
    int i;
    TCHAR buff[256];    //Буффер под строку     

    hTabControl = CreateWindow(WC_TABCONTROL, L"",      //Инициализируем дескриптор окна контролов
        WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
        0, 0, 0, 0, hwndParent, NULL, g_hInst, NULL);


    // Добавляем табы к окну
    tie.mask = TCIF_TEXT;
    tie.iImage = -1;
    tie.pszText = buff;

    for (i = 0; i < TABS; i++)          //Загружаем имена вкладок из ресурсов и создаем их
    {
        LoadString(g_hInst, IDS_TAB1 + i,
            buff, sizeof(buff) / sizeof(buff[0]));
        if (TabCtrl_InsertItem(hTabControl, i, &tie) == -1)
        {
            DestroyWindow(hTabControl);
            return NULL;
        }
    }
}





