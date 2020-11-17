#include <iostream>
#include <string>
#include <sqlite3.h>
#include <Output.h>

using namespace std;

void addStaff(sqlite3* db) {
    char* zErrMsg = 0;
    string firstname;
    string secondname;
    cout << "Введите имя водителя: ";
    cin >> firstname;
    cout << "Введите фамилию водителя: ";
    cin >> secondname;

    string sql = "INSERT INTO STAFF (firstname, secondname) VALUES ('" + firstname + "','" + secondname + "')";

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

    string sql = "SELECT * from STAFF";

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
    string sql = "DELETE from STAFF WHERE id = " + eid;
    int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, &zErrMsg);

    if (rc != SQLITE_OK) {
        cout << "Ошибка! Вы ввели неправильный id.";
    }
    else {
        setlocale(LC_ALL, "Russian");
        cout << "\nЗапись успешно удалена!";
    }
}