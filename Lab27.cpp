#include <iostream>
#include <map>
#include <vector>
using namespace std;

void menu(map<string, tuple<int, string, string>> v); // prototype for menu function, moving villager printing into function

int main() {
    // declarations
    map<string, tuple<int, string, string>> villager;

    
    // insert elements into the map
    // note how the right-hand side of the assignment are the vector elements
    villager["Audie"] = {8, "Duck", "Quack!"};
    villager["Raymond"] = {4, "Dog", "Woof."};
    villager.insert({"Marshal", {3, "Tiger", "Rawr!"}});

    menu(villager);

    // commenting out demo code to work on declarations
    // commenting so I can say Milestone 2

    /* placing back search function 

    // search for an element using .find() to avoid errors
    string searchKey = "Audie";
    auto it = villagerColors.find(searchKey);
    if (it != villagerColors.end()) {  // the iterator points to beyond the end of the map
                                       // if searchKey is not found
        cout << "\nFound " << searchKey << "'s favorite colors: ";
        for (auto color : it->second)  // range loop to traverse the value/vector
            cout << color << " ";
        cout << endl;
    } else
        cout << endl << searchKey << " not found." << endl;
        
    */

    // clear villager for posterity
    villager.clear();

    return 0;
}

// menu function for scalable menu
void menu(map<string, tuple<int, string, string>> v) {
    // int to contain user menu choice
    int choice = -1;

    cout << "1. Increase Friendship" << endl
         << "2. Decrease Friendship" << endl
         << "3. Search For Villager" << endl
         << "4. Exit" << endl;
    cin >> choice;
    while (choice != 4) {
        while (choice < 1 || choice > 4) {
            cout << "Please input a choice between 1 to 4:" << endl;
            cout << "1. Increase Friendship" << endl
            << "2. Decrease Friendship" << endl
            << "3. Search For Villager" << endl
            << "4. Exit" << endl;
            cin >> choice;
            cout << endl;
        }
        if (choice == 1) {
            for (auto &pair : v) {
            if (get<0>(pair.second) != 10) {
                    get<0>(pair.second) += 1;
            }
            }
        }
        else if (choice == 2) {
            for (auto &pair : v) {
            if (get<0>(pair.second) != 0) {
                    get<0>(pair.second) -= 1;
            }
            }
        }
        // moving villager printing into menu
        cout << "Villager details:" << endl;
        for (auto pair : v) {
            cout << pair.first;
            auto [villagerLevel, villagerSpecies, villagerPhrase] = pair.second;
            cout << " [" << villagerLevel << ", " << villagerSpecies << ", " << villagerPhrase << "]";
            cout << endl;
        }
        cin >> choice;
    }


    
}