#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Users.h"
using namespace std;
void clearRow(int row)
{
	DWORD cWritten;
	// получаем хэндл окна консоли
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	// получаем координаты строки для очистки
	COORD coord = { 0, row - 1};
	// получаем данные из буфера вывода консоли
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi);

	// заполняем строку пробелами
	FillConsoleOutputCharacter(hStdOut, ' ', 80, coord, &cWritten);

	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = row - 1;
	// сбрасываем позицию курсора
	SetConsoleCursorPosition(hStdOut, csbi.dwCursorPosition);
}
int determine_file_size(string file_name);
int compare_data_for_login(string file_name, string input_data)
{
	fstream file;

	file.open(file_name, fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		system("cls");
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}

	string buf[10][10];
	string id;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			file >> buf[i][j];
			if (input_data == buf[i][j])
			{
				return 0;
			}
			if (j == 2)
			{
				break;
			}
		}
		if (file.eof())
		{
			break;
		}
	}
	file.close();
	return 1;
	/*
	fstream file;
	file.open(file_name, fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	string buf;

	while (!file.eof())
	{
		file >> buf;
		if (input_data == buf)
		{
			file.close();
			return 0;
		}
	}
	file.close();
	*/
}
int compare_data_for_login(string file_name, string input_data_1, string input_data_2, string separator)
{
	string value;
	value = input_data_1 + separator + input_data_2;
	fstream file;
	file.open(file_name, fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	string buf;

	while (getline(file, buf))
	{
		if (value == buf)
		{
			file.close();
			return 0;
		}
	}
	file.close();
	return 1;
}

bool input_validation_eu(string received_data, int length_data)
{
	string base = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };
	string* sent_data = new string[length_data];
	int counter = 0;
	for (int i = 0; i < length_data; i++)
	{
		for (int j = 0; j < 62; j++)
		{

			if (received_data[i] == base[j])
			{
				counter++;
				break;
			}

			if (j == 61)
			{
				delete[] sent_data;
				return false;
			}

		}
		if (counter == length_data)
		{
			break;
		}
	}

	delete[] sent_data;
	return true;
}
bool input_validation_ru(string received_data, int length_data)
{
	string base = { "абвгдеёжзийклмнопрстуфхцчшщъыьэюяАБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ" };
	string* sent_data = new string[length_data];
	int counter = 0;
	for (int i = 0; i < length_data; i++)
	{
		for (int j = 0; j < 67; j++)
		{

			if (received_data[i] == base[j])
			{
				counter++;
				break;
			}

			if (j == 66)
			{
				delete[] sent_data;
				return false;
			}

		}
		if (counter == length_data)
		{
			break;
		}
	}

	delete[] sent_data;
	return true;
}
bool input_validation_num(string received_data, int length_data)
{
	string base = { "0123456789" };
	string* sent_data = new string[length_data];
	int counter = 0;
	for (int i = 0; i < length_data; i++)
	{
		for (int j = 0; j < 11; j++)
		{

			if (received_data[i] == base[j])
			{
				counter++;
				break;
			}

			if (j == 10)
			{
				delete[] sent_data;
				return false;
			}

		}
		if (counter == length_data)
		{
			break;
		}
	}

	delete[] sent_data;
	return true;
}

