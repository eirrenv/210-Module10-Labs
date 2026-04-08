#include <iostream>
#include <map>
#include <vector>
#include <string> // for getline
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

    // clear villager for posterity
    villager.clear();

    return 0;
}

// menu function for scalable menu
void menu(map<string, tuple<int, string, string>> v) {
    // int to contain user menu choice
    int choice = -1;

    cout << "1. Add Villager" << endl
         << "2. Delete Villager" << endl    
         << "3. Increase Friendship" << endl
         << "4. Decrease Friendship" << endl
         << "5. Search For Villager" << endl
         << "4. Exit" << endl;
    cin >> choice;
    while (choice != 6) {
        while (choice < 1 || choice > 6) {
            cout << "Please input a choice between 1 to 4:" << endl;
            cout << "1. Increase Friendship" << endl
            << "2. Decrease Friendship" << endl
            << "3. Search For Villager" << endl
            << "4. Exit" << endl;
            cin >> choice;
            cout << endl;
        }
        if (choice == 1) {
            // add a villager
            string name;
            int level;
            string species;
            string phrase;
            cout << "Villager name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Friendship level: ";
            cin >> level;
            cin.ignore();
            cout << "Species: "; 
            getline(cin, species);
            cout << "Catchphrase: ";
            getline(cin, phrase);
            v.insert({name, {level, species, phrase}});
        }
        else if (choice == 2) {
            // delete a villager
            string delV;
            cout << "Please enter a villager to delete: ";
            cin.ignore();
            getline(cin, delV);
            auto it = v.find(delV);
            if (it != v.end()) {
                v.erase(it);
                cout << delV << " has been deleted." << endl;
            }
            else {
                cout << endl << delV << " is not a villager." << endl;
            }

        }
        else if (choice == 3) {
            // adds friendship to all villagers by 1
            for (auto &pair : v) {
            if (get<0>(pair.second) != 10) {
                    get<0>(pair.second) += 1;
            }
            }
        }
        else if (choice == 4) {
            // removes friendship from all villagers by 1
            for (auto &pair : v) {
            if (get<0>(pair.second) != 0) {
                    get<0>(pair.second) -= 1;
            }
            }
        }
        else if (choice == 5) {
            // search for an element using .find() to avoid errors
            string searchKey = "";
            cin.ignore();
            cout << "Please enter the villager you would like to search for: ";
            getline(cin, searchKey);
            auto it = v.find(searchKey);
            if (it != v.end()) {
                cout << searchKey << " is a villager!" << endl;
            }
            else {
                cout << endl << searchKey << " is not a villager." << endl;
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
        cout << "Please choose another option: ";
        cin >> choice;
        cout << endl;
    }
    cout << "Exiting program." << endl;
}