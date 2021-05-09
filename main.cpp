#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include "namespace.h"
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;
using namespace mln;

struct User { //будут применяться в красивом выводе с динамическими массивами
	string name;
	string surname;
	string fathername;
	string address;
	int ID;
	int phone;
};

struct Hotel {
	int stars;
	string name;
	string address;
};

struct climate {
	string name;
	int tempreture;
	int humidity;
};

struct Country {
	climate clim;
	string name;
	string sea;
};

struct Offers {
	int ID;
	string name;
	Country Cname;
	int cost;
};

void adminMenu(int ID);
void addput();
void outPut(int per = 0, int index = 0);
void userMenu(int ID);
void delPut();

void Signin(char user = 'k');
void SignUp();

void Getput(int userId);
void outklients(int per = 0, int index = 0);
void delklient();
void infClient(int ID = 0);
void redput();
void search();
void filter();
void sort();

void main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choice;
	while (true) {
		cout << "Главное меню" << endl;
		cout << "1 - Вход под администратором" << endl;
		cout << "2 - Вход под клиентом" << endl;
		cout << "3 - Зарегистрироваться" << endl;
		cout << "0 - Выйти" << endl;
		choice = getValue();
		switch (choice) {
		case 1: Signin('a');
			break;
		case 2: Signin();
			break;
		case 3: SignUp();
			break;
		case 0: exit(0);
		default: cout << "Неккоректный ввод, попробуйте ещё раз" << endl;
		}
	}
}

void adminMenu(int ID) {
	int choice;
	while (true) {
		cout << "Меню:" << endl;
		cout << "1 - Добавить пользователя" << endl;
		cout << "2 - Удалить клиента" << endl;
		cout << "3 - Посмотреть всех клиентов" << endl;
		cout << "4 - Посмотреть историю одного клиента" << endl;
		cout << "5 - Добавить путёвку" << endl;
		cout << "6 - Удалить путёвку" << endl;
		cout << "7 - Посмотреть все путёвки" << endl;
		cout << "8 - Редактировать путёвку" << endl;
		cout << "0 - Выход" << endl;
		choice = getValue();
		switch (choice) {
		case 1: SignUp();
			break;
		case 2: delklient();
			break;
		case 3: outklients();
			break;
		case 4: infClient();
			break;
		case 5: addput();
			break;
		case 6: delPut();
			break;
		case 7: outPut();
			break;
		case 8:redput();
			break;
		case 0: return;
		default: cout << "Неверный ввод" << endl;
		}
	}
}

void userMenu(int ID) {//поменять id на index
	int index;
	User user;
	user.ID = stoi(fulldata("klient.txt", ID, 0));
	index = stoi(Fsearch("infklient.txt", to_string(user.ID), 0, 'k'));
	user.name = fulldata("infklient.txt", index, 1);
	user.surname = fulldata("infklient.txt", index, 2);
	user.fathername = fulldata("infklient.txt", index, 3);
	user.address = fulldata("infklient.txt", index, 4);
	user.phone = stoi(fulldata("infklient.txt", index, 5));
	while (true) {
		int choice;

		cout << "Меню" << endl;
		cout << "1 - Заказать путёвку" << endl;
		cout << "2 - Просмотреть путёвки" << endl;
		cout << "3 - Посмотреть историю покупок" << endl;
		cout << "4 - Поиск путёвки" << endl;
		cout << "5 - Фильтрация путёвок" << endl;
		cout << "6 - Сортировка путёвок по цене" << endl;
		cout << "0 - Выход" << endl;
		cin >> choice;
		switch (choice) {
		case 1: Getput(user.ID);
			break;
		case 2: outPut();
			break;
		case 3: infClient(user.ID);
			break;
		case 4: search();
			break;
		case 5: filter();
			break;
		case 6: sort();
			break;
		case 0: return;
		default: cout << "Нет такой функции" << endl;
		}
	}
}

