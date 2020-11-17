#include <iostream>
#include "sqlite3.h"
#include <string>
#include <iomanip>
#include <Staff.h>
#include <Output.h>

using namespace std;

const string DBName = "test.db";





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
    cout << "Введите число от 1 до 4: ";

    char* zErrMsg = 0;
    int menu_id;
    cin >> menu_id;
    system("cls");
    switch (menu_id) {
    case 1: cout << "Автобусы" << endl;
        break;
    case 2: cout << "Водители" << endl;
        break;
    case 3: cout << "Журнал рейсов" << endl;
        break;
    case 4: cout << "ВЫХОД...";
        return 0;
    default: cout << "Ошибка! Введите число от 1 до 4.";
        return 1;
    }
    cout << "Меню:" << endl;
    cout << "1. создать\n";
    cout << "2. просмотр\n";
    cout << "3. удалить\n";
    cout << "4. выход\n";
    cout << "Введите число от 1 до 4: ";
    int edit_id;
    cin >> edit_id;
        system("cls");


    if (edit_id == 1) {
        addStaff(db);
    }
    if (edit_id == 2) {
        getStaffList(db);
    }
    if (edit_id == 3) {
        removeStaff(db);
    }
    if (edit_id == 4) {
        cout << " ВЫХОД...";
        return 0;
    }
    

    sqlite3_close(db);
}