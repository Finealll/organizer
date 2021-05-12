#ifndef UNICODE
#define UNICODE
#endif 
#pragma comment(lib,"Comctl32.lib") //Подключаем библиотеки для работы с функциями Winapi
#pragma comment(lib, "Winmm.lib")


#include "Global.h" //Подключаем глобальный хедер

#include "dataTypes.h"      //Подключаем собственные хедеры для работы с нашими функциями
#include "OnSizes.h"
#include "TabController.h"
#include "CalendarController.h"
#include "ToDOController.h"
#include "AlarmController.h"

//Оконные функции
//Обработка сообщений главного окна
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
//Обработка сообщений диалога добавления задачи
LRESULT CALLBACK ToDoAddDialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
//Обработка сообщений диалога изменения задачи
LRESULT CALLBACK ToDoEditDialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
//Обработка сообщений диалога добавления будильника
LRESULT CALLBACK AlarmAddDialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Объявление функции работы будильника
void StartAlarm(int* args);

//Функция скрывает контролы всех вкладок
void HideAll() {
    HideCalendar();
    HideToDo();
    HideAlarm();
}


std::vector<TaskToDoItem> Tasks;	//Список задач
std::vector<AlarmItem> Alarms;	//Список будильников

//Точка входа в приложение
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    g_hInst = hInstance;        //Присваиваем нашему g_inst инстанс приложения (уникальный id)
    LPCWSTR CLASS_NAME = L"Organizer Class Name";   //Придумываем уникальное имя класса окна
    WNDCLASS wc = { };      //Создаем структуру определяющую окно

    wc.lpfnWndProc = WindowProc;    //Прописываем оконную функцию
    wc.hInstance = hInstance;    //Прописываем оконную инстанс
    wc.lpszClassName = CLASS_NAME;      //Прописываем созданное имя класса

    RegisterClass(&wc);     //Регистрируем класс окна

    HWND hwnd = CreateWindowEx(         //Создаем окно
        0,                              // Разные стили, которые я не заюзал.
        CLASS_NAME,                     // Класс нашего окна
        L"Органайзер",    // Заголовок окна
        WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS,            // Стили окна
        CW_USEDEFAULT, CW_USEDEFAULT, 600, 600,         // Размер и позиция
        NULL,       // Родительское окно    
        NULL,       // ID меню
        hInstance,  // Инстанс
        NULL        // Дополнительные данные в виде структуры CREATESTRUCT, которые бы передавались в lParam при WM_CREATE
    );
    hMain = hwnd;       //Инициализируем дескриптор нашего главного окна

    if (hwnd == NULL)
    {
        return 0;
    }


    ShowWindow(hwnd, nCmdShow);     //Показываем окно


    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))        //Запускаем цикл сообщений
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}



