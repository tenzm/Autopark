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

void split() {
    cout << LEFT_HORIZONTAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 2) << HORIZONTAL_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << HORIZONTAL_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << RIGHT_HORIZONTAL_SPLIT_CODE << endl;
}


void show_row(string id, string a, string b) {
    cout << VERTICAL_SPLIT_CODE << setfill(' ') << setw(CELL_WIDTH - 3) << id << VERTICAL_SPLIT_CODE
        << setw(CELL_WIDTH - 2) << a << VERTICAL_SPLIT_CODE << setw(CELL_WIDTH - 2) << b << VERTICAL_SPLIT_CODE << endl;
}

void show_header() {
    cout << TOP_LEFT_KORNER_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 2) << TOP_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << TOP_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << TOP_RIGHT_KORNER_CODE << endl;
    cout << VERTICAL_SPLIT_CODE << setfill(' ') << setw((CELL_WIDTH - 1) / 2) << "ID" << setfill(' ') << setw((CELL_WIDTH - 1) / 2 - CELL_WIDTH % 2)
        << VERTICAL_SPLIT_CODE << setfill(' ') << setw((CELL_WIDTH) / 2 + CELL_WIDTH % 2);
    setlocale(LC_ALL, "Russian");
    cout << "Имя";
    setlocale(LC_ALL, "C");
    cout << setfill(' ') << setw((CELL_WIDTH - 4) / 2 + 1)
        << VERTICAL_SPLIT_CODE << setfill(' ') << setw((CELL_WIDTH) / 2 + 2 + CELL_WIDTH % 2);
    setlocale(LC_ALL, "Russian");
    cout << "Фамилия";
    setlocale(LC_ALL, "C");
    cout << setfill(' ') << setw((CELL_WIDTH - 4) / 2 - 1) << VERTICAL_SPLIT_CODE << endl;
}

void show_footer() {
    cout << BOTTOM_LEFT_KORNER_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 2) << BOTTOM_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << BOTTOM_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << BOTTOM_RIGHT_KORNER_CODE << endl;
}



const string STAFF_TABLE_NAME = "STAFF";

void addStaff(sqlite3* db) {
    char* zErrMsg = 0;
    string firstname;
    string secondname;
    cout << "Введите имя водителя: ";
    cin >> firstname;
    cout << "Введите фамилию водителя: ";
    cin >> secondname;

    string sql = "INSERT INTO "+ STAFF_TABLE_NAME +" (firstname, secondname) VALUES ('" + firstname + "','" + secondname + "')";

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

static int staff_out_callback(void* data, int argc, char** argv, char** azColName) {
    split();
    show_row(argv[0], argv[1], argv[2]);
    return 0;
}

void getStaffList(sqlite3* db) {
    char* zErrMsg = 0;

    string sql = "SELECT * from " + STAFF_TABLE_NAME;

    /* Execute SQL statement */

    const char* data = "Callback function called";


    setlocale(LC_ALL, "C");
    cout << "\n";
    show_header(); // Печать шапки таблицы
    int rc = sqlite3_exec(db, sql.c_str(), staff_out_callback, NULL, &zErrMsg);
    show_footer();

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

}

void removeStaff(sqlite3* db) {
    getStaffList(db);
    char* zErrMsg = 0;
    string eid;
    setlocale(LC_ALL, "Russian");
    cout << "\nВведите id для удаления: ";
    cin >> eid;
    string sql = "DELETE from " + STAFF_TABLE_NAME + " WHERE id = " + eid;
    int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &zErrMsg);

    if (rc != SQLITE_OK) {
        cout << "Ошибка! Вы ввели неправильный id.";
    }
    else {
        setlocale(LC_ALL, "Russian");
        cout << "\nЗапись успешно удалена!";
    }
}