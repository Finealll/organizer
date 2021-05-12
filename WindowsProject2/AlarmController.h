#pragma once
#include "Global.h"


//�������������� ����������� ���� �����������
void CreateAlarmControls(HWND hwnd) {

    hAlarmList = CreateWindowEx(0, L"LISTBOX", NULL     //�������������� ���������� ������ �����������
        , WS_CHILD | LBS_STANDARD | LBS_NOTIFY
        , 0, 0, 0, 0
        , hwnd, (HMENU)IDC_ALARM_LIST, g_hInst, NULL);

    hAlarmAdd = CreateWindowEx(0, L"BUTTON", L"��������",     //�������������� ���������� ������ ��������
        WS_TABSTOP | WS_CHILD | BS_DEFPUSHBUTTON,
        0, 0, 0, 0, hwnd, (HMENU)IDC_ALARM_ADD, g_hInst, NULL);

    hAlarmDelete = CreateWindowEx(0, L"BUTTON", L"�������",     //�������������� ���������� ������ �������
        WS_TABSTOP | WS_CHILD | BS_DEFPUSHBUTTON,
        0, 0, 0, 0, hwnd, (HMENU)IDC_ALARM_DELETE, g_hInst, NULL);
}


void HideAlarm() {       //������� �������� ��� ���� �����������
    ShowWindow(hAlarmList, SW_HIDE);
    ShowWindow(hAlarmAdd, SW_HIDE);
    ShowWindow(hAlarmDelete, SW_HIDE);
}


void ShowAlarm() {       //������� ���������� ��� ���� �����������
    ShowWindow(hAlarmList, SW_SHOW);
    ShowWindow(hAlarmAdd, SW_SHOW);
    ShowWindow(hAlarmDelete, SW_SHOW);
}


