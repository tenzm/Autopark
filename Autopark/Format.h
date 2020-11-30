#pragma once
#include <string>
using namespace std;

string cell_format(string str, int width); 
bool id_exist(sqlite3* db, string table, string id);