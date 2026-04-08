#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    // declarations
    map<string, tuple<int, string, string>> villager;

    // insert elements into the map
    // note how the right-hand side of the assignment are the vector elements
    villager["Audie"] = {8, "Duck", "Quack!"};
    villager["Raymond"] = {4, "Dog", "Woof."};
    villager.insert({"Marshal", {3, "Tiger", "Rawr!"}});

    // commenting out demo code to work on declarations
    

    // access the map using a range-based for loop
    cout << "Villagers and their friendship level, species, and catchphrase (range-based for loop):" << endl;
    for (auto pair : villager) {
        cout << pair.first << ": ";
        auto [villagerLevel, villagerSpecies, villagerPhrase] = pair.second;
        cout << "Friendship level: " << villagerLevel << " "
             << "Species: " << villagerSpecies << " " 
             << "Phrase: " << villagerPhrase;
        cout << endl;
    }
    /*
    // access the map using iterators
    cout << "\nVillagers and their favorite colors (iterators):" << endl;
    for (map<string, vector<string>>::iterator it = villagerColors.begin(); 
                                               it != villagerColors.end(); ++it) {
        cout << it->first << ": ";
        for (auto color : it->second) {
            cout << color << " ";
        }
        cout << endl;
    }

    // delete an element
    villagerColors.erase("Raymond");

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

    // report size, clear, report size again to confirm map operations
    cout << "\nSize before clear: " << villager.size() << endl;
    villager.clear();
    cout << "Size after clear: " << villager.size() << endl;

    

    return 0;
}