#pragma once
#include <sqlite3.h>

void addStaff(sqlite3* db);
void getStaffList(sqlite3* db);
void removeStaff(sqlite3* db);