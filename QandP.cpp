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

int findSubLenAtStrPosWithPercentHelper(const char str[], const char pattern[], int strPos, int patPos, bool toggle);

int getRightDots(const char pattern[], int patPos){
    // cout << "current: " << pattern[patPos] << endl;

    if(pattern[patPos] == NULL_CHAR){
        return 0;
    }

    if(pattern[patPos] != QMARK && pattern[patPos] != PERCENT && pattern[patPos] != DOT){
        return 0;
    }

    if(pattern[patPos] == DOT){
        return getRightDots(pattern, patPos + 1) + 1;
    }
    return getRightDots(pattern, patPos + 1);
}

bool checkQuestionMarkHelper(const char pattern[], int patPos = 0){
    if(pattern[patPos] == NULL_CHAR)
        return true;
    if(pattern[patPos] != QMARK && pattern[patPos] != PERCENT)
        return false;
    return checkQuestionMarkHelper(pattern, patPos + 1);
}

bool checkPercentMarkHelper(const char pattern[], int patPos = 0){
    // cout << "in checkPercentMarkHelper: " << pattern[patPos] << endl;
    if(pattern[patPos] == NULL_CHAR){
        return true;
    }
    if(pattern[patPos] != PERCENT && pattern[patPos] != QMARK && pattern[patPos] != DOT){
        return false;
    }
    return checkPercentMarkHelper(pattern, patPos + 1);
}

