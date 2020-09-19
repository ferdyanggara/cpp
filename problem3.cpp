#include<iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    float pigWeight = 4.5;
    float sheep = 3.0;
    float totalWeight = 36.0;

    for (float i = 0; i <= totalWeight ; i++)
    {
        for (float j = 1; j <= totalWeight; i++)
        {
            if ((i * pigWeight + j  * sheep )== 36 )
            cout<< i << " and " << j <<endl;
        }
        
    }
    


    return 0;
}
