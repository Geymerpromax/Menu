#pragma once
#include "point_of_entry.h"
#include "main_menu.h"
#include "Users.h"
#include <iostream>
#include <string.h>
#include <fstream>

class MyException 
{
public:
    MyException(const char* str_err);
    MyException(int id_func, const char* str_err, int err_code);
    char MyWhat_str();
private:
    const char* err_str;
    int err_code;
};

