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

int minStringPercent(const char str[], int strPos){
    if(str[strPos] == NULL_CHAR)
        return 0;
    return minStringPercent(str, strPos + 1) + 1;
}

// bool checkOneCharWildcard(const char str[], const char pattern[], int strPos, int patPos){
//     if(str[strPos] == NULL_CHAR)
//         return false;
    
//     if(pattern[patPos] == QMARK)
//         return checkOneCharWildcard(str, pattern, strPos + 1, patPos + 1);
//     if(pattern[patPos] == str[strPos])
//         return true;
//     return false;
// }

int getOffsetWildCard(const char str[], const char pattern[], int strPos, int patPos){
    // cout << "Nstr: " << str[strPos] << endl;
    if(str[strPos] == NULL_CHAR)
        return NOT_FOUND;
    
    if(str[strPos] == pattern[patPos + 1]){
        // cout << "strPos: " << strPos << endl;
        int testOffset = getOffsetWildCard(str, pattern, strPos + 1, patPos);
        if(testOffset != NOT_FOUND){
            return testOffset + 1;
        }
            
        return 0;
    }
    int result = getOffsetWildCard(str, pattern, strPos + 1, patPos);
    if(result != NOT_FOUND)
        return result + 1;
    return result;
}

int findSubLenAtStrPosWithPercent(const char str[], const char pattern[], int strPos = 0, int patPos = 0)
{
    cout << "str: " << str[strPos] << ", pat: " << pattern[patPos] << endl;
    if(pattern[patPos] == NULL_CHAR)
        return 0;

    if(str[strPos] == NULL_CHAR){
        if(pattern[patPos] != NULL_CHAR && !checkPercentMark(pattern, patPos))
            return NOT_FOUND;
        return 0;
    }

    if (pattern[patPos] == str[strPos])
    {
        if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched
            return 1;
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPosWithPercent(str, pattern, strPos + 1, patPos + 1); // check if the remaining part of the pattern 
                                                                                      // matches with that of the substring
        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
            return 1 + result;
    }
    else if(pattern[patPos] == PERCENT){
        // case where end of pattern consists of percents
        if(checkPercentMark(pattern, patPos)){
            return minStringPercent(str, strPos);
        }

        // pattern : c%%%%%%%%%%%%%%%%%p === c%p
        // str: cp


        if(pattern[patPos + 1] == PERCENT)
            return findSubLenAtStrPosWithPercent(str, pattern, strPos, patPos + 1);

        // determine whether percent is zero or more character wildcard   
        // offset is number of chars in between      
        int offset = getOffsetWildCard(str, pattern, strPos, patPos);

        if(offset == NOT_FOUND)
            return NOT_FOUND;

        // offset == 0
        if(!offset){ 
            cout << "zero char" << endl;
            return findSubLenAtStrPosWithPercent(str, pattern, strPos, patPos + 1);
        }

        // cout << "offset: " << offset << endl;
        int result = findSubLenAtStrPosWithPercent(str, pattern, strPos + offset, patPos + 1);
        if(result != NOT_FOUND)
            return result + offset;
    }

    // cout << "NOt Found !" << endl;
    return NOT_FOUND;
}

int matchSubWithPercent(const char str[], const char pattern[], int& length, int start = 0){
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    int testLength = findSubLenAtStrPosWithPercent(str, pattern, start);
    if (testLength != NOT_FOUND) {
        cout << "Found!" << endl;
        length = testLength;
        return start;
    }
    return matchSubWithPercent(str, pattern, length, start + 1);
}

int main(){
    int index;
    int length;

    // length = findSubLenAtStrPosWithPercent("cpoerjj", "c%%%r%%");

    // length = findSubLenAtStrPosWithPercent("beyond", "%rbe%z");

    // index = matchSubWithPercent("idk", "%", length); // 0 and 3
    // index = matchSubWithPercent("ikidk", "i%k", length); // 0 and 5
    // index = matchSubWithPercent("lolidk", "dk%", length); // 4 and 2
    // index = matchSubWithPercent("ilolol", "%ol", length); // 0 and 6
    // index = matchSubWithPercent("ilolol", "lo%", length); // 1 and 5
    // index = matchSubWithPercent("lol", "w%w", length); // NOT_FOUND and 0
    // index = matchSubWithPercent("something", "%%%s%%t%h", length); // 0 and 6


    cout << "Index: " << index << endl;
    cout << "Length: " << length << endl;
    return 0;
}