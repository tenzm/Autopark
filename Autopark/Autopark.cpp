#include <iostream>
#include "sqlite3.h"
#include <string>
#include <iomanip>
#include <Staff.h>
#include <fstream>
#include <Bus.h>
#include <Route.h>

using namespace std;

const string DBName = "buspark.db";
const string CreateBus = "CREATE TABLE \"buses\" (\"id\" INTEGER UNIQUE, \"car_number\" TEXT, PRIMARY KEY(\"id\" AUTOINCREMENT))";
const string CreateStaff = "CREATE TABLE \"staff\" (\"id\" INTEGER UNIQUE, \"firstname\" TEXT, \"secondname\" TEXT, PRIMARY KEY(\"id\" AUTOINCREMENT))";
const string CreateRoutes = "CREATE TABLE \"routes\" (\"id\" INTEGER UNIQUE, \"staff_id\" TEXT, \"bus_id\" TEXT, \"departure_time\" TEXT, \"arrival_time\" TEXT, \"departure_place\" TEXT, \"arrival_place\" TEXT,  PRIMARY KEY(\"id\" AUTOINCREMENT))";

void menu_output() {
    cout << " Меню:" << endl;
    cout << " 1. создать\n";
    cout << " 2. просмотр\n";
    cout << " 3. удалить\n";
    cout << " 4. назад\n";
    cout << " (2) Введите число от 1 до 4: ";
}

void staff_actions(sqlite3 *db) { // Действия с водителями
    menu_output(); // Вывод подменю
    int edit_id;
    cin >> edit_id;
    system("cls");

    if (edit_id == 1) {
        addStaff(db); // Добавление водителя
    }
    else if (edit_id == 2) {
        getStaffList(db); // Получение списка водителей и его печать
    }
    else if (edit_id == 3) {
        removeStaff(db); // Удаление водителя из списка
    }
    else if (edit_id == 4) {
        cout << " Возвращение на предыдущую страницу...";
    }
    else {
        cout << " Ошибка!";
    }
    system("pause");
}


void bus_actions(sqlite3 *db) { // Действия с автобусами
    menu_output(); // Вывод подменю
    int edit_id;
    cin >> edit_id;
    system("cls");

    if (edit_id == 1) {
        addBus(db); // Добавление автобуса
    }
    else if (edit_id == 2) {
        getBusesList(db); // Получение списка автобусов и его вывод
    }
    else if (edit_id == 3) {
        removeBus(db); // Удаление автобуса из списка
    }
    else if (edit_id == 4) { // Возврат назад
        cout << " Возвращение на предыдущую страницу...";
    }
    else {
        cout << " Ошибка!";
    }
    system("pause");
}

void route_actions(sqlite3* db) { // Действия с маршрутами
    menu_output(); // Вывод подменю
    int edit_id;
    cin >> edit_id;
    system("cls");

    if (edit_id == 1) {
        addRoute(db); // ДОбавление маршрута
    }
    else if (edit_id == 2) {
        getRouteList(db); // Получение списка автобусов и их вывод
    }
    else if (edit_id == 3) {
        removeRoute(db); // Удаление списка автобусов
    }
    else if (edit_id == 4) { // Возврат назад
        cout << " Возвращение на предыдущую страницу...";
    }
    else {
        cout << " Ошибка!";
    }
    system("pause");
}

int main()
{
    setlocale(LC_ALL, "Russian");
    bool db_exist = true; // Наличие файла базы данных

    ifstream file(DBName);
    if (!file) { // Если база данных не найдена
        cout << "Здравствуйте! Для работы программы нужно создать базу данных. Хотите ли вы это сделать? (Y/n): ";
        string sup;
        cin >> sup;
        if (sup != "Y" && sup != "y") { // Предложение создать базу данных
            cout << "Выход из программы...\n";
            return 1; 
        }
        db_exist = false;
    }


    sqlite3* db;
    int rc;
    char* zErrMsg = 0;


    rc = sqlite3_open(DBName.c_str(), &db); // Открытие базы данных

    if (rc) { // Вывод ошибок БД
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db)); 
        return(0);
    }

    if (!db_exist) { // Если БД пустая, то создаем в ней таблицы
        sqlite3_exec(db, CreateBus.c_str(), NULL, NULL, &zErrMsg);
        sqlite3_exec(db, CreateStaff.c_str(), NULL, NULL, &zErrMsg);
        sqlite3_exec(db, CreateRoutes.c_str(), NULL, NULL, &zErrMsg);
        cout << "База данных " << DBName << " успешно создана!\n";
        system("pause");
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

        int menu_id;
        cin >> menu_id;
        system("cls");

        // Вывод главного меню
        switch (menu_id) {
        case 1:
            cout << " Автобусы" << endl;
            bus_actions(db); // Действия с автобусами
            break;
        case 2:
            cout << " Водители" << endl;
            staff_actions(db); // Действия с водителями
            break;
        case 3: 
            cout << " Рейсы" << endl;
            route_actions(db);  // Действия с рейсами
            break;
        case 4: cout << " ВЫХОД...";
            return 0;
        default: cout << "Ошибка!";
            return 1;
        }
    }
    
    sqlite3_close(db);
}