void addput() {
	string country, climate, name;
	string message;
	int tempreture, hemidity;
	int ID, cost;
	bool sea;
	cout << "Введите код путёвки" << endl; //Поправить добавление, чтобы ставился ентер
	ID = getValue();
	cout << "Введите страну" << endl;
	cin >> country;
	cout << "Введите климат" << endl;
	cin >> climate;
	cout << "Введите среднюю тмературу" << endl;
	tempreture = getValue();
	cout << "Введите среднюю влажность" << endl;
	hemidity = getValue();
	cout << "Наличие моря?(1-есть, 0-нет)" << endl;
	cin >> sea;
	cout << "Введите название путёвки" << endl;
	cin >> name;
	cout << "Введите цену путёвки" << endl;
	cost = getValue();
	if (sea == 1)
		message = to_string(ID) + "," + name + "," + country + "," + climate + "," + to_string(tempreture) + "," + to_string(hemidity) + ",Есть," + to_string(cost) + "|";
	else
		message = to_string(ID) + "," + name + "," + country + "," + climate + "," + to_string(tempreture) + "," + to_string(hemidity) + ",Нет," + to_string(cost) + "|";
	Record("offers.txt", message, 'a');
}

void outPut(int per, int index) { //номер в файле ещё надо отправлять
	string line;
	string path = "offers.txt";
	ifstream put(path);
	Offers offer;
	int help, help1;
	if (per == 1) {
		help = index;
		help1 = index;
	}
	else {
		help = 0;
		help1 = fsize(path);
	}
	if (!put.is_open()) {
		cout << "Невозможно открыть файл с путёвками" << endl;
	}
	else {
		cout << setw(5) << "ID";
		cout << setw(20) << "Название путёвки ";
		cout << setw(15) << "Страна ";
		cout << setw(17) << "Климат ";
		cout << setw(15) << "Температура ";
		cout << setw(15) << "Влажность ";
		cout << setw(15) << "Море ";
		cout << setw(15) << "Стоимость " << endl;
		for (int i = help; i <= help1; i++)
		{
			offer.ID = stoi(fulldata(path, i, 0));
			offer.name = fulldata(path, i, 1);
			offer.Cname.name = fulldata(path, i, 2);
			offer.Cname.clim.name = fulldata(path, i, 3);
			offer.Cname.clim.tempreture = stoi(fulldata(path, i, 4));
			offer.Cname.clim.humidity = stoi(fulldata(path, i, 5));
			offer.Cname.sea = fulldata(path, i, 6);
			offer.cost = stoi(fulldata(path, i, 7));
			cout << setw(5) << offer.ID << "|";
			cout << setw(20) << offer.name << "|";
			cout << setw(15) << offer.Cname.name << "|";
			cout << setw(15) << offer.Cname.clim.name << "|";
			cout << setw(15) << offer.Cname.clim.tempreture << "|";
			cout << setw(15) << offer.Cname.clim.humidity << "|";
			cout << setw(10) << offer.Cname.sea << "|";
			cout << setw(15) << offer.cost << "|" << endl;
		}
	}
}

void delPut() {
	int ID, choice;
	cout << "Введите код путёвки" << endl;
	ID = getValue();
	cout << "Вы уверены, что хотите удалить?(1-да, 2-нет)" << endl; 
	outPut(1, stoi(Fsearch("offers.txt", to_string(ID), 0, 'b')));
	choice = getValue();
	switch (choice) {
	case 1: fdel("offers.txt", stoi(Fsearch("offers.txt", to_string(ID), 0, 'k')));
		break;
	case 2: cout << "ОК" << endl;
		break;
	default: cout << "Неправильный ввод" << endl;
	}
}

