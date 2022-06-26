#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include "sqlite3.h"
#include "backendSupport.cpp"

using namespace std;

int main()
{
    print();
    initUser();
    addEvent();
    showEvent();
    searchEvent_topic();
    // deleteEvent();
    // editEvent();
    searchEvent_ddl();

    return 0;
}