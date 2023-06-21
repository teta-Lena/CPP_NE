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
// void addItem(){

// }

string split(string userRequest)
{
    stringstream lineBuffer(userRequest);
    string option;
    vector<string> options;
    while (getline(lineBuffer, option, ' '))
    {
        return option;
    }
}
void sortData(vector<string> &data)
{
    sort(data.begin(), data.end());
}

bool isAddItemCommandValid(string request)
{
    vector<string> options;
    string data;
    stringstream command(request);

    while (getline(command, data, ' '))
    {
        options.push_back(data);
    }
    if (options.size() < 4)
    {
        cout << "Invalid Command" << endl;
        return false;
    }
    return true;
}
int main()
{
    string userRequest;

    string userRequest_toLower;

    getStarted();

    getline(cin, userRequest);

    userRequest_toLower = toLower(userRequest);

    string command = split(userRequest_toLower);

    if (command == "additem")
    {
        cout << "ADD ITEM" << endl;
    }
    if (command == "itemslist")
    {
        cout << "LIST ITEMS" << endl;
    }
    if (command == "exit")
    {
        cout << "Closed app successfully" << endl;
        return 0;
    }
    getStarted();

    // split(userRequest);

    // cout << userRequest_toLower;

    return 0;
}