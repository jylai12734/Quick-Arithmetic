#include "arithmetic.h"
#include "utils.h"

pair<string, int> answer(int& f, int s, int r) { // return the operation and the answer of an arithmetic question
    switch (r) {
        case 0: return {"+ ", f + s};
        case 1: return {"- ", f - s};
        case 2: return {"* ", f * s};
        default:
            f *= s;
            return {"/ ", f / s};
    }
}

int fill(Box test[4][6], int d) { // fill the 4 by 6 array with arithmetic questions
    int random, low, right;
    switch (d) {    // select range depending on the difficulty
        case 1:
            random = 10;
            low = 0;
            right = 6;
            break;
        case 2:
            random = 100;
            low = 0;
            right = 8;
            break;
        default:
            random = 1999;
            low = -999;
            right = 10;
            break;
    }

    // iterate through the 4 by 6 array and create each arithmetic problem
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 6; c++) {
            Box& b = test[r][c];
            b.first = rand() % random + low;
            do b.second = rand() % random + low;
            while (b.second == 0 && r == 3);
            pair<string, int> p = answer(b.first, b.second, r);
            b.answer = p.second;

            // create the visual display of each box
            b.display.push_back("-------------");
            b.display.push_back("|" + string(right - to_string(b.first).size(), ' ') + to_string(b.first) + string(13 - right - 2, ' ') + "|");
            b.display.push_back("| " + p.first + string(right - 3 - to_string(b.second).size(), ' ') + to_string(b.second) + string(13 - right - 2, ' ') + "|");
            b.display.push_back("| --------- |");
            b.display.push_back("|           |");
            b.display.push_back("|           |");
            b.display.push_back("-------------");
        }
    }
    return right;
}

void show(Box test[4][6]) { // display the 4 by 6 array
    for (int i = 0; i < 4; i++) 
        for (int j = 0; j < 7; j++) {
            for (int k = 0; k < 6; k++) cout << test[i][k].display[j];
            cout << endl;
        }
}

void timer(bool& timesUp, bool& submitted) {    // a timer that terminates the test after ten minutes
    for (int i = 600; i != 0; i--) {
        sleep(1);
        if (submitted) return;
    }
    cout << endl << "Times up! Press enter to submit." << endl;
    timesUp = true;
}

void next(int& r1, int& c1, int& r2, int& c2) { // autoselect the box to the right 
    c2++;
    if (c2 == 7) {
        c2 = 1;
        r2++;
    }
    if (r2 == 5) r2 = 1;
    r1 = r2; c1 = c2;
}

void de_select(Box& b, bool x) {    // visually change the border of the selected box and change back the border of the deselected box 
    char c = x ? 'x' : '|';
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < 13; j++)
            if (i == 0 || i == 6 || j == 0 || j == 12) {
                if (!x && (i == 0 || i == 6)) b.display[i][j] = '-';
                else b.display[i][j] = c;
            }
}

void submit(Box test[4][6], int d, int right, string s, map<string, aRecord>& aData, pair<string, aRecord>& aTop) { // submit the test
    int numerator = 0;
    int grade;
    vector<Box> wrong;  // a vector that keeps track of all the wrong problems

    // determine the number of correct solutions and update wrong
    for (int r = 0; r < 4; r++)
        for (int c = 0; c < 6; c++) {
            if (test[r][c].correct) numerator++;
            else wrong.push_back(test[r][c]);
        }

    // display grade
    grade = 100 * numerator / 24;
    cout << "Here is your grade: " + to_string(grade) + "%" << endl;

    // if the user got a 100%
    if (wrong.empty()) {
        string s;
        cout << "Enter a name to record your result or enter nothing to discard it: ";
        getline(cin, s);
        if (s != "" && d == 1) aData[s].easy++;
        else if (s != "" && d == 2) aData[s].medium++;
        else if (s != "" && d == 3) aData[s].hard++;
        if (s != "" && (aTop.first == "" || 10 * aTop.second.hard + 5 * aTop.second.medium + aTop.second.easy < 10 * aData[s].hard + 5 * aData[s].medium + aData[s].easy)) {
            aRecord aRec;
            aRec.hard = aData[s].hard;
            aRec.medium = aData[s].medium;
            aRec.easy = aData[s].easy;
            aTop = {s, aRec};
        } 
        cout << "Returning to the menu..." << endl << endl;
        sleep(1);

    // if the user did not get a 100%
    } else {
        cout << "These are the problem(s) you got wrong. On the left is your answer. On the right is the correct answer." << endl;
        sleep(3);
        for (size_t i = 0; i != wrong.size(); i++) {
            Box& b = wrong[i];
            for (int j = 0; j < 7; j++) {
                if (j == 4) {
                    if (b.attempt == 1000000000) cout << "|           |";
                    else cout << "|" + string(right - to_string(b.attempt).size(), ' ') + to_string(b.attempt) + string(13 - right - 2, ' ') + "|";
                    cout << "|" + string(right - to_string(b.answer).size(), ' ') + to_string(b.answer) + string(13 - right - 2, ' ') + "|" << endl;
                }
                else cout << b.display[j] << b.display[j] << endl;
            }
        }
        cout << "Press enter to return to the menu." << endl;
        getline(cin, s);
        cout << "Returning to the menu..." << endl << endl;
        sleep(1);
    }
}