//Обработка сообщений главного окна
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)      
{
    int wmId, wmEvent;          //Для WM_COMMAND
    switch (msg)
    {
    case WM_CREATE: {       //Событие создания окна. Появляется только 1 раз при создании окна
        DoCreateTabControl(hwnd);     //Создаем табы

        CreateCalendarControls(hwnd);      //Для окна с календарем создаем его контролы
        CreateToDoControls(hwnd);           //Создаем контролы todo листа
        CreateAlarmControls(hwnd);           //Создаем контролы будильников

        //Читаем данные ToDO листа из бинарника
        fstream f1("data.bin");
        if (!f1.is_open()) { // если файла нет
            f1.open("data.bin", ios::binary | ios::in | ios::out | ios::trunc); //Создаем его
        }
        else {  //Если есть
            f1.close();
            f1.open("data.bin", ios::binary | ios::in);
            int pos;
            while (!f1.eof()) {     //Читаем данные до конца файла
                TaskToDo t;         //Структура задачи
                TaskToDoItem ti;    //Структура обертки
                f1.read((char*)&t, sizeof(t));  //Читаем сразу в структуру задачи

                ti.task = t;        //Инициализируем обертку
                ti.isDeleted = false;       
                Tasks.push_back(ti);        //Пушим в список наших задач
                pos = (int)SendMessage(hToDoList, LB_ADDSTRING, 0, (LPARAM)t.name);     //Добавляем строку в ListBox на вкдадке с задачами
                SendMessage(hToDoList, LB_SETITEMDATA, pos, (LPARAM)(Tasks.size() - 1));        //Добавляем этой строке данные - индекс элемента в списке
            }
            Tasks.pop_back();       //Удаляем последний элемент из списка и последнюю добавленную строку
            SendMessage(hToDoList, LB_DELETESTRING, pos, 0);//Зачем? !eof() сработает только на следующей итерации после конца файла -> мы добавили пустые данные
        }
        f1.close();     //Закрываем поток



        //Заполняем массив тестовыми данными
        /*SYSTEMTIME st;
        GetLocalTime(&st);
        for (int i = 0; i < 15; i++) {
            TaskToDo t1;
            t1.name = L"Task";
            t1.description = L"Descr";
            t1.date = st;
            Tasks.push_back(t1);
        }
        for (int i = 0; i < Tasks.size(); i++)
        {
            SendMessage(hToDoList, LB_ADDSTRING, 0, (LPARAM)Tasks[i].name);
        }*/

        ShowCalendar();     //Показываем контролы календаря как первое окно при открытии


        return 0;
    }

    case WM_SIZE:       //WM_SIZE - прилетает при изменении размеров окна
        OnSizeTabController(lParam);        //Вызываем функции ресайза всех контролов в нашей проге. Можно было бы хранить текущий таб и ресайзить только его контролы, но их у нас в целом мало, так что ничего страшного
        OnSizeCalendar(lParam);
        OnSizeToDoList(lParam);
        OnSizeAlarms(lParam);
        
        return 0;

    case WM_COMMAND:            //WM_COMMAND - прилетает когда произошло какое либо действие. Например нажатие кнопки
        wmId = LOWORD(wParam);      //Id окна, вызвавшее событие
        wmEvent = HIWORD(wParam);       //Id события
        int lbItem, i;
        switch (wmId)
        {
        //Окно ToDo листа
        //Нажатие на кнопку добавления задачи
        case IDC_TODO_ADDTASK:
            //Вызываем диалог добавления задачи
            DialogBox(g_hInst, (LPCTSTR)IDD_ADD_TODO_DIALOG, hwnd, (DLGPROC)ToDoAddDialogProc);
            return 0;
        //Нажатие на кнопку удаления задачи
        case IDC_TODO_DELETETASK:
            // Получаем индекс текущего выделенного элемента
            lbItem = (int)SendMessage(hToDoList, LB_GETCURSEL, 0, 0);
            //Если ни один элемент не выбран - ничего не делаем, бибикаем
            if (lbItem == -1) {
                MessageBeep(MB_ICONERROR);
                return 0;
            }
            // Получаем данные элемента
            i = (int)SendMessage(hToDoList, LB_GETITEMDATA, lbItem, 0);
            Tasks[i].isDeleted = true;      //Помечаем элемент на удаление
            SendMessage(hToDoList, LB_DELETESTRING, lbItem, 0);     //Удаляем строку с элементом из листбокса
            SendMessage(hToDoInfo, WM_SETTEXT, 0, (LPARAM)L"");     //Стираем его данные из едитбокса
            return 0;
        //Нажатие на кнопку изменения задачи
        case IDC_TODO_EDITTASK:
            // Получаем индекс текущего выделенного элемента
            lbItem = (int)SendMessage(hToDoList, LB_GETCURSEL, 0, 0);
            //Если ни один элемент не выбран - ничего не делаем, бибикаем
            if (lbItem == -1) {
                MessageBeep(MB_ICONERROR);
                return 0;
            }
            // Получаем данные элемента
            i = (int)SendMessage(hToDoList, LB_GETITEMDATA, lbItem, 0);
            //Открываем диалог изменения элемента, передаем в него индекс элемента в списке
            DialogBoxParam(g_hInst, (LPCTSTR)IDD_ADD_TODO_DIALOG, hwnd, (DLGPROC)ToDoEditDialogProc, (LPARAM)i);
            //Удаляем старую строку из листбокса, очищаем едитбокс, добавляем новую строку и ставим ее данные в едитбокс
            SendMessage(hToDoList, LB_DELETESTRING, lbItem, 0);
            SendMessage(hToDoInfo, WM_SETTEXT, 0, (LPARAM)L"");
            lbItem = (int)SendMessage(hToDoList, LB_ADDSTRING, 0, (LPARAM)Tasks[i].task.name);
            SendMessage(hToDoList, LB_SETITEMDATA, lbItem, i);
            return 0;
            //События нажатия в область листбокса
        case IDC_TODO_LIST:
            switch (wmEvent)
            {
            case LBN_SELCHANGE:     //Выделение элемента в списке
                // Получаем индекс текущего выделенного элемента
                int lbItem = (int)SendMessage(hToDoList, LB_GETCURSEL, 0, 0);
                // Получаем данные элемента
                int i = (int)SendMessage(hToDoList, LB_GETITEMDATA, lbItem, 0);
                // Получаем данные по элементу из массива
                TCHAR buff[MAX_PATH];
                StringCbPrintf(buff, ARRAYSIZE(buff),
                    L"Дата: %d/%d/%d %d:%d:%d\r\nНазвание: %s\r\nТекст:\r\n%s\r\n",
                    Tasks[i].task.date.wDay, Tasks[i].task.date.wMonth, Tasks[i].task.date.wYear,
                    Tasks[i].task.date.wHour, Tasks[i].task.date.wMinute, Tasks[i].task.date.wSecond,
                    Tasks[i].task.name, Tasks[i].task.description);
                //Заполняем этими данными едитбокс
                SendMessage(hToDoInfo, WM_SETTEXT, 0, (LPARAM)buff);

                return 0;
            }
            break;

        //Окно Будильников
        //Нажатие на кнопку добавления будильника
        case IDC_ALARM_ADD:
            //Вызываем диалог с добавлением будильника
            DialogBox(g_hInst, (LPCTSTR)IDD_ADD_ALARM_DIALOG, hwnd, (DLGPROC)AlarmAddDialogProc);
            return 0;
        //Нажатие на кнопку удаления будильника
        case IDC_ALARM_DELETE:
            // Получаем индекс текущего выделенного элемента
            lbItem = (int)SendMessage(hAlarmList, LB_GETCURSEL, 0, 0);
            //Если ни один элемент не выбран - ничего не делаем, бибикаем
            if (lbItem == -1) {
                MessageBeep(MB_ICONERROR);
                return 0;
            }
            // Получаем данные элемента
            i = (int)SendMessage(hAlarmList, LB_GETITEMDATA, lbItem, 0);

            TerminateThread(Alarms[i].task.thread, 0);       //Завершаем поток текущего будильника
            Alarms[i].isDeleted = true;                     //Помечаем будильник на удаление
            SendMessage(hAlarmList, LB_DELETESTRING, lbItem, 0);    //Удаляем строку будильника из листбокса
            PlaySound(NULL, NULL, 0);           //Останавливаем воспроизведение любой мелодии на данный момент
            
            return 0;

        }


        break;
    

    case WM_NOTIFY:     //WM_NOTIFY в нашей программе прилетает с элемента управления вкладками, так же может прилетать с календаря и тп
        
        switch(((LPNMHDR)lParam)->code) { 
        
        case TCN_SELCHANGING:
            return false;       //Разрешаем изменение вкладок

        case TCN_SELCHANGE:     //Нажатие на вкладку
            HideAll();          //Скрываем все элементы на всех вкладках
            switch (TabCtrl_GetCurSel(hTabControl))     // Получаем номер нажатой вкладки
            {       //В зависимости от которого открываем контролы нужной нам вкладки
            case 0:
                ShowCalendar();
                return 0;
            case 1:
                ShowToDo();
                return 0;
            case 2:
                ShowAlarm();
                return 0;
            default:
                ShowCalendar();
                return 0;
            }

        }
        break;


    case WM_DESTROY: {      //Событие прилетает при закрытии окна программы
        ofstream f1("data.bin", ios::binary | ios::out | ios::trunc);       //Записываем данные из списка задач в бинарник
        for (int i = 0; i < Tasks.size(); i++) {
            if(!Tasks[i].isDeleted)         //Записываем только те, которые не удалены
                f1.write((char*)&Tasks[i].task, sizeof(Tasks[i].task));
        }
        f1.close();

        PostQuitMessage(0);     //Посылаем сообщение о выходе
        return 0;
    }

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);        //Для любых других событий вызываем стандартную процедуру обработки сообщений Windows
}


