#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char const *argv[])
{
    int player;

    char heap = 'A';
    cout << "Player"
         << " please select a heap (A, B, or C): ";
    cin >> heap;
    while (heap != 'A')
    {
        cout << "Invalid Input" << endl;
        cout << "Player " << player << " please select a heap (A, B, or C): ";
        cin >> heap;
    }
    cout << "true";
    return 0;
}
