#pragma once
#include <sqlite3.h>
#include <string>

void addStaff(sqlite3* db);
void getStaffList(sqlite3* db);
void removeStaff(sqlite3* db);