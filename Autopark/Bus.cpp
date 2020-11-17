﻿#include <iostream>
#include <string>
#include <sqlite3.h>
#include <iomanip>

using namespace std;

using namespace std;

const int CELL_WIDTH = 21; // Ширина ячейки таблицы

const char TOP_LEFT_KORNER_CODE = (char)218; // Символ верхнего левого угла "┌"
const char TOP_RIGHT_KORNER_CODE = (char)191; // Символ верхнего правого угла "┐"
const char BOTTOM_RIGHT_KORNER_CODE = (char)217; // Символ нижнего правого угла "┘"
const char BOTTOM_LEFT_KORNER_CODE = (char)192; // Символ нижнего левого угла "└"
const char TOP_VERTICAL_SPLIT_CODE = (char)194; // Символ разделителя двух столбцов с верхней границей "┬"
const char BOTTOM_VERTICAL_SPLIT_CODE = (char)193; // Символ разделителя двух столбцов с нижней границей "┴"
const char LEFT_HORIZONTAL_SPLIT_CODE = (char)195; // Символ разделителя двух строк с левой границей "├"
const char RIGHT_HORIZONTAL_SPLIT_CODE = (char)180; // Символ разделителя двух строк с правой границей "┤"
const char HORIZONTAL_VERTICAL_SPLIT_CODE = (char)197; // Символ разделителя строки и столбца "┼"
const char HORIZONTAL_SPLIT_CODE = (char)196; // Символ разделителя двух строк "─"
const char VERTICAL_SPLIT_CODE = (char)179; // Символ разделителя столбцов "│"

void bus_split() {
    cout << LEFT_HORIZONTAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 2) << HORIZONTAL_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << RIGHT_HORIZONTAL_SPLIT_CODE << endl;
}


void bus_show_row(string id, string a) {
    cout << VERTICAL_SPLIT_CODE << setfill(' ') << setw(CELL_WIDTH - 3) << id << VERTICAL_SPLIT_CODE
        << setw(CELL_WIDTH - 2) << a << VERTICAL_SPLIT_CODE << endl;
}

void bus_show_header() {
    cout << TOP_LEFT_KORNER_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 2) << TOP_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << TOP_RIGHT_KORNER_CODE << endl;
    cout << VERTICAL_SPLIT_CODE << setfill(' ') << setw((CELL_WIDTH - 1) / 2) << "ID" << setfill(' ') << setw((CELL_WIDTH - 1) / 2 - CELL_WIDTH % 2)
        << VERTICAL_SPLIT_CODE << setfill(' ') << setw((CELL_WIDTH) / 2 + 4 + CELL_WIDTH % 2);
    setlocale(LC_ALL, "Russian");
    cout << "Гос. номер";
    setlocale(LC_ALL, "C");
    cout << setfill(' ') << setw((CELL_WIDTH - 4) / 2 -3)
        << VERTICAL_SPLIT_CODE << endl;
}

void bus_show_footer() {
    cout << BOTTOM_LEFT_KORNER_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 2) << BOTTOM_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << BOTTOM_RIGHT_KORNER_CODE << endl;
}



const string BUSES_TABLE_NAME = "BUSES";

void addBus(sqlite3* db) {
    char* zErrMsg = 0;
    string car_number;
    cout << "Введите гос. номер автомобиля: ";
    cin >> car_number;

    string sql = "INSERT INTO " + BUSES_TABLE_NAME + " (car_number) VALUES ('"+car_number+"')";

    setlocale(LC_ALL, "C");
    cout << "\n";
    int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &zErrMsg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else {
        setlocale(LC_ALL, "Russian");
        cout << "\nЗапись успешно добавлена!";
    }
}

static int bus_out_callback(void* data, int argc, char** argv, char** azColName) {
    bus_split();
    bus_show_row(argv[0], argv[1]);
    return 0;
}

void getBusesList(sqlite3* db) {
    char* zErrMsg = 0;

    string sql = "SELECT * from " + BUSES_TABLE_NAME;

    /* Execute SQL statement */

    const char* data = "Callback function called";


    setlocale(LC_ALL, "C");
    cout << "\n";
    bus_show_header(); // Печать шапки таблицы
    int rc = sqlite3_exec(db, sql.c_str(), bus_out_callback, NULL, &zErrMsg);
    bus_show_footer();

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

}

void removeBus(sqlite3* db) {
    getBusesList(db);
    char* zErrMsg = 0;
    string eid;
    setlocale(LC_ALL, "Russian");
    cout << "\nВведите id для удаления: ";
    cin >> eid;
    string sql = "DELETE from " + BUSES_TABLE_NAME + " WHERE id = " + eid;
    int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &zErrMsg);

    if (rc != SQLITE_OK) {
        cout << "Ошибка! Вы ввели неправильный id.";
    }
    else {
        setlocale(LC_ALL, "Russian");
        cout << "\nЗапись успешно удалена!";
    }
}