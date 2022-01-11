#include "arithmetic.h"
#include "fluency.h"
#include "utils.h"

void show(vector<vs>& problems) {   // display the row of problems 
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) cout << problems[j][i];
        cout << endl;
    }
}

void fluencydrill(int& end, int& correct) { // helper function to fluency

    // declare variables
    srand(time(NULL));
    Box test[100];
    int ans = -1;
    int current = 0;
    istringstream i;
    size_t asize;
    string align;
    string s;
    vector<vs> problems;
    vs spaces;
    for (int i = 0; i < 3; i++) spaces.push_back(string(6, ' '));   // end declare variables

    // create test
    for (int i = 0; i < 100; i++) {
        Box& b = test[i];
        int r = rand() % 4;
        b.first = rand() % 13;
        do b.second = rand() % 13;
        while ((r == 3 && b.second == 0) || (r == 1 && b.second > b.first));
        pair<string, int> p = answer(b.first, b.second, r);
        b.answer = p.second;

        b.display.push_back(" " + string(3 - to_string(b.first).size(), ' ') + to_string(b.first) + "  ");
        b.display.push_back(p.first + string(2 - to_string(b.second).size(), ' ') + to_string(b.second) + "  ");
        b.display.push_back("----  ");
    }   // end create test

    // introduction
    cout << string(90, '*') << endl;
    cout << "Welcome to Fluency Drill." << endl;
    cout << "Complete the following 100 problems as fast as you can." << endl;
    cout << "Enter '-' or 'b' to go back." << endl;
    cout << "Enter 'e' to return to the menu." << endl;
    cout << "Press enter to start." << endl;
    cout << string(90, '*') << endl;
    getline(cin, s);    // end introduction

    // game loop
    while (true) {

        // create spacing
        asize = to_string(test[current].answer).size();
        switch (current) {
            case 0: // if the user is on the first problem
                problems.push_back(spaces); problems.push_back(spaces); problems.push_back(test[current].display); problems.push_back(test[current + 1].display); problems.push_back(test[current + 2].display);
                align = string(16 - asize, ' ');
                break;
            case 1: // if the user is on the second problem
                problems.push_back(spaces); problems.push_back(test[current - 1].display); problems.push_back(test[current].display); problems.push_back(test[current + 1].display); problems.push_back(test[current + 2].display);
                align = string(10 - to_string(test[current - 1].attempt).size(), ' ') + to_string(test[current - 1].attempt) + string(6 - asize, ' ');
                break;
            case 98: // if the user is on the penultimate problem
                problems.push_back(test[current - 2].display); problems.push_back(test[current - 1].display); problems.push_back(test[current].display); problems.push_back(test[current + 1].display); problems.push_back(spaces);
                align = string(4 - to_string(test[current - 2].attempt).size(), ' ') + to_string(test[current - 2].attempt) + string(6 - to_string(test[current - 1].attempt).size(), ' ') + to_string(test[current - 1].attempt) + string(6 - asize, ' ');
                break;
            case 99: // if the user is on the last problem
                problems.push_back(test[current - 2].display); problems.push_back(test[current - 1].display); problems.push_back(test[current].display); problems.push_back(spaces); problems.push_back(spaces);
                align = string(4 - to_string(test[current - 2].attempt).size(), ' ') + to_string(test[current - 2].attempt) + string(6 - to_string(test[current - 1].attempt).size(), ' ') + to_string(test[current - 1].attempt) + string(6 - asize, ' ');
                break;
            default: // if the user is on any other problem
                problems.push_back(test[current - 2].display); problems.push_back(test[current - 1].display); problems.push_back(test[current].display); problems.push_back(test[current + 1].display); problems.push_back(test[current + 2].display);
                align = string(4 - to_string(test[current - 2].attempt).size(), ' ') + to_string(test[current - 2].attempt) + string(6 - to_string(test[current - 1].attempt).size(), ' ') + to_string(test[current - 1].attempt) + string(6 - asize, ' ');
                break;
        }   // end create spacing

        // show problem and get user input
        cout << string(90, '*') << endl;
        show(problems);
        cout << align;
        getline(cin, s);
        i.clear();
        i.str(s);   // end show problem and get user input

        // invalid inputs
        while (!((s == "-" || s == "b") && current != 0) && !(s == "e") && (!(i >> test[current].attempt) || test[current].attempt < 0 || test[current].attempt > 999)) {
            cout << "Invalid input. Try again." << endl;
            cout << string(90, '*') << endl;
            show(problems);
            cout << align;
            getline(cin, s);
            i.clear();
            i.str(s);
        }   // end invalid inputs

        // valid inputs
        if ((s == "-" || s == "b") && current != 0) {   // go back one problem
            if (test[current - 1].attempt == test[current - 1].answer) correct--;
            current--;
        }
        else if (s == "e") {    // exit out of the test
            end = 2;
            return;
        }
        else {  // go to the next problem
            if (test[current].attempt == test[current].answer) correct++;
            current++;
        }
        problems.clear();   // end valid inputs

        // prompt user to submit or go back
        if (current == 100) {
            cout << endl << "Press enter to submit or press '-' to go back" << endl;
            getline(cin, s);
            if (s == "-") { 
                if (test[99].attempt == test[99].answer) correct--;
                current = 99;
            }
            else {
                end = 1;
                return;
            }
        }   // end prompt user to submit or go back
    }
}   // end game loop

void fluency(map<string, int>& fData, pair<string, int>& fTop) {    // assess the user's speed and accuracy on completing 100 arithmetic problems
    
    // declare variables
    int end = 0, correct = 0, time = 0;
    thread t(fluencydrill, ref(end), ref(correct)); // this thread will run the test while the main thread runs the stopwatch
    
    // stopwatch
    while (end == 0) {
        sleep(1);
        time++;
    }   

    // if the user exits during the test
    if (end == 2) cout << endl << "Returning to menu..." << endl << endl;  

    // if the user got 100%
    else if (correct == 100) {
        string s;
        cout << "Your grade is " << correct << "%" << " in " << time << " seconds. Enter a name to record your result or enter nothing to discard it: ";
        getline(cin, s);
        if (s != "" && fData[s] == 0) fData[s] = time;
        else if (s != "" && fData[s] != 0) fData[s] = min(fData[s], time);
        if (s != "" && (fTop.first == "" || fData[s] < fTop.second)) {
            fTop.first = s;
            fTop.second = fData[s];
        }
        cout << "Returning to the menu..." << endl << endl;
    }

    // if the user did not get 100%
    else cout << endl << "Your grade is " << correct << "%" << " in " << time << " seconds." << endl << "Returning to the menu..." << endl << endl;
    
    t.join();
    sleep(3);
    return;
}