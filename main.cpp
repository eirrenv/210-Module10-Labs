#include <iostream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <algorithm> // vector sort :)
#include <iomanip>
#include <numeric> // accumulate
using namespace std;
using namespace std::chrono;

// scalable
void printLine(string operation, long long vectorVal, long long listVal, long long setVal);

const int RUNS = 15; // how many runs
const int setWidth = 15; // width of print

const int OP = 4; // operations done in program
const int VLS = 3; // types of containers used in program

int main() {

    long long results[RUNS + 1][OP][VLS] = {0}; // accumulator container

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
        cout << "Number of simulations: " << i + 1 << endl;

        // print values in clean list
        cout << setw(12) << right << "Operation" 
         << setw(setWidth) << right << "Vector"
         << setw(setWidth) << right << "List"
         << setw(setWidth) << right << "Set"
         << endl;

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

        // add results to 3D array
        results[i][0][0] = vectorSpeed.count();
        results[i][0][1] = listSpeed.count();
        results[i][0][2] = setSpeed.count();

        // reading time print
        op = "\tRead";
        printLine(op, vectorSpeed.count(), listSpeed.count(), setSpeed.count());

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

        results[i][1][0] = vectorSpeed.count();
        results[i][1][1] = listSpeed.count();
        results[i][1][2] = -1;

        // test sort prints, set already sorted
        op = "\tSort";
        printLine(op, vectorSpeed.count(), listSpeed.count(), -1);

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

        results[i][2][0] = vectorSpeed.count();
        results[i][2][1] = listSpeed.count();
        results[i][2][2] = setSpeed.count();

        // test insert prints
        op = "\tInsert";
        printLine(op, vectorSpeed.count(), listSpeed.count(), setSpeed.count());

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

        results[i][3][0] = vectorSpeed.count();
        results[i][3][1] = listSpeed.count();
        results[i][3][2] = setSpeed.count();

        // test deletion prints
        op = "\tDelete";
        printLine(op, vectorSpeed.count(), listSpeed.count(), setSpeed.count());

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