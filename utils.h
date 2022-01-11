#ifndef UTILS
#define UTILS

#include <ctime>        // defines time
#include <fstream>      // defines fstream
#include <iostream>     // defines cin and cout
#include <map>          // defines map
#include <sstream>      // defines istringstream
#include <stack>        // defines stack
#include <string>       // defines string
#include <thread>       // defines thread
#include <vector>       // defines vector
#include <windows.h>    // defines Sleep

#define sleep(x) Sleep(1000 * (x)) // redefine Sleep

using namespace std;

struct aRecord {
    int hard = 0;
    int medium = 0;
    int easy = 0;
};

typedef vector<string> vs;

bool find(string s, vs strings);

string check(string& s, istringstream& i, int& n, int l, int h, bool& timeUp, vs strings = {});

pair<string, aRecord> aCreate(string& s, istringstream& i);

pair<string, int> fCreate(string& s, istringstream& i);

#endif // UTILS