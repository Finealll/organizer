#pragma once
#include "Global.h"

//Инициализирует дескрипторы окон будильников
void CreateToDoControls(HWND hwnd) {

    hToDoList = CreateWindowEx(0, L"LISTBOX", NULL    //Инициализируем дескриптор списка задач
        , WS_CHILD  | LBS_STANDARD | LBS_NOTIFY
        , 0, 0, 0, 0
        , hwnd, (HMENU)IDC_TODO_LIST, g_hInst, NULL);

    hToDoInfo = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL,     //Инициализируем дескриптор поля отображения задач
        WS_CHILD  | WS_VSCROLL |
        ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        0, 0, 0, 0, hwnd, (HMENU)IDC_TODO_EDIT, g_hInst, NULL);

    hToDoAdd = CreateWindowEx(0, L"BUTTON", L"Добавить",     //Инициализируем дескриптор кнопки добавить
        WS_TABSTOP  | WS_CHILD | BS_DEFPUSHBUTTON,
        0, 0, 0, 0, hwnd, (HMENU)IDC_TODO_ADDTASK, g_hInst, NULL);

    hToDoDelete = CreateWindowEx(0, L"BUTTON", L"Удалить",     //Инициализируем дескриптор кнопки удалить
        WS_TABSTOP  | WS_CHILD | BS_DEFPUSHBUTTON,
        0, 0, 0, 0, hwnd, (HMENU)IDC_TODO_DELETETASK, g_hInst, NULL);

    hToDoEdit = CreateWindowEx(0, L"BUTTON", L"Изменить",     //Инициализируем дескриптор кнопки изменить
        WS_TABSTOP  | WS_CHILD | BS_DEFPUSHBUTTON,
        0, 0, 0, 0, hwnd, (HMENU)IDC_TODO_EDITTASK, g_hInst, NULL);
}


void HideToDo() {       //Функция скрывает все окна задач
    ShowWindow(hToDoList, SW_HIDE);
    ShowWindow(hToDoInfo, SW_HIDE);
    ShowWindow(hToDoAdd, SW_HIDE);
    ShowWindow(hToDoDelete, SW_HIDE);
    ShowWindow(hToDoEdit, SW_HIDE);
}


void ShowToDo() {       //Функция показывает все окна задач
    ShowWindow(hToDoList, SW_SHOW);
    ShowWindow(hToDoInfo, SW_SHOW);
    ShowWindow(hToDoAdd, SW_SHOW);
    ShowWindow(hToDoDelete, SW_SHOW);
    ShowWindow(hToDoEdit, SW_SHOW);
}