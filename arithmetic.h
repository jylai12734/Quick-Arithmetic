#ifndef ARITHMETIC
#define ARITHMETIC

#include "utils.h"

struct Box {
    int first, second, answer, attempt = 1000000000;
    vs display;
    bool correct = false;
};

pair<string, int> answer(int& f, int s, int r);

int fill(Box test[4][6], int d);

void show(Box test[4][6]);

void timer(bool& timesUp, bool& end);

void next(int& r1, int& c1, int& r2, int& c2);

void de_select(Box& n, bool x);

void submit(Box test[4][6], int d, int right, string s, aRecord& aData, pair<string, aRecord>& aTop);

void arithmetic(int d, map<string, aRecord>& aData, pair<string, aRecord>& aTop);

#endif // ARITHMETIC