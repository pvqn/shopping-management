#ifndef HEADERS
#define HEADERS
#include <iostream>
#include <fstream>
#include <string.h>
#include <chrono>
#include <ctime>
#include <conio.h>
using namespace std::chrono;
using namespace std;
#endif
#include "func.h"
void menu()
{
	cout << "Hello, this is your shop management software" << endl;
	cout << "1. First time? Want to add item in your list?" << endl;
	cout << "2. You want to restock?" << endl;
	cout << "3. This option is for selling item" << endl;
	cout << " This option includes: " << endl; 
	cout << " 3.1 Printing the bill" << endl;
	cout << " 3.2 Discount by membership" << endl;
	cout << " 3.3 Discount by birthday of customer" << endl;
	cout << "4. Best seller in your shop!!! and The worst in your shop :(" << endl;
	cout << "5. Let's check things you should add more" << endl;
	cout << "6. How about the expired dates? These following items will be expired in next few days" << endl;
	cout << "7. Find thing by barcode" << endl;
	cout << "8. Find things by tags" << endl;
	cout << "9. Find things by price " << endl;
	cout << "10. Find things by keyword" << endl;
	cout << "11. Find things by expired day, month, year" << endl;
	cout << "12. Find things by tag + barcode" << endl;
	cout << "13. Find things by tag + price " << endl;
	cout << "14. This option is for printing all data of items to a text file" << endl;
	cout << "15. This option is for printing a list of items which are sorted by rate of selling to a file" << endl;
	cout << "16. You want to fix information of an item? " << endl;
	cout << "17. Want to clear item by barcode? " << endl;
	cout << "18. Want to clear item by tag? " << endl;
	cout << "19. Want to clear all items in shop? " << endl;
	cout << "Press 0 to escape. Thanks! : )" << endl;
	cout << "Press the number you want to choose : ";
}
bool CheckTagsExist(arrayoftags tags, char tag[10])
{
	for (int i = 0; i <= tags.count; ++i)
		if (strcmp(tags.tag[i].name, tag) == 0)
			return true;
	return false;
}
void timeNow(date& Date)
{
	system_clock::time_point now = system_clock::now();
	time_t tt = system_clock::to_time_t(now);
	tm local_tm = *localtime(&tt);
	Date.year = local_tm.tm_year + 1900;
	Date.month = local_tm.tm_mon + 1;
	Date.day = local_tm.tm_mday;
	return;
}
void initialize1(members& Members)
{
	ifstream fin;
	fin.open("Input1.txt");
	fin >> Members.count;
	for (int i = 0; i <= Members.count; ++i)
	{
		fin.ignore(1000, '\n');
		fin.getline(Members.Person[i].name, 20);
		fin >> Members.Person[i].frequency;
		fin >> Members.Person[i].dob.day >> Members.Person[i].dob.month >> Members.Person[i].dob.year;
	}
	fin.close();
}
bool initialize(item shop[], int& count, arrayoftags& tags)
{
	count = -1;
	ifstream fin;
	fin.open("Input.txt");
	if (fin.eof())
		return false;
	do
	{
		++count;
		fin >> shop[count].barcode;
		fin.ignore(1000, '\n');
		fin.getline(shop[count].name, 30);
		fin.getline(shop[count].tag, 20);
		fin >> shop[count].price >> shop[count].stock_level >> shop[count].sum_of_selling;
		fin >> shop[count].expired_date.day >>
			shop[count].expired_date.month >> shop[count].expired_date.year;
		fin >> shop[count].first_date.day >> shop[count].first_date.month >> shop[count].first_date.year;
		fin >> shop[count].last_date.day >>
			shop[count].last_date.month >> shop[count].last_date.year;
		if (!CheckTagsExist(tags, shop[count].tag))
		{
			++tags.count;
			strcpy_s(tags.tag[tags.count].name, shop[count].tag);
		}
	} while (!fin.eof());
	fin.close();
	--count;
	--tags.count;
	return true;
}
void SavetoFile1(members Members)
{
	ofstream fout;
	fout.open("Input1.txt");
	fout << Members.count << endl;
	int i;
	for (i = 0; i <= Members.count; ++i);
	{
		fout << Members.Person[i].name << endl;
		fout << Members.Person[i].frequency << endl;
		fout << Members.Person[i].dob.day <<" " << Members.Person[i].dob.month << " " << Members.Person[i].dob.year <<endl;
	}
	fout.close();
}
void SaveToFile(item shop[], int count)
{
	ofstream fout;
	fout.open("Input.txt");
	for (int i = 0; i <= count; ++i)
	{
		fout << shop[i].barcode;
		fout << endl;
		for (int j = 0; j < (int)strlen(shop[i].name); ++j)
			fout << shop[i].name[j];
		fout << endl;
		for (int j = 0; j < (int)strlen(shop[i].tag); ++j)
			fout << shop[i].tag[j];
		fout << endl;
		fout << shop[i].price << endl;
		fout << shop[i].stock_level << endl;
		fout << shop[i].sum_of_selling;
		fout << endl;
		fout << shop[i].expired_date.day << " " << shop[i].expired_date.month << " " << shop[i].expired_date.year;
		fout << endl;
		fout << shop[i].first_date.day << " " << shop[i].first_date.month << " " << shop[i].first_date.year << endl;
		fout << shop[i].last_date.day << " " << shop[i].last_date.month << " " << shop[i].last_date.year;
		fout << endl;
	}
	fout.close();
}
void printoutbill(item bill[], int count, float price, members& Members, char name[])
{
	ofstream fout;
	date Today;
	timeNow(Today);
	fout.open("Output.txt");
	fout << "The Bill: "; fout << endl;
	for (int i = 0; i <= count; ++i)
	{
		fout << i + 1 << " name: ";
		for (int j = 0; j < (int)strlen(bill[i].name); ++j)
			fout << bill[i].name[j];
		fout << " amount: " << bill[i].sum_of_selling << " total: " << bill[i].price;
		fout << endl;
	}
	fout << "total: " << price;
	fout << "Customer's Name: " << name << endl;
	float discount=0;
	for (int i = 0; i <= Members.count; ++i)
	{
		if (strcmp(name, Members.Person[i].name) == 0)
		{
			if (Today.day == Members.Person[i].dob.day && Today.month == Members.Person[i].dob.month)
			{
				fout << "Discount 5 percent of total price for customer's birthday." << endl;
				discount += 0.05;
			}
			if (Members.Person[i].frequency >= 10 && Members.Person[i].frequency < 100)
			{
				fout << "Discount 2 percent of total price as a member" << endl;
				discount += 0.02;
			}
			if (Members.Person[i].frequency >= 100 && Members.Person[i].frequency < 500)
			{
				fout << "Discount 3 percent of total price as a member" << endl;
				discount += 0.03;
			}
			if (Members.Person[i].frequency >=500 )
			{
				fout << "Discount 4 percent of total price as a member" << endl;
				discount += 0.04;
			}
			break;
		}
	}
	if (discount == 0) fout << "Total discount: 0 percent";
	else
	{
		price = price * (1 - discount);
		fout << "Total Price: " << price << endl;
	}
	fout.close();
}
void restock_item(item shop[], int& count, arrayoftags& tags)
{
	int barcode, number;
	float price = 0;
	cout << "enter the barcode: ";
	cin >> barcode;
	while (barcode != 0)
	{
		bool exist = false;
		for (int i = 0; i <= count; ++i)
			if (shop[i].barcode == barcode)
			{
				cout << "how many? ";
				cin >> number;
				shop[i].stock_level += number;
				exist = true;
				break;
			}
		if (!exist)
		{
			++count;
			shop[count].barcode = barcode;
			cin.ignore(1000, '\n');
			cout << "enter the name: ";
			cin.getline(shop[count].name, 20);
			cout << "enter the tag: ";
			cin.getline(shop[count].tag, 20);
			if (!CheckTagsExist(tags, shop[count].tag))
			{
				++tags.count;
				strcpy_s(tags.tag[tags.count].name, shop[count].tag);
			}
			cout << "enter the price: ";
			cin >> shop[count].price;
			cout << "how many? ";
			cin >> number;
			shop[count].stock_level += number;
			cout << "enter the expired day: ";
			cin >> shop[count].expired_date.day >>
				shop[count].expired_date.month >> shop[count].expired_date.year;
			cout << "enter the first date this item appeared: ";
			cin >> shop[count].first_date.day >> shop[count].first_date.month >> shop[count].first_date.year;
			timeNow(shop[count].last_date);
		}
		cout << "enter the barcode: ";
		cin >> barcode;
	}
	SaveToFile(shop, count);
}
void sellitem(item shop[], int count, item bill[], members &Members)
{
	int barcode, number;
	float price = 0;
	cout << "enter the barcode";
	cin >> barcode;
	int count1 = -1;
	while (barcode != 0)
	{
		for (int i = 0; i <= count; ++i)
			if (shop[i].barcode == barcode)
			{
				cout << "how many? ";
				cin >> number;
				if (number > shop[i].stock_level)
				{
					cout << "sorry, out of stock";
				}
				else
				{
					shop[i].stock_level -= number;
					shop[i].sum_of_selling += number;
					price += (shop[i].price * number);
					++count1;
					strcpy_s(bill[count1].name, shop[i].name);
					bill[count1].price = shop[i].price * number;
					bill[count1].sum_of_selling = number;
					timeNow(shop[count1].last_date);
				}
				break;
			}
		cout << "enter the barcode: ";
		cin >> barcode;
	}
	cout << "Customer's Name: "; char name[30]; cin.get(name, 20);
	cout << "Is customer a member? Y/N: ";
	int key;
	key = _getch();
	cout << key - 48 << endl;
	if (key == 'Y' || key == 'y')
	{
		for (int i = 0; i <= Members.count; ++i)
		{
			if (strcmp(name, Members.Person[i].name) == 0)
			{
				++Members.Person[i].frequency;
			}
		}
	}
	else {
		cout << "Is customer want to be a member? Y/N: ";
		key = _getch();
		cout << key - 48 << endl;
		if (key == 'Y' || key == 'y')
		{
			++count;
			++Members.Person[count].frequency;
			strcpy(Members.Person[count].name, name);
			cout << "What's his/her birthday? ";
			cin >> Members.Person[count].dob.day >> Members.Person[count].dob.month >> Members.Person[count].dob.year;
		}
		}
	printoutbill(bill, count1, price, Members, name);
	SaveToFile(shop, count);
	SavetoFile1(Members);
}
void initialize_first(item* shop, int& count, arrayoftags& tags)
{
	int barcode, number;
	float price = 0;
	cout << "enter the barcode: ";
	cin >> barcode;
	while (barcode != 0)
	{
		++count;
		shop[count].barcode = barcode;
		cin.ignore(1000, '\n');
		cout << "enter the name: ";
		cin.getline(shop[count].name, 20);
		cout << "enter the tag: ";
		cin.getline(shop[count].tag, 20);
		if (!CheckTagsExist(tags, shop[count].tag))
		{
			++tags.count;
			strcpy_s(tags.tag[count].name, shop[count].tag);
		}
		cout << "enter the price: ";
		cin >> shop[count].price;
		cout << "how many? ";
		cin >> number;
		shop[count].stock_level += number;
		cout << "enter the expired day: ";
		cin >> shop[count].expired_date.day >> shop[count].expired_date.month >> shop[count].expired_date.year;
		cout << "enter the first date this item appeared: ";
		cin >> shop[count].first_date.day >> shop[count].first_date.month >> shop[count].first_date.year;
		cout << "enter the barcode: ";
		cin >> barcode;
		timeNow(shop[count].last_date);
	}
	SaveToFile(shop, count);
}
bool IsLeap(int year)
{
	bool leap;
	if ((year % 100) == 0)
	{
		if ((year % 400) == 0)
			leap = true;
		else
			leap = false;
	}
	else if ((year % 4) == 0)
		leap = true;
	else
		leap = false;
	return leap;
}
int howmanyday(int month, int year)
{
	if ((month == 1) or (month == 3) or (month == 5) or (month == 7) or (month == 8) or (month == 10) or (month == 12))
		return 31;
	if ((month == 4) or (month == 6) or (month == 9) or (month == 11))
		return 30;
	if (IsLeap(year))
		return 29;
	else
		return 28;
}
int DistanceBetween2Day(date Date1, date Date2)
{
	int d1, d2, m1, m2, y1, y2;
	int day = 0;
	d1 = Date1.day;
	m1 = Date1.month;
	y1 = Date1.year;
	d2 = Date2.day;
	m2 = Date2.month;
	y2 = Date2.year;
	if (y1 != y2)
	{
		for (int i = y1 + 1; i < y2; ++i)
			if (IsLeap(i))
				day += 366;
			else
				day += 365;
		for (int i = 1; i < m2; ++i)
			day += howmanyday(i, y2);
		day += d2;
		for (int i = m1 + 1; i <= 12; ++i)
			day += howmanyday(i, y1);
		day += howmanyday(m1, y1) - d1;
	}
	if (y1 == y2)
	{
		if (m1 == m2)
			day = d2 - d1;
		if (m1 < m2)
		{
			day += howmanyday(m1, y1) - d1 + d2;
			for (int i = m1 + 1; i <= m2 - 1; ++i)
				day += howmanyday(i, y1);
		}
		if (m1 > m2)
		{
			day += -d1 - howmanyday(m2, y1) + d1;
			for (int i = m2 + 1; i <= m1 - 1; ++i)
				day += howmanyday(i, y1);
		}
	}
	return day;
}
void Print_Result(item Item, bool isBest)
{
	if (isBest)
	{
		cout << "THE BEST SELLER IS: ";
		for (int i = 0; i < (int)strlen(Item.name); ++i)
			cout << Item.name[i];
	}
	else
	{
		cout << "THE WORST IS: ";
		for (int i = 0; i < (int)strlen(Item.name); ++i)
			cout << Item.name[i];
	}
	cout << endl;
}
void FindBestAndWorst(item shop[], int count)
{
	float min = 2147483647.0, max = -2147483648.0;
	int position;
	for (int i = 0; i <= count; ++i)
	{
		int day = DistanceBetween2Day(shop[i].first_date, shop[i].last_date);
		float rate = ((float)shop[i].sum_of_selling) / day;
		if (rate < min)
		{
			min = rate;
			position = i;
		}
	}
	Print_Result(shop[position], true);
	for (int i = 0; i <= count; ++i)
	{
		int day = DistanceBetween2Day(shop[i].first_date, shop[i].last_date);
		float rate = ((float)shop[i].sum_of_selling) / day;
		if (rate > max)
		{
			max = rate;
			position = i;
		}
	}
	Print_Result(shop[position], false);
}
void PrintItem(item Item)
{
	cout << "Barcode: " << Item.barcode << endl;
	cout << "Name: ";
	for (int j = 0; j < (int)strlen(Item.name); ++j)
		cout << Item.name[j];
	cout << endl;
	cout << "Tag: " << Item.tag << endl;
	cout << "Price: " << Item.price << endl;
	cout << "Stock level: " << Item.stock_level << endl;
	cout << "Sum of selling: " << Item.sum_of_selling << endl;
	cout << "Last update: " << Item.last_date.day << "/" << Item.last_date.month << "/" << Item.last_date.year << endl;
	cout << "Expired day: " << Item.expired_date.day << "/" << Item.expired_date.month << "/" << Item.expired_date.year << endl;
}
void CheckShouldAdd(item shop[], int count)
{
	cout << "this is the list of things which its stock levels are under or equal to the minimum level \n(the level has the value which is 10). " << endl;
	for (int i = 0; i <= count; ++i)
	{
		if (shop[i].stock_level <= shop[i].min_stock_level)
		{
			cout << i + 1 << " ";
			PrintItem(shop[i]);
			cout << endl;
		}
	}
}
void CheckExpiredDay(item shop[], int count)
{
	cout << "this is the list of things which its expired day will be the next few days." << endl;
	int number = 0;
	for (int i = 0; i <= count; ++i)
	{
		int day = DistanceBetween2Day(shop[i].first_date, shop[i].last_date);
		if (day <= 7)
		{
			++number;
			cout << number << " ";
			PrintItem(shop[i]);
			cout << endl;
		}
	}
}
void FindByBarcode(item shop[], int count)
{
	bool check = false;
	cout << "Which barcode you want to find: ";
	int barcode;
	cin >> barcode;
	for (int i = 0; i <= count; ++i)
	{
		if (shop[i].barcode == barcode)
		{
			cout << "Result: " << endl;
			PrintItem(shop[i]);
			break;
		}
	}
	if (!check)
		cout << "No matching found" << endl;
}
void PrintListofTagtoFind(arrayoftags tags)
{
	cout << "Here is the list of tags you are having: " << endl;
	for (int i = 0; i <= tags.count; ++i)
	{
		cout << i + 1 << ". ";
		for (int j = 0; j < (int)strlen(tags.tag[i].name); ++j)
		{
			cout << tags.tag[i].name[j];
		}
		cout << endl;
	}
}
void FindByTags(item shop[], arrayoftags tags, int& count)
{
	PrintListofTagtoFind(tags);
	cout << "Enter the number of the tag you want to find: ";
	int n;
	cin >> n;
	--n;
	char name[10]; bool check = false;
	strcpy_s(name, tags.tag[n].name);
	cout << "Here is the list of item having the tag: " << endl;
	int order = 0;
	for (int i = 0; i <= count; ++i)
	{
		if (strcmp(name, shop[i].tag) == 0)
		{
			++order;
			cout << order << "." << endl;
			PrintItem(shop[i]);
			check = true;
		}
	}
	if (!check) cout << "No matching found" << endl;
}
void PrintOutItemtoFile(item shop[], int count)
{
	ofstream fout;
	fout.open("Output.txt");
	for (int i = 0; i <= count; ++i)
	{
		fout << "Barcode: " << shop[i].barcode << endl;
		fout << "Name: ";
		fout << shop[i].name;
		fout << endl;
		fout << "Tag: " << shop[i].tag << endl;
		fout << "Price: " << shop[i].price << endl;
		fout << "Stock level: " << shop[i].stock_level << endl;
		fout << "Sum of selling: " << shop[i].sum_of_selling << endl;
		fout << "Last update: " << shop[i].last_date.day << "/" << shop[i].last_date.month << "/" << shop[i].last_date.year << endl;
		fout << "Expired day: " << shop[i].expired_date.day << "/" << shop[i].expired_date.month << "/" << shop[i].expired_date.year << endl;
	}
	fout.close();
}
bool ShouldDeleteTag(item shop[], char tag[], int count, int& position, arrayoftags tags)
{
	int count1 = -1;
	for (int i = 0; i <= count; ++i)
	{
		if (strcmp(tag, shop[i].tag) == 0)
			++count1;
	}
	if (count1) {
		for (int i = 0; i <= tags.count; ++i)
		{
			if (strcmp(tag, tags.tag[i].name))
			{
				position = i;
				break;
			}
		}
		return false;
	}
	else return true;
}
void FixInformation(item shop[], arrayoftags tags, int count)
{
	int barcode = 0;
	int position = 0;
	cout << "enter the barcode of product you want to change its information: ";
	cin >> barcode;
	while (barcode != 0)
	{
		cout << "Here is the list of properties of this product: " << endl;
		cout << "1. Barcode " << endl;
		cout << "2. Name" << endl;
		cout << "3. Tag" << endl;
		cout << "4. Stock_level" << endl;
		cout << "5. Sum of Selling" << endl;
		cout << "6. Mininum of stock level" << endl;
		cout << "7. Price" << endl;
		cout << "8. Expired date" << endl;
		cout << "Enter the number of a property you want to change: " << endl;
		int key; cin >> key;
		while (key != 0)
		{
			switch (key)
			{
			case 1:
				cout << "enter the new barcode: ";
				cin >> shop[barcode].barcode;
				break;
			case 2:
				cout << "enter the new name: ";
				cin.get(shop[barcode].name, 20);
				break;
			case 3:
				cout << "enter the new tag: ";
				char tag[20];
				strcpy(tag, shop[barcode].tag);
				cin.get(shop[barcode].tag, 20);
				if (CheckTagsExist(tags, shop[barcode].tag) == false && ShouldDeleteTag(shop, tag, count, position, tags) == true)
					strcpy(shop[barcode].tag, tags.tag[position].name);
				if (CheckTagsExist(tags, shop[barcode].tag) == false && ShouldDeleteTag(shop, tag, count, position, tags) == false)
				{
					++tags.count;
					strcpy(tags.tag[count].name, shop[barcode].tag);
				}
				if (CheckTagsExist(tags, shop[barcode].tag) == true && ShouldDeleteTag(shop, tag, count, position, tags) == true)
				{
					for (int i = position; i < tags.count; ++i)
						strcpy(tags.tag[i].name, tags.tag[i + 1].name);
					--tags.count;
				}
				break;
			case 4:
				cout << "enter the new stock level: ";
				cin >> shop[barcode].stock_level;
				break;
			case 5:
				cout << "enter the new sum of selling: ";
				cin >> shop[barcode].sum_of_selling;
				break;
			case 6:
				cout << "enter the new minimum of stock level: ";
				cin >> shop[barcode].min_stock_level;
				break;
			case 7:
				cout << "enter the new price: ";
				cin >> shop[barcode].price;
				break;
			case 8:
				cout << "enter the new expired date: ";
				cin >> shop[barcode].expired_date.day
					>> shop[barcode].expired_date.month
					>> shop[barcode].expired_date.year;
				break;
			default:
				cout << "no matching found: " << endl;
				break;
			}
			cout << "Enter the number of a property you want to change: " << endl;
			cin >> key;
		}
		cout << "enter the barcode of product you want to change its information: ";
		cin >> barcode;
	}
}
void Swap(int& a, int& b)
{
	int c;
	c = a;
	a = b;
	b = c;
}
void sortRate(item shop[], int count)
{
	item alt[1000];
	int count1 = count;
	for (int i = 0; i <= count; ++i)
	{
		alt[i].sum_of_selling = shop[i].sum_of_selling;
		alt[i].first_date.day = shop[i].first_date.day;
		alt[i].first_date.month = shop[i].first_date.month;
		alt[i].first_date.year = shop[i].first_date.year;
		alt[i].last_date.day = shop[i].last_date.day;
		alt[i].last_date.month = shop[i].last_date.month;
		alt[i].last_date.year = shop[i].last_date.year;
		strcpy(alt[i].name, shop[i].name);
	}
	for (int i = 0; i <= count; ++i)
	{
		int day = DistanceBetween2Day(alt[i].first_date, alt[i].last_date);
		float rate = ((float)alt[i].sum_of_selling) / day;
		for (int j = i; j <= count - 1; ++j)
		{
			int day1 = DistanceBetween2Day(alt[j].first_date, alt[j].last_date);
			float rate1 = ((float)alt[j].sum_of_selling) / day;
			if (rate1 > rate)
			{
				int date,a; 
				char name[31]; 
				Swap(alt[j].sum_of_selling, alt[i].sum_of_selling);
				Swap(alt[j].last_date.day, alt[i].last_date.day);
				Swap(alt[j].first_date.day, alt[i].first_date.day);
				Swap(alt[j].last_date.month, alt[i].last_date.month);
				Swap(alt[j].first_date.month, alt[i].first_date.month);
				Swap(alt[j].last_date.year, alt[i].last_date.year);
				Swap(alt[j].first_date.year, alt[i].first_date.year);
				strcpy(name, alt[j].name);
				strcpy(alt[j].name, alt[i].name);
				strcpy(alt[i].name, name);
			}
		}
	}
	ofstream fout;
	fout.open("Output.txt");
	for (int i = 0; i <= count; ++i)
	{
		int day = DistanceBetween2Day(alt[i].first_date, alt[i].last_date);
		float rate = ((float)alt[i].sum_of_selling) / day;
		fout << i + 1 << ". " << alt[i].name << endl;
		fout << "  Rate: " << rate << endl;
	}
	fout.close();
}
void FindbyPrice(item shop[], int count)
{
	cout << "Enter the price you want to find: ";
	float price; 
	cin >> price;
	cout << "You want to find items which have its price: " << endl;
	cout << "1. Under " << price << endl;
	cout << "2. Over " << price << endl;
	cout << "3. Equal to " << price << endl;
	cout << "Enter 1, 2, 3 to choose: ";
	int key;
	key = _getch();
	cout << key - 48 << endl;
	switch (key)
	{
	case '1':
		for (int i = 0; i <= count; ++i)
			if (shop[i].price < price)
				PrintItem(shop[i]);
		break;
	case '2':
		for (int i = 0; i <= count; ++i)
			if (shop[i].price > price)
				PrintItem(shop[i]);
		break;
	case '3':
		for (int i = 0; i <= count; ++i)
			if (shop[i].price == price)
				PrintItem(shop[i]);
		break;
	default:
		cout << "No matching found." << endl;
		break;
	}
}
void FindByExpiredDay(item shop[], int count)
{
	cout << "You want to find items" << endl;
	cout << "1. Which will be expired after today ? " << endl;
	cout << "2. Which will be expired after this month?" << endl;
	cout << "3. Which will be expired after this year?" << endl;
	date today; 
	timeNow(today);
	int key; 
	int order = 1;
	key = _getch();
	cout << key - 48 << endl;
	switch (key)
	{
	case '1':
		for (int i = 0; i <= count; ++i)
		{
			if (shop[i].expired_date.day == today.day && shop[i].expired_date.month == today.month && shop[i].expired_date.year == today.year)
			{
				cout << order++ << ". " << endl;
				cout << "Barcode: " << shop[i].barcode << endl;
				cout << "Name: " << shop[i].name << endl;
				cout << "Expired day: " << shop[i].expired_date.day << "/" << shop[i].expired_date.month << "/" << shop[i].expired_date.year << endl;
			}
		}
		break;
	case '2':
		for (int i = 0; i <= count; ++i)
		{
			if (shop[i].expired_date.month == today.month && shop[i].expired_date.year == today.year)
			{
				cout << order++<< ". " << endl;
				cout << "Barcode: " << shop[i].barcode << endl;
				cout << "Name: " << shop[i].name << endl;
				cout << "Expired day: " << shop[i].expired_date.day << "/" << shop[i].expired_date.month << "/" << shop[i].expired_date.year << endl;
			}
		}
		break;
	case '3':
		for (int i = 0; i <= count; ++i)
		{
			if (shop[i].expired_date.year == today.year)
			{
				cout << order++<< ". " << endl;
				cout << "Barcode: " << shop[i].barcode << endl;
				cout << "Name: " << shop[i].name << endl;
				cout << "Expired day: " << shop[i].expired_date.day << "/" << shop[i].expired_date.month << "/" << shop[i].expired_date.year << endl;
			}
		}
		break;
	default:
		cout << "No matching found!" << endl;
		break;
	}
}
bool checkKeyWord(char name[20], char name1[20], int &order, int position, item shop[])
{
	for (int j = 0; j <= strlen(name); ++j)
	{
		if (name1[0] == name[j])
		{
			bool check = true;
			for (int t = 0; t <= strlen(name1); ++t)
			{
				if (name1[t] != name[j + t])
				{
					check = false;
				}
			}
			if (check)
			{
				cout << order++ << endl;
				PrintItem(shop[position]);
				return true;
			}
		}
	}
	return false;
}
void FindByKeyword(item shop[], int count)
{
	cout << "Do you want to find by?" << endl;
	cout << "1. Words " << endl;
	cout << "2. Number" << endl;
	cout << "Enter 1 or 2 to choose: " << endl;
	int key;
	key = _getch();
	cout << key - 48 << endl;
	if (key == '2')
	{
		bool check = false;
		cout << "Enter a number: " << endl;
		float number; 
		cin >> number; 
		int j = 1;
		for (int i = 0; i <= count; ++i)
		{
			check = false;
			if (shop[i].barcode == number) check = true;
			if (shop[i].price == number) check = true;
			if (shop[i].expired_date.day == number || shop[i].expired_date.month == number || shop[i].expired_date.year == number) check = true;
			if (check)
			{
				cout << j++ << endl;
				PrintItem(shop[i]);
			}
		}
		if (check == false)
			cout << "No matching found" << endl;
	}
	else
		if (key == '1')
		{
			cout << "Enter a word: " << endl;
			char name[31]; 
			cin.get(name, 20);
			int order = 1;
			for (int i = 0; i <= count; ++i)
			{
				if (checkKeyWord(shop[i].name, name, order, i, shop) == false)
				{
					if (checkKeyWord(shop[i].tag, name, order, i, shop) == false)
					{
						cout << "No matching found" << endl;
					}
				}
			}
		}
		else 
			cout << "No matching found" << endl;
}
void FindByCompoundedConditions1(item shop[], int count, arrayoftags tags)
{
	PrintListofTagtoFind(tags);
	date Date;
	cout << "Enter the number of the tag you want to find: ";
	int n;
	cin >> n;
	--n;
	cout << "Enter the expired date you want to find: ";
	cin >> Date.day >> Date.month >> Date.year;
	char name[10]; 
	bool check = false;
	strcpy(name, tags.tag[n].name);
	int order = 0;
	for (int i = 0; i <= count; ++i)
	{
		if (strcmp(name, shop[i].tag) == 0)
		{
			if (shop[i].expired_date.day == Date.day && shop[i].expired_date.month == Date.month && shop[i].expired_date.year == Date.year)
			{
				++order;
				cout << order << "." << endl;
				PrintItem(shop[i]);
				check = true;
			}
		}
	}
	if (!check) cout << "No matching found" << endl;
}
void FindByCompoundedConditions2(item shop[], int count, arrayoftags tags)
{
	PrintListofTagtoFind(tags);
	cout << "Enter the number of the tag you want to find: ";
	int n;
	cin >> n;
	--n;
	char name[10]; 
	bool check = false;
	strcpy(name, tags.tag[n].name);
	int order = 0;
	cout << "Enter the price you want to find: ";
	float price; cin >> price;
	cout << "You want to find items which have its price: " << endl;
	cout << "1. Under " << price << endl;
	cout << "2. Over " << price << endl;
	cout << "3. Equal to " << price << endl;
	cout << "Enter 1, 2, 3 to choose: ";
	int key;
	key = _getch();
	cout << key - 48 << endl;
	for (int i = 0; i <= count; ++i)
	{
		if (strcmp(name, shop[i].tag) == 0)
		{
			switch (key)
			{
			case '1':
				if (shop[i].price < price)
				{
					++order;
					cout << order << "." << endl;
					PrintItem(shop[i]);
					check = true;
				}
				break;
			case '2':
				if (shop[i].price == price)
				{
					++order;
					cout << order << "." << endl;
					PrintItem(shop[i]);
					check = true;
				}
				break;
			case '3':
				if (shop[i].price > price)
				{
					++order;
					cout << order << "." << endl;
					PrintItem(shop[i]);
					check = true;
				}
				break;
			}
		}
	}
	if (!check) cout << "No Matching Found" << endl;
}
void ClearAllShop(item shop[], int& count)
{
	for (int i = 0; i <= count; ++i)
	{
		shop[i].barcode = -1;
		shop[i].price = 0;
		shop[i].name[0] = NULL;
		shop[i].tag[0] = NULL;
		shop[i].sum_of_selling = 0;
		shop[i].stock_level = 0;
	}
	count = 0;
}
void ClearItem(item shop[], int& count, int position)
{
	while (position < count)
	{
		shop[position].barcode = shop[position + 1].barcode;
		shop[position].price = shop[position + 1].price;
		shop[position].sum_of_selling= shop[position + 1].sum_of_selling;
		shop[position].stock_level= shop[position + 1].stock_level;
		shop[position].first_date.day = shop[position + 1].first_date.day;
		shop[position].first_date.month= shop[position + 1].first_date.month;
		shop[position].first_date.year = shop[position + 1].first_date.year;
		shop[position].last_date.day = shop[position + 1].last_date.day;
		shop[position].last_date.month = shop[position + 1].last_date.month;
		shop[position].last_date.year = shop[position + 1].last_date.year;
		shop[position].expired_date.day = shop[position + 1].expired_date.day;
		shop[position].expired_date.month = shop[position + 1].expired_date.month;
		shop[position].expired_date.year = shop[position + 1].expired_date.year;
		strcpy(shop[position].name, shop[position + 1].name);
		strcpy(shop[position].tag, shop[position + 1].tag);
		++position;
	}
	shop[count].tag[0] = NULL;
	shop[count].name[0] = NULL;
	--count;
}
void ClearTag(arrayoftags& tags, char name[])
{
	int position;
	for (int i = 0; i <= tags.count; ++i)
	{
		if (strcmp(name, tags.tag[i].name) == 0)
		{
			position = i;
			break;
		}
	}
	while (position < tags.count)
	{
		strcpy(tags.tag[position].name, tags.tag[position + 1].name);
		++position;
	}
	tags.tag[tags.count].name[0] = NULL;
	--tags.count;
}
void ClearByBarcode(item shop[], int& count)
{
	cout << "Enter the barcode of item you want to delete:";
	int barcode;
	cin >> barcode;
	for (int i = 0; i <= count; ++i)
	{
		if (barcode == shop[i].barcode)
		{
			ClearItem(shop, count, i);
			break;
		}
	}
}
void ClearByTag(item shop[], int& count, arrayoftags &tags)
{
	PrintListofTagtoFind(tags);
	cout << "Enter the number of the tag you want to find: ";
	int n, i = 0;
	cin >> n;
	--n;
	char name[10]; 
	strcpy(name, tags.tag[n].name);
	while (i <= count)
	{
		if (strcmp(shop[i].tag, name) == 0)
		{
			ClearItem(shop, count, i);
		}
		else ++i;
	}
	ClearTag(tags, name);
}

