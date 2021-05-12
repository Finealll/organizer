#pragma once
#include "Global.h"

//������ ������� ���� ��� �����������
HRESULT OnSizeTabController(LPARAM lParam)
{
    //�������� ������� ����, ���� ������� - S_OK, ����� E_FAIL
    if (!SetWindowPos(hTabControl, HWND_TOP, 0, 0, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), SWP_SHOWWINDOW))
        return E_FAIL;

    return S_OK;
}


//��������� ������� ������ ���������
HRESULT OnSizeCalendar(LPARAM lParam)
{
    //�������� ������� ����, ���� ������� - S_OK, ����� E_FAIL
    if (!SetWindowPos(hCalendar, HWND_TOP, 0, 25, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) - 25, SWP_NOOWNERZORDER))
        return E_FAIL;

    return S_OK;
}


//��������� ������� ������ ToDo �����
HRESULT OnSizeToDoList(LPARAM lParam)
{
    //�������� ������� ����, ���� ������� - S_OK, ����� E_FAIL
    if (!SetWindowPos(hToDoList, HWND_TOP, 0, 25, GET_X_LPARAM(lParam)/100*40, GET_Y_LPARAM(lParam)-50 - 25, SWP_NOZORDER))
        return E_FAIL;  //����
    if (!SetWindowPos(hToDoInfo, HWND_TOP, GET_X_LPARAM(lParam) / 100 * 40, 25, GET_X_LPARAM(lParam) / 100 * 60, GET_Y_LPARAM(lParam) - 25, SWP_NOZORDER))
        return E_FAIL;  //��������
    if (!SetWindowPos(hToDoAdd, HWND_TOP, 5, GET_Y_LPARAM(lParam)-40, GET_X_LPARAM(lParam) / 100 * 40 / 3.2, 30, SWP_NOZORDER))
        return E_FAIL;  //������ ��������
    if (!SetWindowPos(hToDoDelete, HWND_TOP, GET_X_LPARAM(lParam) / 100 * 40 / 3.2 + 10, GET_Y_LPARAM(lParam) - 40, 
        GET_X_LPARAM(lParam) / 100 * 40 / 3.2, 30, SWP_NOZORDER))
        return E_FAIL;  //������ �������
    if (!SetWindowPos(hToDoEdit, HWND_TOP, GET_X_LPARAM(lParam) / 100 * 40 / 3.2 * 2 + 15, GET_Y_LPARAM(lParam) - 40,
        GET_X_LPARAM(lParam) / 100 * 40 / 3.2, 30, SWP_NOZORDER))
        return E_FAIL;  //������ ��������

    return S_OK;
}

//��������� ������� ������ ����������
HRESULT OnSizeAlarms(LPARAM lParam)
{
    //�������� ������� ����, ���� ������� - S_OK, ����� E_FAIL
    if (!SetWindowPos(hAlarmList, HWND_TOP, 20, 120, GET_X_LPARAM(lParam)-40, GET_Y_LPARAM(lParam) - 100-50, SWP_NOZORDER))
        return E_FAIL;  //����
    if (!SetWindowPos(hAlarmAdd, HWND_TOP, 20, 20+60, GET_X_LPARAM(lParam) / 100 * 46, 30, SWP_NOZORDER))
        return E_FAIL;  //������ ��������
    if (!SetWindowPos(hAlarmDelete, HWND_TOP, GET_X_LPARAM(lParam)-20- GET_X_LPARAM(lParam) / 100 * 46, 20+60, GET_X_LPARAM(lParam) / 100 * 46, 30, SWP_NOZORDER))
        return E_FAIL;  //������ �������

    return S_OK;
}
