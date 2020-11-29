#include <iostream>
#include <string>

using namespace std;

string cell_format(string str, int width) {
    if (str.length() > width - 4)
        str = str.substr(0, width - 5) + "...";
    return str;
}