//Обработка сообщений диалога добавления задачи
LRESULT CALLBACK ToDoAddDialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    int wmId, wmEvent;          //Для WM_COMMAND

    switch (msg)
    {
    case WM_INITDIALOG:{ //инициализация диалога
        HWND name = GetDlgItem(hwnd, IDC_NAME_ADD);     //Получаем дескрипторы едитбоксов названия и описания
        HWND description = GetDlgItem(hwnd, IDC_DESCRIPTION_ADD);
        SendMessage(name, EM_SETLIMITTEXT, 256, 0);         //Устанавливаем ограничение на максимальный ввод символов
        SendMessage(description, EM_SETLIMITTEXT, 1024, 0);

        return 0;
    }

    case WM_COMMAND:  
        wmId = LOWORD(wParam);      //ID элемента диалога
        wmEvent = HIWORD(wParam);   //Комманда

        switch (wmId)
        {
        case IDC_BUTTON_ADD: //Нажатие кнопки Добавить
            wchar_t name[256];      //Под имя
            wchar_t description[1024];      //Под описание задачи
            GetDlgItemText(hwnd, IDC_NAME_ADD, name, 256);  //Получаем текст элеменов из едитбоксов
            GetDlgItemText(hwnd, IDC_DESCRIPTION_ADD, description, 1024);
            //Получаем дескрипторы датапикеров
            HWND dtpDate = GetDlgItem(hwnd, IDC_DATE_ADD);
            HWND dtpHours = GetDlgItem(hwnd, IDC_TIME_ADD);
            //Подготавливаем структуры SYSTEMTIME для извлечения времени
            SYSTEMTIME st;
            SYSTEMTIME st1;
            //Извлекаем дату и время из датапикеров
            SendMessage(dtpDate, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
            SendMessage(dtpHours, DTM_GETSYSTEMTIME, 0, (LPARAM)&st1);
            //Добавляем в первую структуру данные из 2й
            st.wHour = st1.wHour;
            st.wMinute = st1.wMinute;
            st.wSecond = st1.wSecond;
            
            //Создаем структуры задачи и обертки под нее
            TaskToDo t1;
            TaskToDoItem t;
            //Копируем данные имени и описания задачи в структуру задачи
            memcpy(t1.name, name, 256);
            memcpy(t1.description, description, 1024);
            t1.date = st;   //Присваиваем данные о дате и времени задачи
            //Инициализируем обертку
            t.task = t1;
            t.isDeleted = false;
            //Заносим данные в список
            Tasks.push_back(t);
            //Добавляем название задачи в листбокс и назначаем ему данные - индекс элемента в массиве
            int pos = (int)SendMessage(hToDoList, LB_ADDSTRING, 0, (LPARAM)name);
            SendMessage(hToDoList, LB_SETITEMDATA, pos, (LPARAM)(Tasks.size()-1));
            
            EndDialog(hwnd, 0); //Выходим и диалога
            return 0;
        }
        break;

    case WM_DESTROY:        //При клике на крестик выходим из диалога без сохранения
        EndDialog(hwnd, 0);
        return TRUE;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);   //Для любых других событий вызываем стандартную процедуру обработки сообщений Windows
}



