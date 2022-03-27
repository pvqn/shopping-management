struct date
{
    int day;
    int month;
    int year;
};
struct person
{
    char name[20];
    date dob;
    int frequency = 0;
};
struct members
{
    int count = -1;
    person Person[1000];
};
struct item
{
    char name[20];
    char tag[20];
    float price = 0;
    int barcode = -1;
    int stock_level = 0;
    date expired_date, first_date, last_date;
    int min_stock_level = 10;
    int sum_of_selling = 0;
};
struct arrayofstring
{
    char name[10];
};
struct arrayoftags
{
    int count = -1;
    arrayofstring tag[100];
};
void initialize1(members& Members);
void SavetoFile1(members Members);
void menu();
bool CheckTagsExist(arrayoftags tags, char tag[10]);
void timeNow(date& Date);
bool initialize(item shop[], int& count, arrayoftags& tags);
void SaveToFile(item shop[], int count);
void printoutbill(item bill[], int count, float price, members& Members, char name[]);
void restock_item(item shop[], int& count, arrayoftags& tags);
void sellitem(item shop[], int count, item bill[],  members& Members);
void initialize_first(item* shop, int& count, arrayoftags& tags);
bool IsLeap(int year);
int howmanyday(int month, int year);
int DistanceBetween2Day(date Date1, date Date2);
void Print_Result(item Item, bool isBest);
void FindBestAndWorst(item shop[], int count);
void PrintItem(item Item);
void CheckShouldAdd(item shop[], int count);
void CheckExpiredDay(item shop[], int count);
void FindByBarcode(item shop[], int count);
void PrintListofTagtoFind(arrayoftags tags);
void FindByTags(item shop[], arrayoftags tags, int& count);
void PrintOutItemtoFile(item shop[], int count);
bool ShouldDeleteTag(item shop[], char tag[], int count, int& position, arrayoftags tags);
void FixInformation(item shop[], arrayoftags tags, int count);
void Swap(int& a, int& b);
void sortRate(item shop[], int count);
void FindbyPrice(item shop[], int count);
void FindByExpiredDay(item shop[], int count);
bool checkKeyWord(char name[20], char name1[20], int& order, int position, item shop[]);
void FindByKeyword(item shop[], int count);
void FindByCompoundedConditions1(item shop[], int count, arrayoftags tags);
void FindByCompoundedConditions2(item shop[], int count, arrayoftags tags);
void ClearAllShop(item shop[], int& count);
void ClearItem(item shop[], int& count, int position);
void ClearTag(arrayoftags& tags, char name[]);
void ClearByBarcode(item shop[], int& count);
void ClearByTag(item shop[], int& count, arrayoftags& tags);

