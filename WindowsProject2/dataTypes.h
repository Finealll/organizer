#pragma once
#include <Windows.h>

struct TaskToDo         //Одно задание
{
    wchar_t name[256];           //Название
    wchar_t description[1024];        //Текст задачи
    SYSTEMTIME date;                //Время выполнения
};


struct Alarm            //Один будильник
{
    wchar_t name[32];           //Название
    SYSTEMTIME time;                //Время выполнения
    HANDLE thread;               //Дескриптор потока
};


struct TaskToDoItem {       //Структура обертка для элемента списка задач
    TaskToDo task;
    bool isDeleted;         //Определяет удален элемент или нет
};


struct AlarmItem {          //Структура обертка для элемента списка будильников
    Alarm task;
    bool isDeleted;         //Определяет удален элемент или нет
};