//Обработка сообщений диалога изменения задачи
LRESULT CALLBACK ToDoEditDialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    int wmId, wmEvent;          //Для WM_COMMAND
    static int index;           //Индекс элемента в массиве, статическая переменная, получем его из lParam при событии WM_CREATE, т.к. мы его туда передавали

    switch (msg)
    {
    case WM_INITDIALOG: {   //Для это диалога будем использовать диалог добавления задачи, но поменяем в нем некоторые данные
        HWND name = GetDlgItem(hwnd, IDC_NAME_ADD);     //Получим дескрипторы окон имени, описания, датапикеров, кнопки
        HWND description = GetDlgItem(hwnd, IDC_DESCRIPTION_ADD);
        HWND dtpDate = GetDlgItem(hwnd, IDC_DATE_ADD);
        HWND dtpTime = GetDlgItem(hwnd, IDC_TIME_ADD);
        HWND button = GetDlgItem(hwnd, IDC_BUTTON_ADD);
        SendMessage(name, WM_SETTEXT, 0, (LPARAM)Tasks[lParam].task.name);      //Подставим в полученные дескрипторы значения из списка структур для изменяемой структуры
        SendMessage(description, WM_SETTEXT, 0, (LPARAM)Tasks[lParam].task.description);
        SendMessage(dtpDate, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&Tasks[lParam].task.date);
        SendMessage(dtpTime, DTM_SETSYSTEMTIME, GDT_VALID, (LPARAM)&Tasks[lParam].task.date);
        SendMessage(name, EM_SETLIMITTEXT, 256, 0);     //Выставим ограничение на ввод символов для даты и описания
        SendMessage(description, EM_SETLIMITTEXT, 1024, 0);
        SetWindowText(button, L"Изменить");     //Изменим текст кнопки добавить на изменить
        SetWindowText(hwnd, L"Изменение задачи");       //Изменим заголовок окна на изменение задачи
        index = lParam;     //Присваиваем индекс нашей задачи
        return 0;
    }

    case WM_COMMAND:
        wmId = LOWORD(wParam);      //ID элемента диалога
        wmEvent = HIWORD(wParam);   //Команда
        switch (wmId)
        {
        case IDC_BUTTON_ADD: //Нажатие кнопки Изменить
            wchar_t name[256];      //Буфер под имя
            wchar_t description[1024];      //Буфер под описание задачи
            GetDlgItemText(hwnd, IDC_NAME_ADD, name, 256);      //Получаем данные имени и описния из наших текстбоксов
            GetDlgItemText(hwnd, IDC_DESCRIPTION_ADD, description, 1024);
            //Получаем дескрипторы датапикеров
            HWND dtpDate = GetDlgItem(hwnd, IDC_DATE_ADD);  
            HWND dtpHours = GetDlgItem(hwnd, IDC_TIME_ADD);
            //Подготавливаем структуры SYSTEMTIME для извлечения времени
            SYSTEMTIME st;
            SYSTEMTIME st1;
            //Извлекаем дату и время из датапикеров
            SendMessage(dtpDate, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
            SendMessage(dtpHours, DTM_GETSYSTEMTIME, 0, (LPARAM)&st1);
            //Добавляем в первую структуру данные из 2й
            st.wHour = st1.wHour;
            st.wMinute = st1.wMinute;
            st.wSecond = st1.wSecond;
            //Копируем данные имени и описания задачи в структуру задачи
            memcpy(Tasks[index].task.name, name, 256);
            memcpy(Tasks[index].task.description, description, 1024);
            //Присваиваем данные о дате и времени задачи
            Tasks[index].task.date = st;


            EndDialog(hwnd, 0);     //Выходим из диалога
            return 0;
        }
        break;

    case WM_DESTROY:        //При клике на крестик выходим из диалога без сохранения
        EndDialog(hwnd, 0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);  //Для любых других событий вызываем стандартную процедуру обработки сообщений Windows
}


//Обработка сообщений диалога добавления будильника
LRESULT CALLBACK AlarmAddDialogProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    int wmId, wmEvent;          //Для WM_COMMAND

    switch (msg)
    {
    case WM_INITDIALOG: {           //При создании диалога
        HWND name = GetDlgItem(hwnd, IDC_ALARM_NAME);   //Получим дескриптор нашего инпута названия будильника
        SendMessage(name, EM_SETLIMITTEXT, 32, 0);      //Зададим максимальное количество символов
        return 0;
    }

    case WM_COMMAND:    
        wmId = LOWORD(wParam);      //ID элемента диалога
        wmEvent = HIWORD(wParam);   //Команда
        switch (wmId)
        {
        case IDC_ALARM_BUTTON: //Нажатие кнопки Добавить
            wchar_t name[32];      //Буфер под название
            GetDlgItemText(hwnd, IDC_ALARM_NAME, name, 32);     //Получаем название будильника из нашего едитбокса
            //Получаем дескриптор датапикеров
            HWND dtpHours = GetDlgItem(hwnd, IDC_ALARM_TIMEPICKER);
            //Подготавливаем структуру SYSTEMTIME для извлечения времени
            SYSTEMTIME st;
            //Присваиваем данные о времени будильника
            SendMessage(dtpHours, DTM_GETSYSTEMTIME, 0, (LPARAM)&st);
            //Создаем структуру будильника и обертки
            Alarm al;
            AlarmItem ali;
            //Инициаизируем структуру будильника, копируем данные о времени и присваиваем данные о времени полям нашей структуры
            memcpy(al.name, name, 32);
            al.time = st;
            //Инициализируем структуру обертку
            ali.task = al;
            ali.isDeleted = false;
            //Добавляем наш буддильник в список
            Alarms.push_back(ali);
            //Подгатавливаем отображаемую в листбоксе строку для нашего будильника
            TCHAR buff[MAX_PATH];
            StringCbPrintf(buff, ARRAYSIZE(buff),   //Форматируем ее из наших данных
                L"%d:%d:%d   %s",
                st.wHour, st.wMinute, st.wSecond, name);
            //Добавляем название будильника в листбокс и назначаем ему данные - индекс элемента в массиве
            int pos = (int)SendMessage(hAlarmList, LB_ADDSTRING, 0, (LPARAM)buff);
            SendMessage(hAlarmList, LB_SETITEMDATA, pos, (LPARAM)Alarms.size() - 1);
            //Подгатавливаем данные для создания нового потока с будильником
            SYSTEMTIME now;         //Будет хранить текущее время
            int nowMseconds, stMseconds;   //Будут хранить данные в милисекундах
            GetLocalTime(&now);     //Инициализируем структуру текущим временем
            //Высчитываем количество миллисекунд для текущего и заданного времени
            nowMseconds = now.wHour * 3600000 + now.wMinute + 60000 + now.wSecond * 1000;
            stMseconds = st.wHour * 3600000 + st.wMinute + 60000 + st.wSecond * 1000;
            //Массив для передаче функции будильника
            int arr[2];
            arr[0] = Alarms.size() - 1;     //Первый элемент - индекс будильника в массиве
            //Второй - в зависимости от того, раньше или позже будильник от настоящего времени
            if (nowMseconds < stMseconds)   //Если позже, то просто вычтем из будущего текущее
                arr[1] = stMseconds - nowMseconds;
            else        //Иначе добавим сутки
                arr[1] = stMseconds + 24 * 3600000 - nowMseconds;
            //Создадим новый поток с функцией StartAlarm, передадим в нее указатель на массив arr
            HANDLE t = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAlarm, (LPVOID)arr, 0, 0);
            //Handle потока сохраним в структуре нашего будильника. Он пригодится для завершения потока, если мы захотим удалить будильник
            Alarms[Alarms.size() - 1].task.thread = t;

            EndDialog(hwnd, 0);     //Выходим из диалога
            return 0;
        }
        break;

    case WM_DESTROY:         //При клике на крестик выходим из диалога без сохранения
        EndDialog(hwnd, 0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);   //Для любых других событий вызываем стандартную процедуру обработки сообщений Windows
}


