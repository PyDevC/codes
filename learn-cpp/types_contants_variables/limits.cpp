#include<iostream>
#include<climits>

// climits contains the limit of range for each data type in cpp and c

using namespace std;

int main() 
{
    cout << "Range of types int and unsigned int" << endl << endl;
    cout << "int " << INT_MAX << endl;
    cout << "int " << INT_MIN << endl;
    cout << "unsigned " << UINT_MAX << endl; // since unsigned int starts with 0. ther is no UINT_MIN
}
