#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
    float A = 4.0;
    float B = 3.0;
    float C = 2.0;
    float D = 1.0;
    float F = 0.0;

    float gradeSum = 0;
    char gradeLetter;
    float totalCredits = 0;
    float credits;
    float GPA;
    cout << "No. of credits of your course (0 to stop): ";
    cin >> credits;
    float round = 0;
    while (credits > 0)
    {
        cout << "Your letter grade (A, B, C ,D or F): ";
        cin >> gradeLetter;
        if (gradeLetter == 'A')
        {
            gradeSum += (A * credits);
        }
        else if (gradeLetter == 'B')
        {
            gradeSum += (B * credits);
        }
        else if (gradeLetter == 'C')
        {
            gradeSum += (C * credits);
        }
        else if (gradeLetter == 'D')
        {
            gradeSum += (D * credits);
        }
        totalCredits += credits;
        round++;
        cout << "No. of credits of your course (0 to stop): ";
        cin >> credits;
    }
    GPA = gradeSum / totalCredits;
    cout << "You have taken a total of " << totalCredits << " credits.." << endl;
    cout << "And your GPA is " << GPA;

    return 0;
}
