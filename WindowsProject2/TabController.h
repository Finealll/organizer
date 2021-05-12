#pragma once
#include "Global.h"



//������� ������� � ���������� ���������� ���� �����
HWND DoCreateTabControl(HWND hwndParent)
{
    TCITEM tie;         //���������, ����������� �������
    int i;
    TCHAR buff[256];    //������ ��� ������     

    hTabControl = CreateWindow(WC_TABCONTROL, L"",      //�������������� ���������� ���� ���������
        WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE,
        0, 0, 0, 0, hwndParent, NULL, g_hInst, NULL);


    // ��������� ���� � ����
    tie.mask = TCIF_TEXT;
    tie.iImage = -1;
    tie.pszText = buff;

    for (i = 0; i < TABS; i++)          //��������� ����� ������� �� �������� � ������� ��
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





