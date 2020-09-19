#include<iostream>
#include<stdlib.h>
#include <time.h>
using namespace std;

int main(int argc, const char** argv) {
    srand(time(0));

    int number = rand() % 100 + 1;
    int guess1; 
    int guess2;
    int low = 1;
    int high = 100;

    cout<<"Player 1, Please enter your guess"<<endl;
    cin>> guess1 ;
    cout<<"Player 2, Please enter your guess"<<endl;
    while ( cin>>guess2)
    {
        if(guess1 > low && guess2 > low && guess1 < high && guess2 < high){
            if(number == guess1 && number == guess2){
                        cout<<"It's a tie"<<endl;
                        break;
                    }
                    else if (number == guess1){
                        cout<<"Player 1 you win"<<endl;
                        break;
                    }
                    else if (number == guess2){
                        cout<<"Player 2 you win"<<endl;
                        break;
                    }
                    else{
                         if (guess1 < number){
            low = guess1+ 1;
            }
            else if (guess2 < number){
            low = guess2+ 1;
            }
            if (guess1 > number){
            high = guess1+ 1;
            }
            else if (guess2 > number){
            high = guess2+ 1;
            }
                        cout<<"No one's correct, try to input higher than "<< low << " and lower than "<< high << endl;
                        cout<<"Player 1, Please enter your guess"<<endl;
                        cin>>guess1;
                        cout<<"Player 2, Please enter your guess"<<endl;
                        continue;
                    }
        }
        else{
            cout<<"Invalid number, please enter number between range "<< low << " - " << high <<endl;
           
                        cout<<"Player 1, Please enter your guess"<<endl;
                        cin>>guess1;
                        cout<<"Player 2, Please enter your guess"<<endl;
        }
       
    }
    
    return 0;
}
