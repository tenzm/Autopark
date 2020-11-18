#include <iostream>
#include "sqlite3.h"
#include <string>
#include <iomanip>
#include <Staff.h>
#include <Bus.h>
#include <Route.h>

using namespace std;

const string DBName = "test.db";


void menu_output() {
    cout << " Меню:" << endl;
    cout << " 1. создать\n";
    cout << " 2. просмотр\n";
    cout << " 3. удалить\n";
    cout << " 4. назад\n";
    cout << " (2) Введите число от 1 до 4: ";
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
        cout << " Возвращение на предыдущую страницу...";
    }
    else {
        cout << " Ошибка!";
    }
    system("pause");
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
        cout << " Возвращение на предыдущую страницу...";
    }
    else {
        cout << " Ошибка!";
    }
    system("pause");
}

void route_actions(sqlite3* db) {
    menu_output();
    int edit_id;
    cin >> edit_id;
    system("cls");

    if (edit_id == 1) {
        addRoute(db);
    }
    else if (edit_id == 2) {
        getRouteList(db);
    }
    else if (edit_id == 3) {
        removeRoute(db);
    }
    else if (edit_id == 4) {
        cout << " Возвращение на предыдущую страницу...";
    }
    else {
        cout << " Ошибка!";
    }
    system("pause");
}



int main()
{

    sqlite3* db;
    int rc;

    rc = sqlite3_open(DBName.c_str(), &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    }

    while (true) {

        system("cls");
        setlocale(LC_ALL, "Russian");
        cout << " Информационная система поддержки работы автобусного парка.\n Меню:\n";
        cout << " 1. автобусы\n";
        cout << " 2. водители\n";
        cout << " 3. журнал рейсов\n";
        cout << " 4. выход\n";
        cout << " (1) Введите число от 1 до 4: ";

        char* zErrMsg = 0;
        int menu_id;
        cin >> menu_id;
        system("cls");
        switch (menu_id) {
        case 1:
            cout << " Автобусы" << endl;
            bus_actions(db);
            break;
        case 2:
            cout << " Водители" << endl;
            staff_actions(db);
            break;
        case 3: 
            cout << " Рейсы" << endl;
            route_actions(db);
            break;
        case 4: cout << " ВЫХОД...";
            return 0;
        default: cout << "Ошибка!";
            return 1;
        }
    }
    
    


    

    sqlite3_close(db);
}