//Запуск будильника
void StartAlarm(int* args) {
    int pos = args[0];           //Извлекаем позицию будильника в массиве
    int mSeconds = args[1];      //Извлекаем количество миллисекунд до срабатывания будильника
    //Имя и время будильника - строка как в его названии
    TCHAR buff[MAX_PATH];
    StringCbPrintf(buff, ARRAYSIZE(buff),
        L"%d:%d:%d   %s\0",
        Alarms[pos].task.time.wHour, Alarms[pos].task.time.wMinute,
        Alarms[pos].task.time.wSecond, Alarms[pos].task.name);

    Sleep(mSeconds);        //Останавливаем поток на заданное количество миллисекунд
    //После воспроизводим мелодию из ресурсов. Делаем ее асинхронной и зациклененой
    PlaySound(MAKEINTRESOURCE(IDR_WAVE2), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC |SND_LOOP);
    //Выдаем MessageBox с названием и временем будильника
    MessageBox(NULL, buff, L"Будильник", 0);
    //После закрытия останавливаем мелодию
    PlaySound(NULL, NULL, 0);

    //Удаляем элемент
    //Находим индекс элемента в листбоксе по строке
    int index = SendMessage(hAlarmList, LB_FINDSTRING, -1, (LPARAM)buff);
    if (index != LB_ERR)        //Если индекс есть, то удаляем строку
        SendMessage(hAlarmList, LB_DELETESTRING, index, 0);
    Alarms[pos].isDeleted = true;       //Помечаем элемент удаленным
}