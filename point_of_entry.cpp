#pragma once
#include "point_of_entry.h"
#include "main_menu.h"
#include "Users.h"

using namespace std;

// Сравнение данных c клавиатуры и данных из текстового файла: //мусор
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

// Определение размера файла:
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
	int size = file.tellg();///
	file.close();
	return size;
}

// Проверка на вход в аккаунт:
int entry_check()
{
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
	switch (buf)
	{
	case(48):
		login_or_reg_menu();
	case(49):
		cout << "Добро пожаловать!" << endl;
		Main();
	default:
		cout << "Ошибка\nПрограмма будет закрыта!";
		system("pause");
		exit(0);
	}
}

// Проверка введённых символов на соответсвие с алфавитом:
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

// Шифр
string encrypt(string received_data, int length_data)
{
	string base = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789abcdef" };
	string value_data = "";
	string* sent_data = new string[length_data];
	int counter = 0;
	for (int i = 0; i < length_data; i++)
	{
		for (int j = 0; j < 62; j++)
		{
			if (received_data[i] == base[j])
			{
				sent_data[i] = base[j + 1];
				counter++;
				break;

			}
		}
		if (counter == length_data)
		{
			break;
		}
	}

	for (int i = 0; i < length_data; i++)
	{
		value_data += sent_data[i];
	}

	delete[] sent_data;
	return value_data;
}
// Де шифр
string de_encrypt(string received_data, int length_data)
{
	string base = { "9abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" };
	string value_data = "";
	string* sent_data = new string[length_data];
	int counter = 0;
	for (int i = 0; i < length_data; i++)
	{
		for (int j = 1; j < 62; j++)
		{
			if (received_data[i] == base[j])
			{
				sent_data[i] = base[j - 1];
				counter++;
				break;

			}
		}
		if (counter == length_data)
		{
			break;
		}
	}

	for (int i = 0; i < length_data; i++)
	{
		value_data += sent_data[i];
	}

	delete[] sent_data;
	return value_data;
}

// Меню регистрации:
int reg_menu()
{
	system("cls");
	cout << "Меню регистрации:" << endl;
	const int mail_limit = 20;
	cout << "Введите вашу почту, не более " << mail_limit << " символов: "; string mail; cin >> mail; cout << endl;

	if ((mail.length() > mail_limit) or (input_validation_eu(mail, int(mail.length())) == false))
	{
		system("cls");
		if (OK_or_EXIT_or_BACK() == 1)
		{
			reg_menu();
		}
		else
		{
			system("cls");
			login_or_reg_menu();
		}
	}
	const int password_limit = 20;
	cout << "Введите пароль, не более " << password_limit << " символов: "; string password; cin >> password; cout << endl;
	if ((password.length() > password_limit) or input_validation_eu(password, int(password.length())) == false)
	{
		system("cls");

		if (OK_or_EXIT_or_BACK() == 1)
		{
			reg_menu();
		}
		else
		{
			system("cls");
			login_or_reg_menu();
		}
	}

	fstream file;
	switch (determine_file_size("sum_users.txt"))
	{
	case 0:
		file.open("sum_users.txt", fstream::in | fstream::out);
		file << "0";
		file.close();
		break;
	default:
		break;
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
	file << 1;
	file.close();

	system("cls");
	cout << "Желаете добавить персональные данные?" << endl;
	cout << "1. Да" << endl << "2. Нет" << endl << "3. Выход" << endl;
	cout << "Выберите один из пунктов меню: ";
	char choice;
	cin >> choice;
	int res = choice - '\0';
	Users client;
	switch (res)
	{
	case 49:
		system("cls");
		try
		{
			while (client.set_surname())
			{
				break;
			}
		}
		catch (MyException& ex)
		{
			while (OK_or_EXIT_or_BACK() != 3)
			{
				switch (OK_or_EXIT_or_BACK())
				{
				case 1:
				{
					return 1;
				}
				case 2:
				{
					login_or_reg_menu();
				}
				default:
					return 0;
				}
				break;
			}
		}

		try
		{
			client.set_name();
		}
		catch (MyException& ex)
		{
			while (OK_or_EXIT_or_BACK() != 3)
			{
				switch (OK_or_EXIT_or_BACK())
				{
				case 1:
				{
					client.set_name();
				}
				case 2:
				{
					login_or_reg_menu();
				}
				default:
					return 0;
				}
				break;
			}
		}
		try
		{
			client.set_patronymic();
		}
		catch (MyException& ex)
		{
			while (OK_or_EXIT_or_BACK() != 3)
			{
				switch (OK_or_EXIT_or_BACK())
				{
				case 1:
				{
					client.set_name();
					client.set_patronymic();
					client.set_surname();
				}
				case 2:
				{
					login_or_reg_menu();
				}
				default:
					return 0;
				}
				break;
			}
		}

		cout << "Данные имени приняты!" << endl;
		system("cls");
		cout << "Добро пожаловать!" << endl;
		Main();
		break;
	case 50:
		system("cls");
		Main();
		break;
	case 51:
		exit(0);
	default:
		system("cls");
		cout << "Неверный выбор, попробуйте ещё раз!" << endl;
		login_or_reg_menu();
	}

}

// Выбор меню входа или регистрации
int login_or_reg_menu()
{

	cout << "1. Войти" << endl << "2. Зарегестрироваться" << endl << "3. Выход" << endl;
	cout << "Выберите один из пунктов меню: ";
	char choice;
	cin >> choice;
	int res = choice - '\0';
	switch (res)
	{
	case 49:
		login_menu();
		break;
	case 50:
		reg_menu();
		break;
	case 51:
		exit(0);
	default:
		system("cls");
		cout << "Неверный выбор, попробуйте ещё раз!" << endl;
		login_or_reg_menu();

	}
	return 0;
}

// Очистка экрана
void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

// Обработка ошибок
int OK_or_EXIT_or_BACK()
{
	cout << "Ошибка!" << endl;
	cout << "1. Попробовать ещё раз" << endl << "2. Назад" << endl << "3. Выйти из программы" << endl;
	cout << "Выберите один из пунктов меню: ";
	char choice;
	cin >> choice;
	int res = choice - '\0';
	switch (res)
	{
	case 49:
		return 1;
	case 50:
		return 2;
	case 51:
		return 0;
	default:
		system("cls");
		cout << "Неверный выбор, попробуйте ещё раз!" << endl;
		OK_or_EXIT_or_BACK();
		return 3;
	}
}

// Мусор
void clear_reg_list()
{
	fstream reg_list;
	reg_list.open("reg_list.txt", fstream::in | fstream::out | fstream::app);
	reg_list.clear(true);
	reg_list.close();
}

