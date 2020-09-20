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
    int player;

    while (A != 0 || B != 0 || C != 0)
    {
        rounds % 2 == 0 ? player = 2 : player = 1;
        char heap;
        int numOfCoins;
        cout << "Round " << rounds << " A: " << A << " B: " << B << " C: " << C << endl;
        cout << "Player " << player << " please select a heap (A, B, or C): ";
        cin >> heap;
        int numLeft;
        if (heap == 'A')
        {
            numLeft = A;
        }
        else if (heap == 'B')
        {
            numLeft = B;
        }
        else if (heap == 'C')
        {
            numLeft = C;
        }
        while (heap != 'A' && heap != 'B' && heap != 'C' || numLeft == 0)
        {
            cout << "Invalid Input" << endl;
            cout << "Player " << player << " please select a heap (A, B, or C): ";
            cin >> heap;
            if (heap == 'A')
            {
                numLeft = A;
            }
            else if (heap == 'B')
            {
                numLeft = B;
            }
            else if (heap == 'C')
            {
                numLeft = C;
            }
        }
        if (heap == 'A')
        {
            numLeft = A;
        }
        else if (heap == 'B')
        {
            numLeft = B;
        }
        else if (heap == 'C')
        {
            numLeft = C;
        }
        cout << "Player " << player << " please select the number of coins to remove (1, 2 or 3): ";

        cin >> numOfCoins;
        while (numOfCoins == 0 || numOfCoins > 3 || numOfCoins > numLeft)
        {
            cout << "Invalid Input" << endl;
            cout << "Player " << player << " please select the number of coins to remove (1, 2 or 3):  ";
            cin >> numOfCoins;
        }

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
    cout << "Player " << player << " removes the last coin. Player " << player << " wins the game!" << endl;

    return 0;
}