bool containPercent(const char pattern[], int patPos){
    if(pattern[patPos] == NULL_CHAR){
        return false;
    }
    if(pattern[patPos] == PERCENT){
        return true;
    }
    return containPercent(pattern, patPos + 1);
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



bool checkOneCharWildcard(const char str[], const char pattern[], int strPos, int patPos, int dotOffset){
    if(str[strPos + dotOffset] == NULL_CHAR)
        return false;
    
    if(pattern[patPos] == QMARK)
        return checkOneCharWildcard(str, pattern, strPos + 1, patPos + 1, dotOffset);
    else if(pattern[patPos] == DOT)
        return checkOneCharWildcard(str, pattern, strPos, patPos + 1, dotOffset);
    if(pattern[patPos] == str[strPos + dotOffset])
        return true;
    return false;
}

int findSubLenAtStrPosWithQmarkHelper(const char str[], const char pattern[], int strPos = 0, int patPos = 0, bool toggleDot = false)
{
    // cout << "Qstr: " << str[strPos] << ", Qpat: " << pattern[patPos] << endl;
    if(pattern[patPos] == NULL_CHAR)
        return 0;

    if(str[strPos] == NULL_CHAR){
        if(pattern[patPos] != NULL_CHAR && !checkQuestionMarkHelper(pattern, patPos))
            return NOT_FOUND;
        return 0;
    }

    if (pattern[patPos] == str[strPos])
    {
        if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched
            return 1;
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPosWithQmarkHelper(str, pattern, strPos + 1, patPos + 1, false); // check if the remaining part of the pattern 
                                                                                      // matches with that of the substring
        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
            return 1 + result;
    }
    else if(pattern[patPos] == QMARK){
        //determine whether ? is zero-character or 1 character wildcarc
        
        // check if remaining pattern is all questionamarks
        
        if(checkQuestionMarkHelper(pattern, patPos)){ 
            if(containPercent(pattern, patPos)){
                int result = findSubLenAtStrPosWithPercentHelper(str, pattern, strPos, patPos, false);
                if(result != NOT_FOUND)
                    return result;
            }
            return minString(str, pattern, strPos, patPos);
        }

        int prelimResult = findSubLenAtStrPosWithQmarkHelper(str, pattern, strPos , patPos + 1, false );
        if(prelimResult == NOT_FOUND){
            int result = findSubLenAtStrPosWithQmarkHelper(str, pattern, strPos + 1, patPos + 1, false);
            if(result != NOT_FOUND){
                // cout<< "pat Pos: " << patPos << ", one Char" << ", dots: " << dots << endl;
                return result + 1;
            }
        }
        else
        {
            // cout<< "pat Pos: " << patPos << ", zerochar" << endl;
            return prelimResult;
        }

    }
    else if(pattern[patPos] == PERCENT){
        int result = findSubLenAtStrPosWithPercentHelper(str, pattern, strPos, patPos, false);
        return result;
    }
    else if(pattern[patPos] == DOT){
        int result = findSubLenAtStrPosWithQmarkHelper(str, pattern, strPos + 1, patPos + 1);
        if(result != NOT_FOUND)
            return result + 1;
    }
    else if(pattern[patPos] == CARET){
        return findSubLenAtStrPosWithQmarkHelper(str, pattern, strPos, patPos + 1);
    }

    // cout  << "NOt Found !" << endl;
    return NOT_FOUND;
}

int matchSubWithQmark(const char str[], const char pattern[], int &length, int start = 0)
{
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    // cout << "HI!!" << endl;
    int testLength = findSubLenAtStrPosWithQmarkHelper(str, pattern, start);
    if (testLength != NOT_FOUND) {
        // cout << "Found!" << endl;
        length = testLength;
        return start;
    }
    return matchSubWithQmark(str, pattern, length, start + 1);
}

int getOffsetWildCardHelper(const char str[], const char pattern[], int strPos, int patPos, int dotOffset){
    // cout << "Nstr: " << str[strPos] << endl;
    if(str[strPos + dotOffset] == NULL_CHAR)
        return NOT_FOUND;
    
    if(str[strPos + dotOffset] == pattern[patPos + 1 + dotOffset]){
        // cout << "strPos: " << strPos << endl;
        int testOffset = getOffsetWildCardHelper(str, pattern, strPos + 1, patPos, dotOffset);
        if(testOffset != NOT_FOUND){
            return testOffset + 1;
        }
            
        return 0;
    }
    int result = getOffsetWildCardHelper(str, pattern, strPos + 1, patPos, dotOffset);
    if(result != NOT_FOUND)
        return result + 1;
    return result;
}

int findSubLenAtStrPosWithPercentHelper(const char str[], const char pattern[], int strPos = 0, int patPos = 0, bool toggle = false)
{
    // cout << "Pstr: " << str[strPos] << ", Ppat: " << pattern[patPos] << endl;
    if(pattern[patPos] == NULL_CHAR)
        return 0;

    if(str[strPos] == NULL_CHAR){
        if(pattern[patPos] != NULL_CHAR && !checkPercentMarkHelper(pattern, patPos))
            return NOT_FOUND;
        return 0;
    }

    if (pattern[patPos] == str[strPos])
    {
        if (pattern[patPos + 1] == NULL_CHAR) // the entire pattern is matched
            return 1;
        // otherwise, the match is only part way through
        int result = findSubLenAtStrPosWithPercentHelper(str, pattern, strPos + 1, patPos + 1, true); // check if the remaining part of the pattern 
                                                                                      // matches with that of the substring
        if (result != NOT_FOUND) // only return a match when the entire pattern is matched
            return 1 + result;
    }
    else if(pattern[patPos] == PERCENT || (pattern[patPos] == QMARK && !toggle)){
        // case where end of pattern consists of percents

        int dots = getRightDots(pattern, patPos);
        if(checkPercentMarkHelper(pattern, patPos)){
            int result = minStringPercent(str, strPos);
            if(result < dots)
                return NOT_FOUND;
            return result;
        }

        if(pattern[patPos + 1] == PERCENT || pattern[patPos + 1] == QMARK)
            return findSubLenAtStrPosWithPercentHelper(str, pattern, strPos, patPos + 1);

        // determine whether percent is zero or more character wildcard        
        int offset = getOffsetWildCardHelper(str, pattern, strPos, patPos, dots);

        if(offset == NOT_FOUND)
            return NOT_FOUND;

        if(!offset){
            cout << "zero char" << endl;
            return findSubLenAtStrPosWithPercentHelper(str, pattern, strPos, patPos + 1);
        }
        
        cout << "offset: " << offset << endl;
        int result = findSubLenAtStrPosWithPercentHelper(str, pattern, strPos + offset + dots, patPos + 1 + dots);
        if(result != NOT_FOUND)
            return result + offset + dots;
        return NOT_FOUND;
        
    }
    else if(pattern[patPos] == QMARK && toggle)
        return findSubLenAtStrPosWithQmarkHelper(str, pattern, strPos, patPos);
    else if(pattern[patPos] == DOT){
        int result = findSubLenAtStrPosWithPercentHelper(str, pattern, strPos + 1, patPos + 1);
        if(result != NOT_FOUND)
            return result + 1;
    }

    // cout << "NOt Found !" << endl;
    return NOT_FOUND;
}

int matchSubWithPercent(const char str[], const char pattern[], int& length, int start = 0){
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    int testLength = findSubLenAtStrPosWithPercentHelper(str, pattern, start);
    if (testLength != NOT_FOUND) {
        // cout << "Found!" << endl;
        length = testLength;
        return start;
    }
    return matchSubWithPercent(str, pattern, length, start + 1);
}

int matchSub(const char str[], const char pattern[], int &length, int start = 0){
    length = 0;
    if (str[start] == NULL_CHAR)
        return NOT_FOUND;
    if(pattern[0] == CARET){
        // cout << "hello" << endl;
        if(pattern[1] != PERCENT && pattern[1] != QMARK && pattern[1] != DOT){
            // cout << "helo" << endl;
            if(str[start] != pattern[1])
                return NOT_FOUND;
        }
    }
    // cout << "HI!!" << endl;
    int testLength = findSubLenAtStrPosWithQmarkHelper(str, pattern, start);
    if (testLength != NOT_FOUND) {
        // cout << "Found!" << endl;
        length = testLength;
        return start;
    }
    return matchSub(str, pattern, length, start + 1);
}

int main(){
    int length;
    int index;
    
    // length = findSubLenAtStrPosWithQmarkHelper("lllllll", "?%?");
    // length = findSubLenAtStrPosWithQmarkHelper("idkk", "..?k.???");
    // length = findSubLenAtStrPosWithQmarkHelper("idkk", "%.dk?");
    // length = findSubLenAtStrPosWithQmarkHelper("idkwhatsgoingon", ".kw%g", 1);
    // length = findSubLenAtStrPosWithQmarkHelper("comp2011", "c??.%m");
    // length = findSubLenAtStrPosWithQmarkHelper("comp2011", "c?????.2");

    // index = matchSub("idk", "dk", length); // 1 and 2
    // index = matchSub("idk", "^i", length); // 0 and 1
    // index = matchSub("idk", "^?i", length); // 0 and 1
    // index = matchSub("dkidk", "^id", length); // NOT_FOUND and 0
    // index = matchSub("idkwhatsgoingon", ".kw%g", length); // 1 and 12
    // index = matchSub("ithinkithinktoomuch", "^ith%ink.???o", length); // 0 and 15
    // index = matchSub("BeyondCalm", "%?%??%%eyondCalm", length); // 0 and 10
    // index = matchSub("BeyondCalm", "%?%??%%.BeyondCalm", length); // NOT_FOUND and 0
    // index = matchSub("IAmBeyondCalmIamZen", "Zen?%?%%??", length); // 16 and 3
    // index = matchSub("IAmBeyondCalmIamZen", "?.?Ze?%.?%%??", length); // 13 and 6
    
    cout << "Index: " << index << endl;
    cout << "Length: " << length << endl;
    return 0;
}