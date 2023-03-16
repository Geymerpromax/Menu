#pragma once
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

class Users
{
private:
	string surname;
	string name;
	string patronymic;
	string day;
	string month;
	string year;
	int id;
	int entry;
public:
	Users();
	void change_surname();
	void change_name();
	void change_patronymic();

	void get_data_curent_client();

	void change_day_birth();
	void change_month_birth();
	void change_year_birth();
	int change_data_birth();
	void set_data(Users current_client);
	void print_data_curent_client();

	void change_id();
};
