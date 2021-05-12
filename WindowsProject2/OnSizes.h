#pragma once
#include "Global.h"

//Меняет размеры окон таб контроллера
HRESULT OnSizeTabController(LPARAM lParam)
{
    //Изменяем размеры окна, если успешно - S_OK, иначе E_FAIL
    if (!SetWindowPos(hTabControl, HWND_TOP, 0, 0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), SWP_SHOWWINDOW))
        return E_FAIL;

    return S_OK;
}


//Изменение размера обасти календаря
HRESULT OnSizeCalendar(LPARAM lParam)
{
    //Изменяем размеры окна, если успешно - S_OK, иначе E_FAIL
    if (!SetWindowPos(hCalendar, HWND_TOP, 0, 25, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) - 25, SWP_NOOWNERZORDER))
        return E_FAIL;

    return S_OK;
}


//Изменение размера обасти ToDo листа
HRESULT OnSizeToDoList(LPARAM lParam)
{
    //Изменяем размеры окна, если успешно - S_OK, иначе E_FAIL
    if (!SetWindowPos(hToDoList, HWND_TOP, 0, 25, GET_X_LPARAM(lParam)/100*40, GET_Y_LPARAM(lParam)-50 - 25, SWP_NOZORDER))
        return E_FAIL;  //Лист
    if (!SetWindowPos(hToDoInfo, HWND_TOP, GET_X_LPARAM(lParam) / 100 * 40, 25, GET_X_LPARAM(lParam) / 100 * 60, GET_Y_LPARAM(lParam) - 25, SWP_NOZORDER))
        return E_FAIL;  //Едитбокс
    if (!SetWindowPos(hToDoAdd, HWND_TOP, 5, GET_Y_LPARAM(lParam)-40, GET_X_LPARAM(lParam) / 100 * 40 / 3.2, 30, SWP_NOZORDER))
        return E_FAIL;  //Кнопка добавить
    if (!SetWindowPos(hToDoDelete, HWND_TOP, GET_X_LPARAM(lParam) / 100 * 40 / 3.2 + 10, GET_Y_LPARAM(lParam) - 40, 
        GET_X_LPARAM(lParam) / 100 * 40 / 3.2, 30, SWP_NOZORDER))
        return E_FAIL;  //Кнопка удалить
    if (!SetWindowPos(hToDoEdit, HWND_TOP, GET_X_LPARAM(lParam) / 100 * 40 / 3.2 * 2 + 15, GET_Y_LPARAM(lParam) - 40,
        GET_X_LPARAM(lParam) / 100 * 40 / 3.2, 30, SWP_NOZORDER))
        return E_FAIL;  //Кнопка изменить

    return S_OK;
}

//Изменение размера обасти будильника
HRESULT OnSizeAlarms(LPARAM lParam)
{
    //Изменяем размеры окна, если успешно - S_OK, иначе E_FAIL
    if (!SetWindowPos(hAlarmList, HWND_TOP, 20, 120, GET_X_LPARAM(lParam)-40, GET_Y_LPARAM(lParam) - 100-50, SWP_NOZORDER))
        return E_FAIL;  //Лист
    if (!SetWindowPos(hAlarmAdd, HWND_TOP, 20, 20+60, GET_X_LPARAM(lParam) / 100 * 46, 30, SWP_NOZORDER))
        return E_FAIL;  //Кнопка добавить
    if (!SetWindowPos(hAlarmDelete, HWND_TOP, GET_X_LPARAM(lParam)-20- GET_X_LPARAM(lParam) / 100 * 46, 20+60, GET_X_LPARAM(lParam) / 100 * 46, 30, SWP_NOZORDER))
        return E_FAIL;  //Кнопка удалить

    return S_OK;
}
