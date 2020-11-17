#include <iostream>
#include "sqlite3.h"
#include <string>
#include <iomanip>
#include <Staff.h>
#include <Bus.h>

using namespace std;

const string DBName = "test.db";


void menu_output() {
    cout << "Меню:" << endl;
    cout << "1. создать\n";
    cout << "2. просмотр\n";
    cout << "3. удалить\n";
    cout << "4. выход\n";
    cout << "(2) Введите число от 1 до 4: ";
}

void staff_actions(sqlite3 *db) {
    menu_output();
    int edit_id;
    cin >> edit_id;
    system("cls");

    if (edit_id == 1) {
        addStaff(db);
    }
    else if (edit_id == 2) {
        getStaffList(db);
    }
    else if (edit_id == 3) {
        removeStaff(db);
    }
    else if (edit_id == 4) {
        cout << " ВЫХОД...";
    }
    else {
        cout << "Ошибка!";
    }
}


void bus_actions(sqlite3 *db) {
    menu_output();
    int edit_id;
    cin >> edit_id;
    system("cls");

    if (edit_id == 1) {
        addBus(db);
    }
    else if (edit_id == 2) {
        getBusesList(db);
    }
    else if (edit_id == 3) {
        removeBus(db);
    }
    else if (edit_id == 4) {
        cout << " ВЫХОД...";
    }
    else {
        cout << "Ошибка!";
    }
}



int main()
{
    setlocale(LC_ALL, "Russian");

    sqlite3* db;
    int rc;

    rc = sqlite3_open(DBName.c_str(), &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }


    cout << "Информационная система поддержки работы автобусного парка.\nМеню:\n";
    cout << "1. автобусы\n";
    cout << "2. водители\n";
    cout << "3. журнал рейсов\n";
    cout << "4. выход\n";
    cout << "(1) Введите число от 1 до 4: ";

    char* zErrMsg = 0;
    int menu_id;
    cin >> menu_id;
    system("cls");
    switch (menu_id) {
    case 1: 
        cout << "Автобусы" << endl;
        bus_actions(db);
        break;
    case 2:
        cout << "Водители" << endl;
        staff_actions(db);
        break;
    case 3: cout << "Журнал рейсов" << endl;
        break;
    case 4: cout << "ВЫХОД...";
        return 0;
    default: cout << "Ошибка!";
        return 1;
    }
    
    


    

    sqlite3_close(db);
}