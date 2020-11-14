#include <iostream>
#include <limits>
#include <assert.h>

using namespace std;

// C string termination character
const char NULL_CHAR = '\0';

// The "not found" flag
const int NOT_FOUND = -1;

// Single character wildcard
const char DOT = '.';

// Zero or single character wildcard
const char QMARK = '?';

// Zero or more character wildcard
const char PERCENT = '%';

// Matches the beginning of a string
const char CARET = '^';

int findSubLenAtStrPosWithPercent(const char str[], const char pattern[], int strPos, int patPos);

bool checkQuestionMark(const char pattern[], int patPos = 0){
    if(pattern[patPos] == NULL_CHAR)
        return true;
    if(pattern[patPos] != QMARK)
        return false;
    return checkQuestionMark(pattern, patPos + 1);
}

bool checkPercentMark(const char pattern[], int patPos = 0){
    if(pattern[patPos] == NULL_CHAR)
        return true;
    if(pattern[patPos] != PERCENT)
        return false;
    return checkQuestionMark(pattern, patPos + 1);
}

int minString(const char str[], const char pattern[], int strPos, int patPos){
    if(pattern[patPos] == NULL_CHAR || str[strPos] == NULL_CHAR)
        return 0;
    return minString(str, pattern, strPos + 1, patPos + 1) + 1;
}

// bool checkZeroCharWilcard(const char str[], const char pattern[], int strPos, int patPos){
//     if(pattern[patPos] == NULL_CHAR && pattern[patPos - 1] == QMARK)
//         return true;

//     if(pattern[patPos] == QMARK){
//         return checkZeroCharWilcard(str, pattern, strPos, patPos + 1);
//     }
//     if(str[strPos] == patPos){
//         return true;
//     }
//     return false;
// }

// bool checkOneCharWildcard(const char str[], const char pattern[], int strPos, int patPos){
//     if(str[strPos] == NULL_CHAR)
//         return false;
    
//     if(pattern[patPos] == QMARK)
//         return checkOneCharWildcard(str, pattern, strPos + 1, patPos + 1);
//     if(pattern[patPos] == str[strPos])
//         return true;
//     return false;
// }

int findSubLenAtStrPosWithQmark(const char str[], const char pattern[], int strPos = 0, int patPos = 0)
{
    // cout << "str: " << str[strPos] << ", pat: " << pattern[patPos] << endl;
    if(pattern[patPos] == NULL_CHAR)
        return 0;

    if(str[strPos] == NULL_CHAR){
        if(pattern[patPos] != NULL_CHAR && !checkQuestionMark(pattern, patPos))
            return NOT_FOUND;
        return 0;
    }

    //case 1: when chars in strPos and patPos are the same
    if (pattern[patPos] == str[strPos])
    {
        if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched
            return 1;
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPosWithQmark(str, pattern, strPos + 1, patPos + 1); // check if the remaining part of the pattern 
                                                                                      // matches with that of the substring
        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
            return 1 + result;
    }
    //case 2: when we encounter the qmark
    else if(pattern[patPos] == QMARK){
        //determine whether ? is zero-character or 1 character wildcarc
        
        // check if remaining pattern is all questionamarks
        if(checkQuestionMark(pattern, patPos))
            return minString(str, pattern, strPos, patPos);

        // assume that qmark is zero-char wildcard
        int prelimResult = findSubLenAtStrPosWithQmark(str, pattern, strPos, patPos + 1);
        // if the qmark is a one-char wilcard
        if(prelimResult == NOT_FOUND){
            int result = findSubLenAtStrPosWithQmark(str, pattern, strPos + 1, patPos + 1);
            if(result != NOT_FOUND)
                return result + 1;
        }
        else
        {
            return prelimResult;
        }
        

        //otherwise, current questionmark is zero wildcard
        // cout << "zeroChar" << endl;
    }

    // cout << "NOt Found !" << endl;
    // case 3: chars are different
    return NOT_FOUND;
}

int matchSubWithQmark(const char str[], const char pattern[], int &length, int start = 0)
{
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    cout << "HI!!" << endl;
    int testLength = findSubLenAtStrPosWithQmark(str, pattern, start);
    if (testLength != NOT_FOUND) {
        cout << "Found!" << endl;
        length = testLength;
        return start;
    }
    return matchSubWithQmark(str, pattern, length, start + 1);
}

int main(){
    int length;
    int index;

    // length = findSubLenAtStrPosWithQmark("pp", "?pp");
    // index = matchSubWithQmark("lj", "?", length); // 0 and 1
    // index = matchSubWithQmark("ilolol", "?ol", length); // 1 and 3
    // index = matchSubWithQmark("ilolol", "?ilo", length); // 0 and 3
    // index = matchSubWithQmark("iloolol", "lol?", length); // 4 and 3
    // index = matchSubWithQmark("ilolool", "lo?l", length); // 1 and 3
    // index = matchSubWithQmark("iloolol", "lo?l", length); // 1 and 4
    // index = matchSubWithQmark("illl", "lo?l", length); // NOT_FOUND AND 0
    // index = matchSubWithQmark("comethru", "???c?o?m?e????r?u??", length); // 0 and 8
    // index = matchSubWithQmark("comp", "???c????", length);
    // length = findSubLenAtStrPosWithQmark("c", "c????p");
    // length = findSubLenAtStrPosWithQmark("idkk", "???k?");

    // length = findSubLenAtStrPosWithQmark("pp", "?pp");


    cout << "Index: " << index << endl;
    cout << "Length: " << length << endl;
    return 0;
}