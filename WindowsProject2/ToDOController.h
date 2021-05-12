#pragma once
#include "Global.h"

//�������������� ����������� ���� �����������
void CreateToDoControls(HWND hwnd) {

    hToDoList = CreateWindowEx(0, L"LISTBOX", NULL    //�������������� ���������� ������ �����
        , WS_CHILD  | LBS_STANDARD | LBS_NOTIFY
        , 0, 0, 0, 0
        , hwnd, (HMENU)IDC_TODO_LIST, g_hInst, NULL);

    hToDoInfo = CreateWindowEx(WS_EX_CLIENTEDGE, L"EDIT", NULL,     //�������������� ���������� ���� ����������� �����
        WS_CHILD  | WS_VSCROLL |
        ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | ES_READONLY,
        0, 0, 0, 0, hwnd, (HMENU)IDC_TODO_EDIT, g_hInst, NULL);

    hToDoAdd = CreateWindowEx(0, L"BUTTON", L"��������",     //�������������� ���������� ������ ��������
        WS_TABSTOP  | WS_CHILD | BS_DEFPUSHBUTTON,
        0, 0, 0, 0, hwnd, (HMENU)IDC_TODO_ADDTASK, g_hInst, NULL);

    hToDoDelete = CreateWindowEx(0, L"BUTTON", L"�������",     //�������������� ���������� ������ �������
        WS_TABSTOP  | WS_CHILD | BS_DEFPUSHBUTTON,
        0, 0, 0, 0, hwnd, (HMENU)IDC_TODO_DELETETASK, g_hInst, NULL);

    hToDoEdit = CreateWindowEx(0, L"BUTTON", L"��������",     //�������������� ���������� ������ ��������
        WS_TABSTOP  | WS_CHILD | BS_DEFPUSHBUTTON,
        0, 0, 0, 0, hwnd, (HMENU)IDC_TODO_EDITTASK, g_hInst, NULL);
}


void HideToDo() {       //������� �������� ��� ���� �����
    ShowWindow(hToDoList, SW_HIDE);
    ShowWindow(hToDoInfo, SW_HIDE);
    ShowWindow(hToDoAdd, SW_HIDE);
    ShowWindow(hToDoDelete, SW_HIDE);
    ShowWindow(hToDoEdit, SW_HIDE);
}


void ShowToDo() {       //������� ���������� ��� ���� �����
    ShowWindow(hToDoList, SW_SHOW);
    ShowWindow(hToDoInfo, SW_SHOW);
    ShowWindow(hToDoAdd, SW_SHOW);
    ShowWindow(hToDoDelete, SW_SHOW);
    ShowWindow(hToDoEdit, SW_SHOW);
}