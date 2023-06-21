#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

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
vector<string> split(string userRequest)
{
    stringstream lineBuffer(userRequest);
    string option;
    vector<string> options;
    while (getline(lineBuffer, option, ' '))
    {
        options.push_back(option);
    }

    return options;
}
bool isAddItemCommandValid(vector<string> commandOptions)
{
    if (commandOptions.size() < 5)
    {
        return false;
    }
    return true;
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
};
int main()
{
    string userRequest;

    string userRequest_toLower;

    getStarted();

    getline(cin, userRequest);

    userRequest_toLower = toLower(userRequest);
    vector<string> commandOptions = split(userRequest_toLower);

    if (commandOptions.at(0) == "additem")
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
            cout << "It is a valid command" << endl;
        }
        else
        {
            cout << "Invalid command" << endl;
        }
    }
}