void Signin(char user) {
	string path;
	string login, pass;
	if (user == 'k') {
		path = "klient.txt";
	}
	else if (user == 'a') {
		path = "admin.txt";
	}
	while (true)
	{
		cout << "Введите логин" << endl;
		cin >> login;
		if (Fsearch(path, login, 1) == "Error")
		{
			cout << "Такого логина нет, попробуйте ещё раз" << endl;
		}
		else
		{
			cout << "Введите пароль" << endl;
			cin >> pass;
			if (Fsearch(path, login, 1, 'k') == Fsearch(path, pass, 2, 'k'))
			{
				if (user == 'k')
					userMenu(stoi(Fsearch(path, login, 1, 'k')));
				else if (user == 'a')
					adminMenu(stoi(Fsearch(path, login, 1, 'k')));
				break;
			}
			else {
				cout << "Пароль введён неверно" << endl;
			}
		}
	}
}

void SignUp() {
	string name, surname, fathername, address, login, pass;
	int ID, phone;
	cout << "Введите имя пользователя" << endl;
	cin >> name;
	cout << "Введите фамилию пользователя" << endl;
	cin >> surname;
	cout << "Введите отчество" << endl;
	cin >> fathername;
	cout << "Введите адрес" << endl;
	cin >> address;
	cout << "Введите код клиента" << endl;
	ID = getValue();
	cout << "Введите номер клиента" << endl;
	phone = getValue();
	cout << "Введите логин пользователя" << endl;
	cin >> login;
	cout << "Введите пароль пользователя" << endl;
	cin >> pass;
	string message;
	message = to_string(ID) + "," + name + "," + surname + "," + fathername + "," + address + "," + to_string(phone) + "|";
	Record("infklient.txt", message, 'a');
	message = to_string(ID) + "," + login + "," + pass + "|";
	Record("klient.txt", message, 'a');
}

void Getput(int userID) {
	string ID, message;
	int choice;
	cout << "Введите код путёвки" << endl;
	cin >> ID;
	if (Fsearch("offers.txt", ID, 0) == "Error") {
		cout << "Нет такой путёвки" << endl << "Вывести вам все путёвки?(1-Да, 2-Нет)" << endl;
		choice = getValue();
		if (choice == 1) {
			outPut();
			Getput(userID);
		}
		else if (choice == 2)
			cout << "Ладно" << endl;
		else
			cout << "Неправильный ввод" << endl;
	}
	else {
		cout << Fsearch("offers.txt", ID, 0) << endl;
		cout << "Вы точно хотите туда поехать?(1-Да, 2-Нет)" << endl;
		choice = getValue();
		if (choice == 1) {
			cout << "Вы успешно приобрели путёвку, удачной поездки" << endl;
			message = to_string(userID) + ',' + Fsearch("offers.txt", ID, 0);
			Record("history.txt", message, 'a');
		}
		else if (choice == 2) {
			cout << "Ладно" << endl;
		}
		else {
			cout << "Неккоректный ввод" << endl;
		}
	}

}

void outklients(int per, int index) {
	User klient;
	string path = "infklient.txt";
	int help, help1;
	if (per == 1) {
		help = index;
		help1 = index;
	}
	else {
		help = 0;
		help1 = fsize(path);
	}
	cout << setw(5) << "ID";
	cout << setw(15) << "Имя";
	cout << setw(15) << "Фамилия";
	cout << setw(15) << "Отчество";
	cout << setw(15) << "Адрес";
	cout << setw(15) << "Телефон" << endl;
	for (int i = help; i <= help1; i++)
	{
		klient.ID = stoi(fulldata(path, i, 0));
		klient.name = fulldata(path, i, 1);
		klient.surname = fulldata(path, i, 2);
		klient.fathername = fulldata(path, i, 3);
		klient.address = fulldata(path, i, 4);
		klient.phone = stoi(fulldata(path, i, 5));
		cout << setw(5) << klient.ID << "|";
		cout << setw(15) << klient.name << "|";
		cout << setw(15) << klient.surname << "|";
		cout << setw(15) << klient.fathername << "|";
		cout << setw(15) << klient.address << "|";
		cout << setw(10) << klient.phone << "|" << endl;
	}
}

