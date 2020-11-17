#pragma once
#include "sqlite3.h"

void addBus(sqlite3* db);
void getBusesList(sqlite3* db);
void removeBus(sqlite3* db);