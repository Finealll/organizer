#ifndef GLOBAL_H
#define GLOBAL_H

#pragma comment(lib,"Comctl32.lib")		//���������� ���������� ��� ������ � ��������� Winapi
#pragma comment(lib, "Winmm.lib")


#include <windows.h>		//���������� ���������� ��� ������ � ��������� Winapi	
#include <tchar.h>
#include <strsafe.h>
#include <Commctrl.h>
#include <windowsx.h>
#include <vector>
#include <fstream>

#include "Resource.h"		//��������� ����� ��� ������ � ���������

using namespace std;		//����� std

//������� id ���� ����
//������� ���������
#define IDC_CALENAR_BODY 10				//���������
//������� ToDo �����
#define IDC_TODO_LIST 20				//�������� ����� 
#define IDC_TODO_EDIT 21				//Edit ��� ������ ������ �����
#define IDC_TODO_ADDTASK 22				//������ ���������� ������
#define IDC_TODO_DELETETASK 23			//������ �������� ������
#define IDC_TODO_EDITTASK 24			//������ �������������� ������
//������� �����������
#define IDC_ALARM_LIST 31				//�������� ����������� 
#define IDC_ALARM_ADD 32				//������ ���������� ���������� 
#define IDC_ALARM_DELETE 33				//������ �������� ���������� 

#define TABS 3							//���������� �������



HINSTANCE g_hInst;      //���������� hInst
//����������� ����
HWND hMain;				//���������� �������� ����

HWND hTabControl;        //���������� ����������� ����

HWND hCalendar;			//���������� ���������

HWND hToDoList;				//���������� ����� ToDo
HWND hToDoInfo;				//���������� ���� ���������� �����
HWND hToDoAdd;				//���������� ������ ���������� �����
HWND hToDoDelete;			//���������� ������ �������� �����
HWND hToDoEdit;				//���������� ��������� �����

HWND hAlarmList;				//���������� ����� Alarm
HWND hAlarmAdd;				//���������� ������ ���������� ����������
HWND hAlarmDelete;				//���������� ������ �������� ����������




#endif GLOBAL_H