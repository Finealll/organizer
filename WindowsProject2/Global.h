#ifndef GLOBAL_H
#define GLOBAL_H

#pragma comment(lib,"Comctl32.lib")		//Подключаем библиотеки для работы с функциями Winapi
#pragma comment(lib, "Winmm.lib")


#include <windows.h>		//Подключаем библиотеки для работы с функциями Winapi	
#include <tchar.h>
#include <strsafe.h>
#include <Commctrl.h>
#include <windowsx.h>
#include <vector>
#include <fstream>

#include "Resource.h"		//Поключаем хедер для работы с ресурсами

using namespace std;		//Юзаем std

//Дефайны id моих окон
//Вкладка календаря
#define IDC_CALENAR_BODY 10				//Календарь
//Вкладка ToDo листа
#define IDC_TODO_LIST 20				//Листбокс задач 
#define IDC_TODO_EDIT 21				//Edit для вывода текста задач
#define IDC_TODO_ADDTASK 22				//Кнопка добавления задачи
#define IDC_TODO_DELETETASK 23			//Кнопка удаления задачи
#define IDC_TODO_EDITTASK 24			//Кнопка редактирования задачи
//Вкладка будильников
#define IDC_ALARM_LIST 31				//Листбокс будильников 
#define IDC_ALARM_ADD 32				//Кнопка добавления будильиков 
#define IDC_ALARM_DELETE 33				//Кнопка удаления будильиков 

#define TABS 3							//Количество вкладок



HINSTANCE g_hInst;      //Глобальный hInst
//Дескрипторы окон
HWND hMain;				//Дескриптор главного окна

HWND hTabControl;        //Дескриптор внутреннего окна

HWND hCalendar;			//Дескриптор календаря

HWND hToDoList;				//Дескриптор листа ToDo
HWND hToDoInfo;				//Дескриптор окна информации таска
HWND hToDoAdd;				//Дескриптор кнопки добавления таска
HWND hToDoDelete;			//Дескриптор кнопки удаления таска
HWND hToDoEdit;				//Дескриптор изменения таска

HWND hAlarmList;				//Дескриптор листа Alarm
HWND hAlarmAdd;				//Дескриптор кнопки добавления будильника
HWND hAlarmDelete;				//Дескриптор кнопки удаления будильника




#endif GLOBAL_H