void delklient() {
	string par1, par2;
	cout << "Введите ID клиента" << endl;
	int ID = getValue();
	par1 = Fsearch("infklient.txt", to_string(ID), 0, 'k');
	par2 = Fsearch("klient.txt", to_string(ID), 0, 'k');
	if (par1 == "Error" || par2 == "Error") {
		cout << "Нет такого ID" << endl;
	}
	else {
		fdel("infklient.txt", stoi(par1));
		fdel("klient.txt", stoi(par2));
		cout << "Клиент успешно удалён" << endl;
	}
}

void infClient(int ID) {
	string lines[25];
	User klient;
	string path = "infklient.txt";
	string patho = "history.txt";
	Offers offer;
	if (ID == 0) {
		cout << "Введите ID клиента" << endl;
		ID = getValue();
	}
	outklients(1, stoi(Fsearch(path, to_string(ID), 0, 'u')));
	cout << "Заказы:" << endl;
	cout << setw(5) << "ID";
	cout << setw(20) << "Название путёвки ";
	cout << setw(15) << "Страна ";
	cout << setw(17) << "Климат ";
	cout << setw(15) << "Температура ";
	cout << setw(15) << "Влажность ";
	cout << setw(15) << "Море ";
	cout << setw(15) << "Стоимость " << endl;
	char str[150], fline[30];
	string  line;
	ifstream file("history.txt");
	int count = 0, k = 0, check = 0;
	if (!file.is_open()) {
		cout << "Файл не может быть открыт" << endl;
	}
	else {
		while (getline(file, line))
		{
			strcpy(str, line.c_str());
			count = 0;
			k = 0;
			for (int i = 0; i < sizeof(str); i++, k++)
			{
				fline[k] = str[i];
				if (str[i] == ',' || str[i] == '|')
					if (count == 0)
					{
						fline[k] = '\0';
						if (strcmp(fline, to_string(ID).c_str()) == 0) {
							offer.ID = stoi(fulldata(patho, check, 1));
							offer.name = fulldata(patho, check, 2);
							offer.Cname.name = fulldata(patho, check, 3);
							offer.Cname.clim.name = fulldata(patho, check, 4);
							offer.Cname.clim.tempreture = stoi(fulldata(patho, check, 5));
							offer.Cname.clim.humidity = stoi(fulldata(patho, check, 6));
							offer.Cname.sea = fulldata(patho, check, 7);
							offer.cost = stoi(fulldata(patho, check, 8));
							cout << setw(5) << offer.ID << "|";
							cout << setw(20) << offer.name << "|";
							cout << setw(15) << offer.Cname.name << "|";
							cout << setw(15) << offer.Cname.clim.name << "|";
							cout << setw(15) << offer.Cname.clim.tempreture << "|";
							cout << setw(15) << offer.Cname.clim.humidity << "|";
							cout << setw(10) << offer.Cname.sea << "|";
							cout << setw(15) << offer.cost << "|" << endl;
							break;
						}
						else
						{
							memset(fline, 0, 30);
							k = -1;
						}
					}
					else {
						memset(fline, 0, 30);
						count++;
						k = -1;
					}

			}
			str[0] = '\0';
			fline[0] = '\0';
		    check++;
		}
	}
}

