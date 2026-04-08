#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <algorithm> // vector sort :)
#include <iomanip>
using namespace std;
using namespace std::chrono;

// scalable
void printLine(string operation, long long vectorVal, long long listVal, long long setVal);

const int RUNS = 15; // how many runs
const int setWidth = 15; // width of print

const int VLS = 3; // operations done in program

int main() {

    // accumulator containers
    long long Read[RUNS][VLS] = {0}; 
    long long Sort[RUNS][VLS] = {0}; 
    long long Insert[RUNS][VLS] = {0}; 
    long long Delete[RUNS][VLS] = {0}; 

    // accumulators for totals
    long long readTotal[VLS] = {0};
    long long sortTotal[VLS] = {0};
    long long insertTotal[VLS] = {0};
    long long deleteTotal[VLS] = {0};

    string op;
    string codeToInsert;
    vector<string> data;
    vector<string> codeVector;
    list<string> codeList;
    set<string> codeSet;

    ifstream fin("codes.txt");
    while (fin >> codeToInsert) {
        data.push_back(codeToInsert);
    }

    for (int i = 0; i < RUNS; ++i) { // run loop
        
        // vector reading time
        auto start = high_resolution_clock::now();
        for (const auto &x : data) codeVector.push_back(x);
        auto end = high_resolution_clock::now();
        auto vectorSpeed = duration_cast<nanoseconds>(end - start);

        // list reading time
        start = high_resolution_clock::now();
        for (const auto &x : data) codeList.push_back(x);
        end = high_resolution_clock::now();
        auto listSpeed = duration_cast<nanoseconds>(end - start);

        // set reading time
        start = high_resolution_clock::now();
        for (const auto &x : data) codeSet.insert(x);
        end = high_resolution_clock::now();
        auto setSpeed = duration_cast<nanoseconds>(end - start);

        // add results to 2D array
        Read[i][0] = vectorSpeed.count();
        Read[i][1] = listSpeed.count();
        Read[i][2] = setSpeed.count();

        // add results to 3D array total
        readTotal[0] += Read[i][0];
        readTotal[1] += Read[i][1];
        readTotal[2] += Read[i][2];

        // vector sorting time
        start = high_resolution_clock::now();
        sort(codeVector.begin(), codeVector.end());
        end = high_resolution_clock::now();
        vectorSpeed = duration_cast<nanoseconds>(end - start);

        // list sorting time
        start = high_resolution_clock::now();
        codeList.sort();
        end = high_resolution_clock::now();
        listSpeed = duration_cast<nanoseconds>(end - start);

        Sort[i][0] = vectorSpeed.count();
        Sort[i][1] = listSpeed.count();
        Sort[i][2] = -1;

        sortTotal[0] += Sort[i][0];
        sortTotal[1] += Sort[i][1];
        sortTotal[2] += Sort[i][2];

        codeToInsert = "TESTCODE";

        // vector inserting time
        start = high_resolution_clock::now();
        codeVector.insert(codeVector.begin() + data.size() / 2, codeToInsert);
        end = high_resolution_clock::now();
        vectorSpeed = duration_cast<nanoseconds>(end - start);

        // list inserting time
        start = high_resolution_clock::now();
        auto it = codeList.begin();
        advance(it, codeList.size() / 2);
        codeList.insert(it, codeToInsert);
        end = high_resolution_clock::now();
        listSpeed = duration_cast<nanoseconds>(end - start);

        // set inserting time
        start = high_resolution_clock::now();
        codeSet.insert(codeToInsert);
        end = high_resolution_clock::now();
        setSpeed = duration_cast<nanoseconds>(end - start);

        Insert[i][0] = vectorSpeed.count();
        Insert[i][1] = listSpeed.count();
        Insert[i][2] = setSpeed.count();

        insertTotal[0] += Insert[i][0];
        insertTotal[1] += Insert[i][1];
        insertTotal[2] += Insert[i][2];

        // vector deletion time
        start = high_resolution_clock::now();
        codeVector.erase(codeVector.begin() + codeVector.size() / 2);
        end = high_resolution_clock::now();
        vectorSpeed = duration_cast<nanoseconds>(end - start);
        
        // list deletion time
        start = high_resolution_clock::now();
        it = codeList.begin();
        advance(it, codeList.size() / 2);
        codeList.erase(it);
        end = high_resolution_clock::now();
        listSpeed = duration_cast<nanoseconds>(end - start);

        // set deletion time
        start = high_resolution_clock::now();
        codeSet.erase(codeToInsert);
        end = high_resolution_clock::now();
        setSpeed = duration_cast<nanoseconds>(end - start);

        Delete[i][0] = vectorSpeed.count();
        Delete[i][1] = listSpeed.count();
        Delete[i][2] = setSpeed.count();

        deleteTotal[0] += Delete[i][0];
        deleteTotal[1] += Delete[i][1];
        deleteTotal[2] += Delete[i][2];

        // temp removing print statements to use averages

        /*
        // print loop results in table
        cout << "Number of simulations: " << i + 1 << endl;

        // print values in clean list
        cout << setw(12) << right << "Operation" 
         << setw(setWidth) << right << "Vector"
         << setw(setWidth) << right << "List"
         << setw(setWidth) << right << "Set"
         << endl;
    
        // printing values using 3D array
        op = "\tRead";
        printLine(op, results[i][0][0], results[i][0][1], results[i][0][2]);
        op = "\tSort";
        printLine(op, results[i][1][0], results[i][1][1], results[i][1][2]);
        op = "\tInsert";
        printLine(op, results[i][2][0], results[i][2][1], results[i][2][2]);
        op = "\tDelete";
        printLine(op, results[i][3][0], results[i][3][1], results[i][3][2]);

        */

        // cleaning out for next loop
        codeVector.clear();
        codeList.clear();
        codeSet.clear();
    }

    return 0;
}

void printLine(string operation, long long vectorVal, long long listVal, long long setVal) {
    cout << setw(12) << right << operation 
         << setw(setWidth) << right << vectorVal 
         << setw(setWidth) << right << listVal 
         << setw(setWidth) << right << setVal 
         << endl;
}
/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<nanoseconds>(end - start)
duration.count() references elapsed nanoseconds
*/