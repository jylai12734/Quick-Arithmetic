#include "utils.h"

bool find(string s, vs strings) {
    for (size_t i = 0; i != strings.size(); i++) if (s == strings[i]) return true;
    return false;
}

string check(string& s, istringstream& i, int& n, int l, int h, bool& timesUp, vs strings) {
    i.str(s);
    while (!timesUp && !find(s, strings) && (s.find(' ') != s.npos || !(i >> n) || n < l || n > h)) {
        cout << "Invalid input. Try again: ";
        getline(cin, s);
        i.clear();
        i.str(s);
    }
    i.clear();
    return s;
}

pair<string, aRecord> aCreate(string& s, istringstream& i) {
    aRecord aRec;
    int n = 0, count = 0;
    while (s[count] != ':') count++;
    string name = s.substr(n, count);
    n = count + 2;
    while (s[count] != 'H') count++;
    i.str(s.substr(n, count));
    i >> aRec.hard;
    i.clear();
    n = count + 3;
    while (s[count] != 'M') count++;
    i.str(s.substr(n, count));
    i >> aRec.medium;
    i.clear();
    n = count + 3;
    while (s[count] != 'E') count++;
    i.str(s.substr(n, count));
    i >> aRec.easy;
    i.clear();
    return {name, aRec};
}

pair<string, int> fCreate(string& s, istringstream& i) {
    int n = 0, count = 0;
    while (s[count] != ':') count++;
    string name = s.substr(n, count);
    n = count + 2;
    count += 2;
    while (s[count] != ' ') count++;
    i.str(s.substr(n, count));
    i >> n;
    i.clear();
    return {name, n};
}