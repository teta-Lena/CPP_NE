#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <regex>

using namespace std;

// structure used to store our inventory object
struct InventoryItem
{
    string id;
    string name;
    string quantity;
    string date;
};

// screen displayed on startup
void getStarted()
{
    cout << "" << endl;
    cout << "Welcome to Teta Lena's CPP NE Practical application" << endl;
    cout << "" << endl;
    cout << "Need help getting started? Enter 'help'" << endl;
    cout << "" << endl;
    cout << "Enter 'Exit' to log out of the application" << endl;
    cout << "" << endl;
}

// to lower case to disable case-sensitivity
string toLower(string &text)
{
    string texttolower = text;
    for (char &c : texttolower)
    {
        c = tolower(c);
    }
    return texttolower;
}

// split string based on a certain delimiter
vector<string> split(string userRequest, char delimiter)
{
    stringstream lineBuffer(userRequest);
    string option;
    vector<string> options;
    while (getline(lineBuffer, option, delimiter))
    {
        options.push_back(option);
    }

    return options;
}
bool isIdExists(const string &id)
{
    ifstream file("inventory.csv");
    string line;
    while (getline(file, line))
    {
        vector<string> row = split(line, ',');
        if (row.size() > 1 && row[0] == id)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// check if itemadd command is valid
bool isAddItemCommandValid(vector<string> commandOptions)
{
    if (commandOptions.size() == 5 && !isIdExists(commandOptions[1]))
    {
        return true;
    }
    return false;
}

// check if a string is a valid number
bool isNumeric(const string &str)
{
    return regex_match(str, regex("\\d+"));
}

// check if a string consists only of alphabetic characters
bool isString(const string &str)
{
    return regex_match(str, regex("[A-Za-z]+"));
}

// check if ID already exists

// check if item with specified ID and name combination already exists
bool isItemExists(const string &id, const string &name)
{
    ifstream file("inventory.csv");
    string line;
    while (getline(file, line))
    {
        vector<string> row = split(line, ',');
        if (row.size() > 1 && row[0] == id && row[1] == name)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// check if an item with specified name already exists
bool isNameExists(const string &name)
{
    ifstream file("inventory.csv");
    string line;
    while (getline(file, line))
    {
        vector<string> row = split(line, ',');
        if (row.size() > 1 && row[1] == name)
        {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// check if a date is valid and in the format "yy-mm-dd"
bool isValidDate(const string &date)
{
    regex dateRegex("^\\d{4}-\\d{2}-\\d{2}$");
    if (!regex_match(date, dateRegex))
    {
        return false;
    }

    int year = stoi(date.substr(0, 2));
    int month = stoi(date.substr(3, 2));
    int day = stoi(date.substr(6, 2));

    if (year < 0 || year > 99 || month < 1 || month > 12 || day < 1 || day > 31)
    {
        return false;
    }

    // Validate February's days in a leap year
    if (month == 2)
    {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > 29 || (day == 29 && !isLeapYear))
        {
            return false;
        }
    }

    return true;
}

// add item function
void addItem(string id, string name, string quantity, string date)
{
    ofstream file;
    file.open("inventory.csv", ios::app);
    if (file.is_open())
    {
        file << id << "," << name << "," << quantity << "," << date << endl;
        cout << "" << endl;
        cout << "Item added successfully" << endl;
    }
    else
    {
        cout << "Failed to open file" << endl;
    }

    file.close();
}

// sorting algorithm
bool sortingAlgorithm(InventoryItem &item1, InventoryItem &item2)
{
    return item1.name < item2.name;
}

// list all items
void listItems()
{
    ifstream file("inventory.csv");
    string line;
    string data;
    vector<InventoryItem> inventoryItems;

    vector<string> row;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            vector<string> row = split(line, ',');
            InventoryItem item;
            item.id = row[0];
            item.name = row[1];
            item.quantity = row[2];
            item.date = row[3];
            inventoryItems.push_back(item);
        }
    }
    else
    {
        cout << "Failed to open file" << endl;
    }
    sort(inventoryItems.begin(), inventoryItems.end(), sortingAlgorithm);
    for (const auto &item : inventoryItems)
    {
        cout << "Item ID: " << item.id << "   Item Name: " << item.name << "      Quantity: " << item.quantity << "      RegDate: " << item.date << endl;
    }
    file.close();
}

// help menu
void getHelp()
{
    cout << "" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "*                      Commands syntaxes                      *" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "     itemadd <item_id> <item_name> <quantity> <registration_date>" << endl;
    cout << "     itemslist" << endl;
}

int main()
{
    string userRequest;
    string userRequest_toLower;

    getStarted();

    while (true)
    {
        getline(cin, userRequest);

        userRequest_toLower = toLower(userRequest);
        vector<string> commandOptions = split(userRequest_toLower, ' ');

        if (commandOptions.size() >= 1)
        {
            if (commandOptions.at(0) == "itemadd")
            {
                if (isAddItemCommandValid(commandOptions))
                {
                    string item_id = commandOptions.at(1);
                    string item_name = commandOptions.at(2);
                    string item_quantity = commandOptions.at(3);
                    string item_registration_date = commandOptions.at(4);

                    addItem(item_id, item_name, item_quantity, item_registration_date);
                }
                else if (isIdExists(commandOptions.at(1)))
                {
                    cout << "" << endl;
                    cout << "The ID already exists. Please enter another ID." << endl;
                }
                else
                {
                    cout << "" << endl;
                    cout << "Invalid command or missing/invalid arguments. Please try again." << endl;
                }
            }
            else if (commandOptions.at(0) == "itemslist")
            {
                listItems();
            }
            else if (commandOptions.at(0) == "help")
            {
                getHelp();
            }
            else if (commandOptions.at(0) == "exit")
            {
                break;
            }
            else
            {
                cout << "" << endl;
                cout << "Invalid command. Please try again." << endl;
            }
        }
    }

    return 0;
}