void redput() {
	int ID, choice, schoice, i, par;
	Offers offer;
	int cost;
	string path = "offers.txt", line;
	cout << "Введите ID путёвки" << endl;
	ID = getValue();
	cout << "Вы хотите отредактировать эту запись?(1-да, 2-нет)" << endl;
	if (Fsearch(path, to_string(ID), 0, 'k') == "Error")
		cout << "Нет такой записи" << endl;
	else
	{
		outPut(1, stoi(Fsearch(path, to_string(ID), 0, 'k')));
		choice = getValue();
		if (choice == 1)
		{
			i = stoi(Fsearch(path, to_string(ID), 0, 'k'));
			if (Fsearch(path, to_string(ID), 0, 'k') == "Error")
				cout << "Нет такой записи" << endl;
			else
			{
				offer.ID = stoi(fulldata(path, i, 0));
				offer.name = fulldata(path, i, 1);
				offer.Cname.name = fulldata(path, i, 2);
				offer.Cname.clim.name = fulldata(path, i, 3);
				offer.Cname.clim.tempreture = stoi(fulldata(path, i, 4));
				offer.Cname.clim.humidity = stoi(fulldata(path, i, 5));
				offer.Cname.sea = fulldata(path, i, 6);
				offer.cost = stoi(fulldata(path, i, 7));
				cout << "Что вы хотите отредактировать?" << endl;
				cout << "1 - Название путёвки" << endl;
				cout << "2 - Страна" << endl;
				cout << "3 - Климат" << endl;
				cout << "4 - Температура" << endl;
				cout << "5 - Влажность" << endl;
				cout << "6 - Море" << endl;
				cout << "7 - Стоимость" << endl;
				schoice = getValue();
				switch (schoice) {
				case 1:
					cout << "Введите название путевки" << endl;
					cin >> line;
					offer.name = line;
					break;
				case 2:
					cout << "Введите страну" << endl;
					cin >> line;
					offer.Cname.name = line;
					break;
				case 3:
					cout << "Введите климат страны" << endl;
					cin >> line;
					offer.Cname.clim.name = line;
				case 4:
					cout << "Введите температуру страны" << endl;
					par = getValue();
					offer.Cname.clim.tempreture = par;
					break;
				case 5:
					cout << "Введите влажность страны" << endl;
					par = getValue();
					offer.Cname.clim.humidity = par;
					break;
				case 6:
				{
					int l = 0;
					while (true)
					{
						cout << "Введите наличие море(1-да,2-нет)" << endl;
						l = getValue();
						if (l == 1)
						{
							offer.Cname.sea = "Есть";
							break;
						}
						else if (l == 2)
						{
							offer.Cname.sea = "Нет";
							break;
						}
						else
							cout << "Неверный ввод" << endl;
					}
					offer.Cname.sea = line;
					break;
				}
				case 7:
					cout << "Введите стоимость путевки" << endl;
					cost = getValue();
					offer.cost = cost;
					break;
				default: cout << "Неверный ввод" << endl;
				}
				fdel(path, i);
				string message = to_string(ID) + "," + offer.name + "," + offer.Cname.name + "," + offer.Cname.clim.name + "," + to_string(offer.Cname.clim.tempreture) + "," + to_string(offer.Cname.clim.humidity) + "," + offer.Cname.sea + "," + to_string(offer.cost) + "|";
				Record(path, message, 'a');
			}
		}
	}
}

void search() {
	int choice;
	string path = "offers.txt";
	cout << "По какому параметру вы хотите искать путёвку?" << endl;
	cout << "1 - ID" << endl;
	cout << "2 - Страна" << endl;
	cout << "3 - Море" << endl;
	choice = getValue();
	switch (choice) {
	case 1: {
		int ID;
		cout << "Введите ID (4 цифры)" << endl;
		ID = getValue();
		if (Fsearch(path, to_string(ID), 0, 'k') == "Error")
			cout << "Нет такого ID" << endl;
		else
			allnotes(path, to_string(ID), 0);
		break;
	}
	case 2: {
		string Country;
		cout << "Введите название страны" << endl;
		cin >> Country;
		if (Fsearch(path, Country, 2, 'k') == "Error")
			cout << "Нет такогой страны" << endl;
		else
			allnotes(path, Country, 2);
		break;
	}
	case 3: {
		int k;
		cout << "Есть ли море?(1- да, 2- нет)" << endl;
		k = getValue();
		if (k == 1)
		{
			
			if (Fsearch(path, "Есть", 6, 'k') == "Error")
				cout << "Нет такогой страны" << endl;
			else
				allnotes(path, "Есть", 6);
		}
		else if (k == 2)
		{ 
			if (Fsearch(path, "Нет", 6, 'k') == "Error")
				cout << "Нет такогой страны" << endl;
			else
				allnotes(path, "Нет", 6);
		}
		else
			cout << "Неправильный ввод" << endl;
		break;
	default: cout << "Неправильный ввод" << endl;
		break;
	}
	}
}

