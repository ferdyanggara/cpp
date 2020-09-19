#include<iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    int size; 
    cout<<"Please enter your desired rat size: "<<endl;
    cin>>size;

// normal rat
    // for (int i = 0; i < size; i++)
    // {
    //     for (int j = 0 ; j <= i; j++){
    //     cout<<"*";
    //     }
    //     cout<<endl;
    // }
// fat rat
//  for (int i = 0; i < size*2; i+=2)
//     {
//         for (int j = 0 ; j <= i; j++){
//         cout<<"*";
//         }
//         cout<<endl;
//     }
// hollow rat
//  for (int i = 0; i < size; i++)
//     {
//         if (i>=2 && i< (size-1))
//            {
//                for (int x = 0; x <= i ; x++)
//                { 
//                    if (x==0 || x == i){
//                    cout<<"*";
//                    } else{
//                     cout<<" ";
//                    }
//                }
//             cout<<endl;
//            } else if (i>=0 && i<2 || i==(size-1)){
//         for (int j = 0 ; j <= i; j++){
//             cout<<"*";
//             }
//             cout<<endl;
//         }
        
//     }
// upside down rat
//  for (int i = size; i > 0; i--)
//     {
//         for (int j = 0 ; j < i; j++){
//         cout<<"*";
//         }
//         cout<<endl;
//     }
// row of rat





    return 0;
}
