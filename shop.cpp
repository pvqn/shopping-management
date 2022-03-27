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
int main()
{
    item shop[100];
    item bill[1000];
    arrayoftags tags;
    int count = -1;
    float price = 0;
    members Members;
    menu();
    int key;
    key = _getch();
    cout << key - 48 << endl;
    while (key != '0')
    {
        switch (key)
        {
        case '0':
            return 0;
            break;
        case '1':
            system("cls");
            initialize_first(shop, count, tags);
            break;
        case '2':
            system("cls");
            initialize(shop, count, tags);
            restock_item(shop, count, tags);
            break;
        case '3':
            system("cls");
            initialize(shop, count, tags);
            initialize1(Members);
            sellitem(shop, count, bill, Members);
            break;
        case '4':
            system("cls");
            initialize(shop, count, tags);
            FindBestAndWorst(shop, count);
            break;
        case '5':
            system("cls");
            initialize(shop, count, tags);
            CheckShouldAdd(shop, count);
            break;
        case '6':
            system("cls");
            initialize(shop, count, tags);
            CheckExpiredDay(shop, count);
            break;
        case '7':
            system("cls");
            initialize(shop, count, tags);
            FindByBarcode(shop, count);
            break;
        case '8':
            system("cls");
            initialize(shop, count, tags);
            FindByTags(shop, tags, count);
            break;
        case '9':
            system("cls");
            initialize(shop, count, tags);
            FindbyPrice(shop, count);
            break;
        case '10':
            system("cls");
            initialize(shop, count, tags);
            FindbyPrice(shop, count);
            break;
        case '11':
            system("cls");
            initialize(shop, count, tags);
            FindByKeyword(shop, count);
            break;
        case '12':
            system("cls");
            initialize(shop, count, tags);
            FindByCompoundedConditions1(shop, count, tags);
            break;
        case '13':
            system("cls");
            initialize(shop, count, tags);
            FindByCompoundedConditions2(shop, count, tags);
            break;
        case '14':
            system("cls");
            initialize(shop, count, tags);
            PrintOutItemtoFile(shop, count);
            break;
        case '15':
            system("cls");
            initialize(shop, count, tags);
            sortRate(shop, count);
            break;
        case '16':
            system("cls");
            initialize(shop, count, tags);
            FixInformation(shop, tags, count);
            break;
        case '17':
            system("cls");
            initialize(shop, count, tags);
            ClearByBarcode(shop, count);
            break;
        case '18':
            system("cls");
            initialize(shop, count, tags);
            ClearByTag(shop, count, tags);
            break;
        case '19':
            system("cls");
            initialize(shop, count, tags);
            ClearAllShop(shop, count);
            break;
        default:
            cout << "no matching found" << endl;
            break;
        }
        menu();
        key = _getch();
        cout << key - 48 << endl;
    }

    return 0;
}