void filter() {
	int choice;
	string path = "offers.txt";
	cout << "По какому параметру вы хотите фильтровать?" << endl;
	cout << "1 - Цена" << endl;
	cout << "2 - Температура" << endl;
	cout << "3 - Влажность" << endl;
	choice = getValue();
	switch (choice) {
	case 1: { int min, max;
		Offers* arr = new Offers[fsize(path) + 1];
		for (int i = 0; i <= fsize(path); i++)
		{
			arr[i].cost = stoi(fulldata(path, i, 7));
		}
		cout << "Введите минимальное значение" << endl;
		min = getValue();
		cout << "Введите максимальное значение" << endl;
		max = getValue();
		for (int i = 0; i <= fsize(path); i++)
		{
			if (arr[i].cost <= max && arr[i].cost >= min)
			{
				outPut(1, stoi(Fsearch(path, to_string(arr[i].cost), 7, 'k')));

			}
		}
		
	}
    break;
	case 2:
	{int min, max;
	cout << "Введите минимальное значение" << endl;
	min = getValue();
	cout << "Введите максимальное значение" << endl;
	max = getValue();
	Offers* arr = new Offers[fsize(path) + 1];
	for (int i = 0; i <= fsize(path); i++)
	{
		arr[i].Cname.clim.tempreture = stoi(fulldata(path, i, 4));
	}
	for (int i = 0; i <= fsize(path); i++)
	{
		if (arr[i].Cname.clim.tempreture <= max && arr[i].Cname.clim.tempreture >= min)
		{
			outPut(1, stoi(Fsearch(path, to_string(arr[i].Cname.clim.tempreture), 4, 'k')));
		}
	}
	}
	break;
	case 3:
	{int min, max;
	Offers* arr = new Offers[fsize(path) + 1];
	int* arr1 = new int[fsize(path) + 1];
	for (int i = 0; i <= fsize(path); i++)
	{
		arr[i].Cname.clim.humidity = stoi(fulldata(path, i, 5));
	}
	cout << "Введите минимальное значение" << endl;
	min = getValue();
	cout << "Введите максимальное значение" << endl;
	max = getValue();
	for (int i = 0; i <= fsize(path); i++)
	{
		if (arr[i].Cname.clim.humidity <= max && arr[i].Cname.clim.humidity >= min)
		{
			outPut(1, stoi(Fsearch(path, to_string(arr[i].Cname.clim.humidity), 5, 'k')));
		}
	}
	}
	break;
	default: cout << "Неверный ввод" << endl;
	}
}

