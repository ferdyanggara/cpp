#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char const *argv[])
{
    srand(time(0));
    int A = rand() % 4 + 3;
    int B = rand() % 4 + 3;
    int C = rand() % 4 + 3;
    int totalCoins = A + B + C;
    cout << "Welcome to the Nim game!" << endl;
    int rounds = 1;

    while (A && B && C != 0)
    {
        int player;
        rounds % 2 == 0 ? player = 2 : player = 1;
        char heap;
        int numOfCoins;
        cout << "Round " << rounds << " A: " << A << " B: " << B << " C: " << C << endl;
        cout << "Player " << player << " please select a heap (A, B, or C): ";
        cin >> heap;
        while (heap != 'A' && heap != 'B' && heap != 'C')
        {
            cout << "Invalid Input" << endl;
            cout << "Player " << player << " please select a heap (A, B, or C): ";
            cin >> heap;
        }
        cout << "Player " << player << " please select the number of coins to remove (1, 2 or 3): ";
        cin >> numOfCoins;
        cout << "Player " << player << " removes " << numOfCoins << " coin(s) from heap " << heap << endl;
        rounds++;
        // count logic
        if (heap == 'A')
        {
            A -= numOfCoins;
        }
        else if (heap == 'B')
        {
            B -= numOfCoins;
        }
        else if (heap == 'C')
        {
            C -= numOfCoins;
        }
        else
        {
            cout << "Invalid input" << endl;
        }
    }

    return 0;
}
