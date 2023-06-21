#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

struct InventoryItem
{
    string id;
    string name;
    string quantity;
    string date;
};

void getStarted()
{
    cout << "" << endl;
    cout << "Welcome to Teta Lena's CPP NE Practical application" << endl;
    cout << "" << endl;
    cout << "Need help getting started ? Enter 'help' " << endl;
    cout << "" << endl;
    cout << "Enter 'Exit' to log out of the application" << endl;
    cout << "" << endl;
};
string toUpper(string &text)
{
    string texttoupper = text;
    for (char &c : texttoupper)
    {
        c = toupper(c);
    }
    return texttoupper;
}
string toLower(string &text)
{
    string texttolower = text;
    for (char &c : texttolower)
    {
        c = tolower(c);
    }
    return texttolower;
}
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
bool isAddItemCommandValid(vector<string> commandOptions)
{
    if (commandOptions.size() == 5)
    {
        return true;
    }
    return false;
}
void addItem(string id, string name, string quantity, string date)
{
    ofstream file;
    file.open("inventory.csv", ios::app);
    if (file.is_open())
    {
        file << id << "," << name << "," << quantity << "," << date << endl;
        cout << "" << endl;
        cout << "Item addded successfully" << endl;
    }
    else
    {
        cout << "Failed to open file" << endl;
    }

    file.close();
};

// bool sortingAlgorithm(InventoryItem &item1, InventoryItem &item2)
// {
//     return item1.name < item2.name;
// }
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
    // sort(inventoryItems.begin(), inventoryItems.end(), sortingAlgorithm);
    for (const auto &item : inventoryItems)
    {
        cout << "Item ID: " << item.id << "                         Item Name: " << item.name << "                       Quantity: " << item.quantity << "                   RegDate: " << item.date << endl;
    }
    file.close();
};

void getHelp()
{
    cout << "" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "*                      Commands syntaxes                      *" << endl;
    cout << "--------------------------------------------------------------" << endl;
    cout << "     itemadd <item_id> <item_name> <quantity> <registration_date>" << endl;
    cout << "     itemslist" << endl;
};

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
                    {
                        string item_id = commandOptions.at(1);
                        string item_name = commandOptions.at(2);
                        string item_quantity = commandOptions.at(3);
                        string item_registration_date = commandOptions.at(4);

                        addItem(item_id, item_name, item_quantity, item_registration_date);
                    }
                }
                else
                {
                    cout << "Invalid command" << endl;
                }
            }

            else if (commandOptions.at(0) == "help")
            {
                getHelp();
            }
            else if (commandOptions.at(0) == "exit")
            {
                break;
            }
            else if (commandOptions.at(0) == "itemslist")
            {
                listItems();
            }
            else
            {
                cout << "Command not part of command list , try 'Help' to see available commands" << endl;
            }
        }
        else
        {
            cout << " Invalid command .. Type 'Help' to see command list" << endl;
        }
    }
    return 0;
}