void arithmetic(int d, map<string, aRecord>& aData, pair<string, aRecord>& aTop) {  // asses the user's ability to complete 24 arithmetic questions under 10 minutes

    // declare variables
    srand(time(NULL));
    Box test[4][6];
    bool timesUp = false, end = false;
    int ans, r1, c1 = -1, r2 = 1, c2 = 0;
    int right = fill(test, d);
    istringstream i;
    pair<int, int> p = {-1, -1};
    stack<pair<int, int> > history;
    string s; // end declare variables

    // introduction
    cout << string(90, '*') << endl;
    cout << "Welcome to Arithmetic Exercise (";
    if (d == 1) cout << "easy)." << endl;
    else if (d == 2) cout << "medium)." << endl;
    else cout << "hard)." << endl;
    cout << "Complete the following problems in under 10 minutes." << endl;
    cout << "Press the spacebar to autoselect forward." << endl;
    cout << "Enter 'b' to go back." << endl;
    cout << "Enter a row number between [1, 4] and a column number between [1, 6] to manually select." << endl;
    cout << "Enter 'e' to return to the menu." << endl;
    cout << "Enter 's' to submit." << endl;
    cout << "Press enter to start." << endl;
    cout << string(90, '*') << endl;
    getline(cin, s);
    show(test);
    thread t(timer, ref(timesUp), ref(end)); // end introduction

    // game loop
    while (true) {

        // get user row input
        cout << "Enter a row number: ";
        getline(cin, s);
        if (history.empty()) check(s, i, r1, 1, 4, timesUp, {" ", "e", "s"});
        else check(s, i, r1, 1, 4, timesUp, {" ", "b", "e", "s"}); // end get user row input

        // get user column input
        if (!find(s, {" ", "b", "e", "s"})) {
            cout << "Enter a column number: ";
            getline(cin, s);
            if (history.empty()) check(s, i, c1, 1, 6, timesUp, {" ", "e", "s"});
            else check(s, i, c1, 1, 4, timesUp, {" ", "b", "e", "s"});  
        } // end get user column input

        // update variable and select or special cases
        if (timesUp || s == "e" || s == "s") break;
        else if (s == " ") {
            next(r1, c1, r2, c2);
            de_select(test[r1 - 1][c1 - 1], true);
            show(test); 
        }
        else if (s != "b") {
            de_select(test[r1 - 1][c1 - 1], true);
            show(test); 
        }
        while (s == "b") {
            p = history.top();
            history.pop();
            r1 = p.first;
            c1 = p.second;
            de_select(test[r1 - 1][c1 - 1], true);
            show(test);
            if (!history.empty()) {
                cout << "Type enter to select this box or type 'b' to go back more." << endl;
                getline(cin, s);
                if (s == "b") de_select(test[r1 - 1][c1 - 1], false);
            }
            else {
                cout << "Type enter to select this box." << endl;
                getline(cin, s);
                break;
            }
        } 
        r2 = r1;
        c2 = c1; // end update variable and select or special cases

        // get user solution
        cout << "Enter your solution: ";
        getline(cin, s);
        switch (d) {
            case 1:
                check(s, i, ans, -9999, 99999, timesUp, {"e", "s"});
                break;
            case 2:
                check(s, i, ans, -999999, 9999999, timesUp, {"e", "s"});
                break;
            default:
                check(s, i, ans, -99999999, 999999999, timesUp, {"e", "s"});
                break;
        } if (timesUp || s == "e" || s == "s") break; // end get user solution

        // check user solution and deselect
        if (ans == test[r1 - 1][c1 - 1].answer) test[r1 - 1][c1 - 1].correct = true;
        test[r1 - 1][c1 - 1].attempt = ans;
        test[r1 - 1][c1 - 1].display[4] = "x" + string(right - to_string(ans).size(), ' ') + to_string(ans) + string(13 - right - 2, ' ') + "x";
        show(test);
        de_select(test[r1 - 1][c1 - 1], false); // end check user solution and deselect

        history.push({r1, c1});       
        
    } // end game loop
    
    // submit or exit
    if (c1 != -1) de_select(test[r1 - 1][c1 - 1], false);
    if (timesUp) {
        t.join();
        submit(test, d, right, s, aData, aTop);
        return;
    }
    else if (s == "s") submit(test, d, right, s, aData, aTop);
    else cout << "Returning to the menu..." << endl << endl;
    end = true;
    t.join();
    sleep(1); // end submit or exit
}