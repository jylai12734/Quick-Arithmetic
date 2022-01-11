#include "arithmetic.h"
#include "fluency.h"
#include "utils.h"

// g++ menu.cpp utils.cpp arithmetic.cpp fluency.cpp -o QuickArithmetic

int main() {

    // declare variables
    aRecord a;
    bool timesUp = false;
    int count, n;
    istringstream i;
    map<string, aRecord> aData;
    map<string, int> fData;
    pair<string, aRecord> aTop = {"", a};
    pair<string, int> fTop = {"", 0};
    fstream file;
    size_t t;
    string s;   // end declare variables

    // read record.txt
    file.open("record.txt", ios::in); 
    if (file.is_open()) {
        while (getline(file, s) && s != "") aData.insert(aCreate(s, i));
        if (getline(file, s) && s != "") aTop = aCreate(s, i);
        while (getline(file, s) && s != "") fData.insert(fCreate(s, i));
        if (getline(file, s) && s != "") fTop = fCreate(s, i);
        file.close();
    }   // end read record.txt

    // introduction
    cout << string(90, '*') << endl;
    cout << "Welcome to Quick Arithmetic!" << endl;
    cout << "Type the number that corresponds with your desired choice." << endl;
    cout << "Type 4 to exit." << endl;
    cout << string(90, '*') << endl << endl; // end introduction

    // main game loop
    while (n != 4) {
        
        // display menu
        cout << string(90, '*') << endl;
        cout << "Menu" << endl;
        cout << "1: Arithmetic Exercise" << endl;
        cout << "2: Fluency Drill" << endl;
        cout << "3: Player Records" << endl;
        cout << "4: Exit" << endl;
        cout << string(90, '*') << endl << endl; // end display menu

        // user input
        cout << "Enter number: ";
        getline(cin, s);
        check(s, i, n, 1, 4, timesUp); // end user input

        switch (n) {

            case 1: // Arithmetic Exercise
                
                // display difficulty levels
                cout << endl << "Choose a difficulty level or enter '4' to go back." << endl << endl;
                cout << string(90, '*') << endl;
                cout << "Levels" << endl;
                cout << "1: Easy" << endl; 
                cout << "2: Medium" << endl;
                cout << "3: Hard" << endl;
                cout << string(90, '*') << endl << endl; // end display difficulty levels

                // user difficulty
                cout << "Enter number: ";
                getline(cin, s);
                check(s, i, n, 1, 4, timesUp);
                cout << endl; // end user difficulty

                if (n != 4) arithmetic(n, aData, aTop); 
                break;  // end Arithmetic Exercise

            case 2: // Fluency Drill
                cout << endl;
                fluency(fData, fTop);
                break;  // end Fluency Drill

            case 3: // Player Records

                do {

                // display actions
                cout << endl << "Choose an action." << endl << endl;
                cout << string(90, '*') << endl;
                cout << "Actions" << endl;
                cout << "1: Show top player(s)" << endl;
                cout << "2: Retrieve player stats" << endl;
                cout << "3: Delete player" << endl;
                cout << "4: Show all record(s)" << endl;
                cout << "5: Return to menu" << endl;
                cout << string(90, '*') << endl << endl; // end display actions

                // user action
                cout << "Enter number: ";
                getline(cin, s);
                check(s, i, n, 1, 5, timesUp);
                cout << endl;   // end user action

                switch (n) {

                    case 1: // Show top player(s)
                        cout << "Top Player for Arithmetic Exercise: ";
                        if (aTop.first != "") cout << aTop.first << endl << "Stats: " << aTop.second.hard << "H, " << aTop.second.medium << "M, " << aTop.second.easy << "E" << endl;
                        else cout << "None" << endl;
                        cout << "Top Player for Fluency Drill: ";
                        if (fTop.first != "") cout << fTop.first << endl << "Stats: " << fTop.second << " seconds" << endl;
                        else cout << "None" << endl;
                        break; // end Show top player(s)

                    case 2: // Retrieve player stats
                        cout << "Enter name or enter nothing to go back: ";
                        getline(cin, s);
                        if (s == "") break;
                        t = aData.size();
                        aData[s];
                        cout << "Arithmetic Exercise: ";
                        if (aData.size() == t) cout << aData[s].hard << "H, " << aData[s].medium << "M, " << aData[s].easy << "E" << endl;
                        else {
                            cout << "no information" << endl;
                            aData.erase(s);
                        }
                        cout << "Fluency Drill: ";
                        if (fData[s]) cout << fData[s] << " seconds" << endl;
                        else {
                            cout << "no information" << endl;
                            fData.erase(s);
                        }
                        break;  // end Retrieve player stats

                    case 3: // Delete player
                        cout << "Enter name or enter nothing to go back: ";
                        getline(cin, s);
                        while (!aData.erase(s) && !fData.erase(s) && s != "") {
                            cout << s << " does not have a record. Enter name or enter nothing to go back: ";
                            getline(cin, s);
                        }
                        break; // end Delete player

                    case 4: // Show all record(s)
                        cout << "Arithmetic Exercise records" << endl;
                        for (map<string, aRecord>::iterator it = aData.begin(); it != aData.end(); it++) cout << it->first << ": " << it->second.hard << "H, " << it->second.medium << "M, " << it->second.easy << "E" << endl;
                        cout << endl << "Fluency Drill records" << endl;
                        for (map<string, int>::iterator it = fData.begin(); it != fData.end(); it++) cout << it->first << ": " << it->second << " seconds" << endl;
                        break;  // end Show all record(s)
                    }

                } while (n != 5);

                break; // end Player Records
        }
    } // end main game loop

    // write record.txt
    file.open("record.txt", ios::out);
    if (file.is_open()) {
        for (map<string, aRecord>::iterator it = aData.begin(); it != aData.end(); it++) file << it->first << ": " << it->second.hard << "H, " << it->second.medium << "M, " << it->second.easy << "E\n";
        file << "\n";
        if (aTop.first != "") file << aTop.first << ": " << aTop.second.hard << "H, " << aTop.second.medium << "M, " << aTop.second.easy << "E\n";
        else file << "\n";
        for (map<string, int>::iterator it = fData.begin(); it != fData.end(); it++) file << it->first << ": " << it->second << " seconds\n";
        file << "\n";
        if (fTop.first != "") file << fTop.first << ": " << fTop.second << " seconds\n";
        else file << "\n";
        file.close();
    }   // end write record.txt

    cout << "Bye!" << endl;
    sleep(1);
    return 0;
}
