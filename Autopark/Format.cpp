#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;

string cell_format(string str, int width) {
    if (str.length() > width - 4)
        str = str.substr(0, width - 5) + "...";
    return str;
}

bool id_exist(sqlite3* db, string table, string id) {

    sqlite3_stmt* stmt;
    string check_id; // Полное имя

    string query = "SELECT COUNT(*) as count FROM " + table + " WHERE id = \"" + id + "\"";

    sqlite3_prepare(db, query.c_str(), 1000, &stmt, NULL); // Готовимся к выполнению запроса

    sqlite3_step(stmt); // Считываем первую группу элементов
    string count((char*)sqlite3_column_text(stmt, 0)); // Получаем имя водителя

    if(count != "0") return true;
    cout << "Ошибка! Введённого элемента не существует. \n";
    system("pause");
    return false;
    sqlite3_finalize(stmt);
}