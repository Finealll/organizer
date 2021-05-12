#pragma once
#include <Windows.h>

struct TaskToDo         //���� �������
{
    wchar_t name[256];           //��������
    wchar_t description[1024];        //����� ������
    SYSTEMTIME date;                //����� ����������
};


struct Alarm            //���� ���������
{
    wchar_t name[32];           //��������
    SYSTEMTIME time;                //����� ����������
    HANDLE thread;               //���������� ������
};


struct TaskToDoItem {       //��������� ������� ��� �������� ������ �����
    TaskToDo task;
    bool isDeleted;         //���������� ������ ������� ��� ���
};


struct AlarmItem {          //��������� ������� ��� �������� ������ �����������
    Alarm task;
    bool isDeleted;         //���������� ������ ������� ��� ���
};