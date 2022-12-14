#include <bits/stdc++.h>
#include <string.h>
using namespace std;
string convert(string hexa)
{
    long int i = 0;
    string bin = "";
    while (hexa[i])
    {
        switch (hexa[i])
        {
        case '0':
            bin += "0000";
            break;
        case '1':
            bin += "0001";
            break;
        case '2':
            bin += "0010";
            break;
        case '3':
            bin += "0011";
            break;
        case '4':
            bin += "0100";
            break;
        case '5':
            bin += "0101";
            break;
        case '6':
            bin += "0110";
            break;
        case '7':
            bin += "0111";
            break;
        case '8':
            bin += "1000";
            break;
        case '9':
            bin += "1001";
            break;
        case 'A':
        case 'a':
            bin += "1010";
            break;
        case 'B':
        case 'b':
            bin += "1011";
            break;
        case 'C':
        case 'c':
            bin += "1100";
            break;
        case 'D':
        case 'd':
            bin += "1101";
            break;
        case 'E':
        case 'e':
            bin += "1110";
            break;
        case 'F':
        case 'f':
            bin += "1111";
            break;
        }
        i++;
    }
    return bin;
}
int main()
{
    string line;
    vector<string> Address;
    ifstream CI("Hex_Input.txt");
    if (CI.is_open())
    {
        while (getline(CI, line))
        {
            Address.push_back((line));
        }
    }
    else
        cout << "Unable to open file";
    CI.close();

    ofstream CIout("Cache_Input.txt");
    if (CIout.is_open())
    {
        for (int i = 0; i < Address.size(); i++)
        {

            CIout << convert(Address[i]) << endl;
        }
    }
    else
        cout << "Unable to open file"
             << "Cache_Input.txt" << endl;
    CIout.close();

    return 0;
}