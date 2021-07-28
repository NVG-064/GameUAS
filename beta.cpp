#include<iostream>
#include<fstream>
using namespace std;



struct history{
    string character = "Lylia";
    string weapon = "Magic Wand";
    string enemy = "Final boss 1";
}gameHistory;

int main()
{
    int a;
    cout << "Enter number : " << endl;
    cin >> a;

    // open file stream
    ofstream file;

    file.open("battleHistory.log");
    file << gameHistory.character << "\n" << gameHistory.weapon << "\n" << gameHistory.enemy << "\n\n";

    file.close();
    return 0;
}