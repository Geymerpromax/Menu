#include "Users.h"
bool input_validation_ru(string received_data, int length_data);
bool input_validation_num(string received_data, int length_data);

void Users::change_surname()
{
	
	const int name_limit = 20;
	do
	{
		cout << "Введите фамилию: "; cin >> this->surname;
	} while ((this->surname.length() < name_limit) or (input_validation_ru(this->surname, int(this->surname.length())) != false));
	cout << "Фамилия принята!" << endl;

	fstream file;
	file.open("users_data.txt", fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	file << this->surname << " ";
	file.close();
	cout << "Данные загружены" << endl;
	
}
void Users::change_name()
{
	const int name_limit = 20;
	
	do
	{
		cout << "Введите имя: ";  cin >> this->name;
	} while ((this->name.length() > name_limit) or (input_validation_ru(this->name, int(this->name.length())) == false));
	cout << "Имя принято!" << endl;
	fstream file;
	file.open("users_data.txt", fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	file << this->name << " ";
	file.close();
	cout << "Данные загружены" << endl;
	
}
void Users::change_patronymic()
{
	const int patronymic_limit = 20;
	
	do
	{
		cout << "Введите отчество: "; cin >> this->patronymic;
	} while ((this->patronymic.length() > patronymic_limit) or (input_validation_ru(this->patronymic, int(this->patronymic.length())) == false));
	
	cout << "Отчество принято!" << endl;
	fstream file;
	file.open("users_data.txt", fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	file << this->patronymic << " ";
	file.close();
	cout << "Данные загружены" << endl;
}

void Users::get_data_curent_client()
{
	fstream file;
	file.open("users_data.txt", fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		system("cls");
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	//Проверить
	int buf;
	do
	{
		file >> buf;
	} while (this->id != buf);

	file >> this->id >> this->surname >> this->name >> this->month >> this->day >> this->month >> this->year;
	file.close();
}
void Users::print_data_curent_client()
{
	fstream file;
	file.open("entry_check.txt", fstream::in | fstream::out | fstream::app);
	file >> this->entry >> this->id;
	file.close();
	file.open("users_data.txt", fstream::in | fstream::out | fstream::app);

	if (!(file.is_open()))
	{
		system("cls");
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	cout << "Фамилия: "  << this->surname << endl
		 << "Имя: "      << this->name    << endl
		 << "Отчество: " << this->month   << endl
		 << "День: "     << this->day     << endl
		 << "Месяц: "    << this->month   << endl 
		 << "Год: "      << this->year    << endl;
	file.close();
}

void Users::change_day_birth()
{
	
	const int day_month_limit = 2;
	do
	{
		cout << "Введите день рождения: "; cin >> this->day;
	} while ((this->day.length() > day_month_limit) or input_validation_num(this->day, int(this->day.length())) == false);

	fstream file;
	file.open("users_data.txt", fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	file << this->day << " " << endl;
	file.close();
	cout << "Данные приняты!" << endl;
}
void Users::change_month_birth()
{
	
	const int day_month_limit = 2;
	do
	{
		cout << "Введите месяц рождения: "; cin >> this->month;
	} while ((this->month.length() > day_month_limit) or input_validation_num(this->month, int(this->month.length())) == false);
	fstream file;
	file.open("users_data.txt", fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	file << this->month << " " << endl;
	file.close();
	cout << "Данные приняты!" << endl;

}
void Users::change_year_birth()
{
	
	const int year_limit = 4;
	cin >> this->year;

	do
	{
		cout << "Введите год рождения: "; cin >> this->month;
	} while ((this->month.length() > year_limit) or input_validation_num(this->month, int(this->month.length())) == false);

	fstream file;
	file.open("users_data.txt", fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	file << this->year << endl;
	file.close();
	cout << "Данные приняты!" << endl;
}

int Users::change_data_birth()
{
	return 0;
}


void Users::change_id()
{
	fstream file;
	file.open("reg_list.txt", fstream::in | fstream::out | fstream::app);

	if (!(file.is_open()))
	{
		
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	
	file.close();

	
	file.open("check_login.txt", fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	
	file.close();
}


Users::Users()
{
	surname = "";
	name = "";
	patronymic = "";
	day = "";
	month = "";
	year = "";
	/*
	id += 1;
	fstream file;
	file.open("reg_list.txt", fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	file << id << " ";
	file.close();
	file.open("users_data.txt", fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	file << id << " ";
	file.close();
	*/
}
