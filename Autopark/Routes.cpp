#include <iostream>
#include <string>
#include <sqlite3.h>
#include <iomanip>
#include <Bus.h>
#include <Staff.h>
#include <Format.h>
using namespace std;


const int CELL_WIDTH = 18; // Ширина ячейки таблицы

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

void route_split() {
    cout << LEFT_HORIZONTAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 2) << HORIZONTAL_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << HORIZONTAL_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << HORIZONTAL_VERTICAL_SPLIT_CODE;
    cout << HORIZONTAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 2) << HORIZONTAL_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << HORIZONTAL_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << HORIZONTAL_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << RIGHT_HORIZONTAL_SPLIT_CODE << endl;

}

void route_show_row(string id, string a, string b, string c, string d, string e, string f) {
    cout << VERTICAL_SPLIT_CODE << setfill(' ') << setw(CELL_WIDTH - 3) << cell_format(id, CELL_WIDTH) << VERTICAL_SPLIT_CODE
        << setw(CELL_WIDTH - 2) << cell_format(a, CELL_WIDTH) << VERTICAL_SPLIT_CODE << setw(CELL_WIDTH - 2) << cell_format(b, CELL_WIDTH) << VERTICAL_SPLIT_CODE;
    cout << " " << setfill(' ') << setw(CELL_WIDTH - 3) << cell_format(e, CELL_WIDTH) << VERTICAL_SPLIT_CODE
        << setw(CELL_WIDTH - 2) << cell_format(f, CELL_WIDTH) << VERTICAL_SPLIT_CODE;
    cout << " " << setfill(' ') << setw(CELL_WIDTH - 3) << cell_format(c, CELL_WIDTH)<< VERTICAL_SPLIT_CODE
        << setw(CELL_WIDTH - 2) << cell_format(d, CELL_WIDTH) << VERTICAL_SPLIT_CODE << endl;
}

void route_show_header() {
    setlocale(LC_ALL, "Russian");
    cout << "Список маршрутов:\n\n";
    setlocale(LC_ALL, "C");
    cout << TOP_LEFT_KORNER_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 2) << TOP_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << TOP_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << TOP_VERTICAL_SPLIT_CODE;
    cout << HORIZONTAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 2) << TOP_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << TOP_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << TOP_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << TOP_RIGHT_KORNER_CODE << endl;

    cout << VERTICAL_SPLIT_CODE << setfill(' ') << setw((CELL_WIDTH - 1) / 2) << "ID" << setfill(' ') << setw((CELL_WIDTH - 1) / 2 - CELL_WIDTH % 2)
        << VERTICAL_SPLIT_CODE << setfill(' ') << setw((CELL_WIDTH) / 2 + CELL_WIDTH % 2 + 3);
    setlocale(LC_ALL, "Russian");
    cout << "Водитель";
    setlocale(LC_ALL, "C");
    cout << setfill(' ') << setw((CELL_WIDTH - 4) / 2 +-2)
        << VERTICAL_SPLIT_CODE << setfill(' ') << setw((CELL_WIDTH) / 2 + 2 + CELL_WIDTH % 2);
    setlocale(LC_ALL, "Russian");
    cout << "Автобус";
    setlocale(LC_ALL, "C");
    cout << setfill(' ') << setw((CELL_WIDTH - 4) / 2 - 1) << VERTICAL_SPLIT_CODE;
    cout << setfill(' ') << setw((CELL_WIDTH - 4) / 2 + 7);
    setlocale(LC_ALL, "Russian");
    cout << "Пункт отпр.";
    setlocale(LC_ALL, "C");
    cout << setfill(' ') << setw((CELL_WIDTH - 4) / 2 + -4 + CELL_WIDTH % 2)
        << VERTICAL_SPLIT_CODE << setfill(' ') << setw((CELL_WIDTH) / 2 + 4 + CELL_WIDTH % 2);
    setlocale(LC_ALL, "Russian");
    cout << "Пункт приб.";
    setlocale(LC_ALL, "C");
    cout << setfill(' ') << setw((CELL_WIDTH - 4) / 2 + -3)
        << VERTICAL_SPLIT_CODE << setfill(' ') << setw((CELL_WIDTH) / 2 + 4 + CELL_WIDTH % 2);
    setlocale(LC_ALL, "Russian");
    cout << "Время отпр.";
    setlocale(LC_ALL, "C");
    cout << setfill(' ') << setw((CELL_WIDTH - 4) / 2 + -3)
        << VERTICAL_SPLIT_CODE << setfill(' ') << setw((CELL_WIDTH) / 2 + 4 + CELL_WIDTH % 2);
    setlocale(LC_ALL, "Russian");
    cout << "Время приб.";
    setlocale(LC_ALL, "C");
    cout << setfill(' ') << setw((CELL_WIDTH - 4) / 2 - 3) << VERTICAL_SPLIT_CODE << endl;
}

