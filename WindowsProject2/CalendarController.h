#pragma once
#include "Global.h"

//�������������� ����������� ���� ���������
void CreateCalendarControls(HWND hwnd) {

    hCalendar = CreateWindowW(MONTHCAL_CLASSW, L"",     //�������������� ���������� ���������
        WS_BORDER | WS_CHILD | WS_VISIBLE | MCS_NOTODAYCIRCLE,
        0, 0, 0, 0, hwnd, (HMENU)IDC_CALENAR_BODY, NULL, NULL);
}


void HideCalendar() {       //������� �������� ��� ���� ���������
    ShowWindow(hCalendar, SW_HIDE);
}

void ShowCalendar() {       //������� ���������� ��� ���� ���������
    ShowWindow(hCalendar, SW_SHOW);
}