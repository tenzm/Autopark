#pragma once
#include "sqlite3.h"

void addRoute(sqlite3* db);
void getRouteList(sqlite3* db);
void removeRoute(sqlite3* db);