void route_show_footer() {
    cout << BOTTOM_LEFT_KORNER_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 2) << BOTTOM_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << BOTTOM_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << BOTTOM_VERTICAL_SPLIT_CODE;
    cout << HORIZONTAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 2) << BOTTOM_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << BOTTOM_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << BOTTOM_VERTICAL_SPLIT_CODE << setfill(HORIZONTAL_SPLIT_CODE) << setw(CELL_WIDTH - 1) << BOTTOM_RIGHT_KORNER_CODE << endl;

}


const string ROUTES_TABLE_NAME = "ROUTES";

void addRoute(sqlite3* db) {

    cout << "Для создания маршрута необходимо прикрепить водителя к автобусу\n";

    getStaffList(db);
    cout << "\n";
    getBusesList(db);

    char* zErrMsg = 0;
    string tabID;
    string busID;
    string departureTime;
    string arrivalTime;
    string departurePlace;
    string arrivalPlace;
    setlocale(LC_ALL, "Russian");
    cout << "Введите табельный номер водителя: ";
    cin >> tabID;
    cout << "Введите ID автобуса: ";
    cin >> busID;
    cout << "Укажите пункт отправления: ";
    cin >> departurePlace;
    cout << "Укажите пункт прибытия: ";
    cin >> arrivalPlace;
    cout << "Укажите время отправления: ";
    cin >> departureTime;
    cout << "Укажите время прибытия: ";
    cin >> arrivalTime;

    string sql = "INSERT INTO " + ROUTES_TABLE_NAME + " (staff_id, bus_id, departure_time, arrival_time, departure_place, arrival_place) VALUES ('" + tabID + "','" + busID + "','" + departureTime + "','" + arrivalTime + "','" + departurePlace + "','" + arrivalPlace + "')";

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

static int route_out_callback(void* data, int argc, char** argv, char** azColName) {
    sqlite3 *db = (sqlite3*)data;
    string staff_sql = "SELECT firstname, secondname from STAFF WHERE id = " + string(argv[1]);
    string bus_sql = "SELECT car_number from BUSES WHERE id = " + string(argv[2]);

    /* Execute SQL statement */

    setlocale(LC_ALL, "C");

    sqlite3_stmt* stmt;
    string fullname = "";

    sqlite3_prepare(db, staff_sql.c_str(), 1000, &stmt, NULL);//preparing the statement

    sqlite3_step(stmt);
    string firstname((char*)sqlite3_column_text(stmt, 0));
    string secondname((char*)sqlite3_column_text(stmt, 1));
    fullname = firstname + " " + secondname;

    sqlite3_prepare(db, bus_sql.c_str(), 1000, &stmt, NULL);//preparing the statement

    sqlite3_step(stmt);
    string bus_name((char*)sqlite3_column_text(stmt, 0));

    sqlite3_finalize(stmt);
    route_split();
    route_show_row(argv[0], fullname, bus_name, argv[3], argv[4], argv[5], argv[6]);
    return 0;
}

void getRouteList(sqlite3* db) {
    char* zErrMsg = 0;

    string sql = "SELECT * from " + ROUTES_TABLE_NAME;
    


    route_show_header(); // Печать шапки таблицы

    int rc = sqlite3_exec(db, sql.c_str(), route_out_callback, (void*)db, &zErrMsg);
    route_show_footer();

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

}

void removeRoute(sqlite3* db) {
    getRouteList(db);
    char* zErrMsg = 0;
    string eid;
    setlocale(LC_ALL, "Russian");
    cout << "\nВведите id для удаления (-1 для отмены): ";
    cin >> eid;
    if (eid == "-1") {
        cout << "Удаление отменено.\n";
        return;
    }
    string sql = "DELETE from " + ROUTES_TABLE_NAME + " WHERE id = " + eid;
    int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &zErrMsg);

    if (rc != SQLITE_OK) {
        cout << "Ошибка! Вы ввели неправильный id.";
    }
    else {
        setlocale(LC_ALL, "Russian");
        cout << "\nЗапись успешно удалена!";
    }
}