// reg_menu()
// Функция регистрации пользователя.
// Данные после считывания с клавиатуры(Почта и пароль) проверяются и передаются в файл.
// Возвращает 0: если персональные данные(ФИО, ДР) добавлять не требуется.
// Возвращает 1: в обратном случае.
//
int reg_menu()
{
	system("cls");
	cout << "Меню регистрации:" << endl;
	const int mail_limit = 20;
	string mail;
	do
	{
		clearRow(2);
		cout << "Введите вашу почту, не более " << mail_limit << " символов: ";  cin >> mail; 

	} while ((mail.length() > mail_limit) or (input_validation_eu(mail, int(mail.length())) == false));
	
	const int password_limit = 20;
	string password;
	do
	{
		clearRow(3);
		cout << "Введите пароль, не более " << password_limit << " символов: ";  cin >> password;  cout << endl;
	} while ((password.length() > password_limit) or input_validation_eu(password, int(password.length())) == false);

	fstream file;
	if (determine_file_size("sum_users.txt") == 0)
	{
		file.open("sum_users.txt", fstream::in | fstream::out);
		file << "0";
		file.close();
	}
	file.open("sum_users.txt", fstream::in | fstream::out);
	if (!(file.is_open()))
	{
		system("cls");
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	char sum;
	file >> sum;
	file.close();
	sum += 1;
	file.open("sum_users.txt", fstream::in | fstream::out);
	file << sum;
	file.close();
	

	file.open("mail_list.txt", fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		system("cls");
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	file << sum << " " << mail << endl;
	file.close();

	file.open("password_list.txt", fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		system("cls");
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	file << sum << " " << password << " " << endl;
	file.close();

	file.open("users_data.txt", fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		system("cls");
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	file << sum << " ";
	file.close();

	file.open("check_login.txt", fstream::in | fstream::out);
	if (!(file.is_open()))
	{
		system("cls");
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	file << 1 << " " << sum;
	file.close();
	cout << "Вход выполнен." << endl;
	cout << "Желаете добавить персональные данные?" << endl;
	cout << "1. Да" << endl << "2. Нет" << endl;
	char choice;
	int res;
	do
	{
		clearRow(9);
		cout << "Выберите один из пунктов меню: "; cin >> choice;
		res = choice - '\0';

	} while (res != 49 and res != 50);

	switch (res)
	{
	case 48:
		return 0;
	case 49:
		return 1;
	}
}

// Функция: Меню входа.
// Данные после считывания с клавиатуры(Почта и пароль) проверяются на соответствие базе.
// Возвращает 0: если данные соответсвуют
// Возвращает 1: в обратном случае.
int login_menu()
{
	system("cls");
	cout << "Меню Входа:" << endl;
	const int mail_limit = 20;
	string mail;
	do
	{
		clearRow(2);
		cout << "Введите вашу почту: ";  cin >> mail; cout << endl;

	} while ((mail.length() > mail_limit) or (input_validation_eu(mail, int(mail.length())) == false));

	const int password_limit = 20;
	string password;
	do
	{
		clearRow(3);
		cout << "Введите пароль: "; cin >> password; cout << endl;
	} while (((password.length() > password_limit) or input_validation_eu(password, int(password.length())) == false));

	fstream file;

	if (compare_data_for_login("mail_list.txt", mail) == 1 or (compare_data_for_login("password_list.txt", password) == 1))
	{
		cout << "Неверное имя пользователя или пароль!" << endl;
		return 1;
	}
	file.open("check_login.txt", fstream::in | fstream::out);
	if (!(file.is_open()))
	{
		system("cls");
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	file << 1;
	file.close();
}

// Функция выбора: вход или регистрация.
// Возвращает 0: если вход/регистрация выполнены.
// Возвращает 1: если вход/регистрация не выполнены.
// Возвращает 2: если регистрация выполнена, но требуется добавить перс. данные.
int login_or_reg_menu()
{
	char choice;
	int res;
	do
	{
		system("cls");
		cout << "1. Войти" << endl << "2. Зарегестрироваться" << endl << "3. Выход" << endl;
		cout << "Выберите один из пунктов меню: ";
		cin >> choice;
		res = choice - '\0';
	} while (res !=49 and res !=50);
	switch (res)
	{
	case 48:
		exit(0);
	case 49:
		res = login_menu();
		if (res == 0)
		{
			return 0;
		}
		return 1;
	case 50:
		res = reg_menu();
		switch (res)
		{
		case 0:
			return 0;
		case 1:

			return 1;
		}
	}
}

// Функция: Главное меню программы.
// 
//1. Профиль
//2. Выйти из аккаунта
//3. 
//0. Выйти из программы
int main_menu()
{
	system("cls");
	cout << "Главное меню" << endl
		<< "1. Профиль" << endl
		<< "2. Выйти из аккаунта" << endl
		<< "3. " << endl
		<< "0. Выйти из программы" << endl
		<< "Выберите один из пунктов меню: ";
	char choice;
	cin >> choice;
	int res = choice - '\0';
	switch (res)
	{
	case 49:
		return 1;
	case 50:
		/*out_of_profile();*/
		return 0;
	case 51:
		main_menu();
		return 0;
	case 48:
		system("pause");
		exit(0);
	default:
		system("cls");
		cout << "\nНеверный выбор, попробуйте ещё раз!" << endl;
		return 0;
		
	}
	system("pause");
	exit(0);

}
int determine_file_size(string file_name)
{
	fstream file;
	file.open(file_name, fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		system("cls");
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	file.seekg(0, ios::end);
	int size = file.tellg();
	file.close();
	return size;
}


int main()
{
	system("chcp 1251");
	Users current_client;
	int rezult;
	if (determine_file_size("check_login.txt") == 0)
	{
		fstream file;
		file.open("check_login.txt", fstream::in | fstream::out | fstream::app);
		if (!(file.is_open()))
		{
			system("cls");
			cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
			system("pause");
			exit(0);
		}
		file << 0;
		file.close();
	}
	fstream file;
	file.open("check_login.txt", fstream::in | fstream::out | fstream::app);
	if (!(file.is_open()))
	{
		cout << "Ошибка открытия файла\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
	char buf;
	file >> buf;
	file.close();
	if (buf == 48)
	{

		do
		{
			rezult = login_or_reg_menu();
		}
		while (rezult == 1);
		switch (rezult)
		{
		case 0:
			break;
		case 2:
			current_client.change_surname();
			current_client.change_name();
			current_client.change_patronymic();
			current_client.change_day_birth();
			current_client.change_month_birth();
			current_client.change_year_birth();
			break;
		}
	}
	current_client.get_data_curent_client();
	do
	{
		rezult = main_menu();
	} while (rezult == 0);

	return 0;
}