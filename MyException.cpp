#include "MyException.h"

MyException::MyException(const char* err_str)
{
	this->err_str = err_str;
}
MyException::MyException(int id_func, const char* err_str, int err_code)
{
	
	this->err_str = err_str;
	this->err_code = err_code;
}
char MyException::MyWhat_str()
{
	return *err_str;
}