void sort() {
	int choice, index;
	cout << "Сортировать по убыванию или по возрастанию?(1- По возрастанию, 2 - По убыванию)" << endl;
	choice = getValue();
	string path = "offers.txt";
	string line;
	Offers* arr = new Offers[fsize(path)+1];
	int* arr1 = new int[fsize(path)+1];
	for (int i = 0; i <= fsize(path); i++)
	{
		arr[i].ID = stoi(fulldata(path, i, 0));
		arr[i].name = fulldata(path, i, 1);
		arr[i].Cname.name = fulldata(path, i, 2);
		arr[i].Cname.clim.name = fulldata(path, i, 3);
		arr[i].Cname.clim.tempreture = stoi(fulldata(path, i, 4));
		arr[i].Cname.clim.humidity = stoi(fulldata(path, i, 5));
		arr[i].Cname.sea = fulldata(path, i, 6);
		arr[i].cost = stoi(fulldata(path, i, 7));
		arr1[i] = stoi(fulldata(path, i, 7));
	}
	switch (choice) {
	case 1: {
		int schoice;
		qsort(arr1, fsize(path) + 1, sizeof(int), comp1);
		cout << setw(5) << "ID";
		cout << setw(20) << "Название путёвки ";
		cout << setw(15) << "Страна ";
		cout << setw(17) << "Климат ";
		cout << setw(15) << "Температура ";
		cout << setw(15) << "Влажность ";
		cout << setw(15) << "Море ";
		cout << setw(15) << "Стоимость " << endl;
		for (int i = 0; i <= fsize(path); i++)
		{
			line = to_string(arr1[i]);
			index = stoi(Fsearch(path, to_string(arr1[i]), 7, 'k'));
			cout << setw(5) << arr[index].ID << "|";
			cout << setw(20) << arr[index].name << "|";
			cout << setw(15) << arr[index].Cname.name << "|";
			cout << setw(15) << arr[index].Cname.clim.name << "|";
			cout << setw(15) << arr[index].Cname.clim.tempreture << "|";
			cout << setw(15) << arr[index].Cname.clim.humidity << "|";
			cout << setw(10) << arr[index].Cname.sea << "|";
			cout << setw(15) << arr[index].cost << "|" << endl;
		}
		cout << "Вывести это в файл?(1-да, 2-нет)" << endl;
		schoice = getValue();
		string message;
		if (schoice == 1)
		{
			for (int i = 0; i <= fsize(path); i++)
			{
				message = to_string(arr[index].ID) + "," + arr[index].name + "," + arr[index].Cname.name + "," + arr[index].Cname.clim.name + "," + to_string(arr[index].Cname.clim.tempreture) + "," + to_string(arr[index].Cname.clim.humidity) + ",Есть," + to_string(arr[index].cost) + "|";
				if (i == 0)
					Record(path, message);
				else
					Record(path, message, 'a');
			}
			cout << "Сортированный список успешно выведен" << endl;
		}
		break;
	}
	case 2: {
		qsort(arr1, fsize(path) + 1, sizeof(int), comp2);
		cout << setw(5) << "ID";
		cout << setw(20) << "Название путёвки ";
		cout << setw(15) << "Страна ";
		cout << setw(17) << "Климат ";
		cout << setw(15) << "Температура ";
		cout << setw(15) << "Влажность ";
		cout << setw(15) << "Море ";
		cout << setw(15) << "Стоимость " << endl;
		for (int i = 0; i <= fsize(path); i++)
		{
			line = to_string(arr1[i]);
			index = stoi(Fsearch(path, to_string(arr1[i]), 7, 'k'));
			cout << setw(5) << arr[index].ID << "|";
			cout << setw(20) << arr[index].name << "|";
			cout << setw(15) << arr[index].Cname.name << "|";
			cout << setw(15) << arr[index].Cname.clim.name << "|";
			cout << setw(15) << arr[index].Cname.clim.tempreture << "|";
			cout << setw(15) << arr[index].Cname.clim.humidity << "|";
			cout << setw(10) << arr[index].Cname.sea << "|";
			cout << setw(15) << arr[index].cost << "|" << endl;
		}
		cout << "Вывести это в файл?(1-да, 2-нет)" << endl;
		int schoice = getValue();
		string message;
		if (schoice == 1)
		{
			for (int i = 0; i <= fsize(path); i++)
			{
				message = to_string(arr[index].ID) + "," + arr[index].name + "," + arr[index].Cname.name + "," + arr[index].Cname.clim.name + "," + to_string(arr[index].Cname.clim.tempreture) + "," + to_string(arr[index].Cname.clim.humidity) + ",Есть," + to_string(arr[index].cost) + "|";
				if (i == 0)
					Record(path, message);
				else
					Record(path, message, 'a');
			}
			cout << "Сортированный список успешно выведен" << endl;
		}
		break;
	}
	default: cout << "Неверный ввод" << endl;
		break;
	}
}

