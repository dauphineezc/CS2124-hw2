// Zoe Dauphinee, homework 2, Functions; Structs; and File I/O

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


struct Warrior {
    string name;
    int strength;
};


void open_file(ifstream& file);

void read_file(ifstream& file, vector<Warrior>& warriors);

void create_warrior(const string& name, int strength, vector<Warrior>& warriors);

size_t get_warrior(const string& name, vector<Warrior>& warriors);

void battle(Warrior& fighter1, Warrior& fighter2);

void print_status(const vector<Warrior>& warriors);


int main() {
    ifstream file;
    vector<Warrior> warriors;
    open_file(file);
    read_file(file, warriors);
    file.close();
}


void open_file(ifstream& file) {
    file.open("warriors.txt");
    // check to make sure file opened correctly
    while(!file) {
        cerr << "failed to open warriors.txt";
        exit(1);
    }
}

void read_file(ifstream& file, vector<Warrior>& warriors) {
    string command;
    string name;
    string fighter1_name;
    string fighter2_name;
    int strength;
    while(file >> command) {
        // calls to create new warrior
        if (command == "Warrior") {
            file >> name >> strength;
            create_warrior(name, strength, warriors);
        }
        // finds the two warriors from their names and calls Battle
        else if (command == "Battle") {
            file >> fighter1_name >> fighter2_name;
            size_t fighter1_index = get_warrior(fighter1_name, warriors);
            size_t fighter2_index = get_warrior(fighter2_name, warriors);
            if (fighter1_index == warriors.size()) {
                cout << fighter1_name << " does not exist\n";
            } 
            else if (fighter2_index == warriors.size()) {
                cout << fighter2_name << " does not exist\n";
            }
            else { 
                battle(warriors[fighter1_index], warriors[fighter2_index]); 
            }
        }
        // calls print_status
        else if (command == "Status") {
            print_status(warriors);
        }
    }
}

void create_warrior(const string& name, int strength, vector<Warrior>& warriors) {
    // checks to see if a warrior with that name already exists
    for (size_t index = 0; index < warriors.size(); ++index) {
        if (warriors[index].name == name) {
            cout << "a warrior with that name already exists!" << endl;
        }
    }
    // creates new warrior and adds it to the vector
    Warrior new_warrior = {name, strength};
    warriors.push_back(new_warrior);
}

size_t get_warrior(const string& name, vector<Warrior>& warriors) {
    // returns the index of the warrior with passed in name if in the vector
    for (size_t index = 0; index < warriors.size(); ++index) {
        if (warriors[index].name == name) {
            return index;
        }
    }
    // if not in the vector, return the size of the vector
    return warriors.size();
}

void battle(Warrior& fighter1, Warrior& fighter2) {
    cout << fighter1.name << " battles " << fighter2.name << endl;
    // both already dead, print but don't change strengths
    if (fighter1.strength == 0 && fighter2.strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!\n";
    }
    // fighter 1 has strength 0
    else if (fighter1.strength == 0) {
        cout << "He's dead, " << fighter2.name << endl;
    }
    // fighter 2 has strength 0
    else if (fighter2.strength == 0) {
        cout << "He's dead, " << fighter1.name << endl;
    }
    // both fighters have strength
    else {
        // fighter 1 defeats fighter 2, change strengths accordingly
        if (fighter1.strength > fighter2.strength) {
            cout << fighter1.name << " defeats " << fighter2.name << endl;
            fighter1.strength -= fighter2.strength;
            fighter2.strength = 0;
        }
        // fighter 1 defeats fighter 2, change strengths accordingly
        else if(fighter1.strength < fighter2.strength) {
            cout << fighter2.name << " defeats " << fighter1.name << endl;
            fighter2.strength -= fighter1.strength;
            fighter1.strength = 0;
        }
        // fighter 1 defeats fighter 2, change strengths accordingly
        else if (fighter1.strength == fighter2.strength) {
            cout << "Mutual Annihilation: " << fighter1.name << " and " 
            << fighter2.name << " die at each other's hands\n";
            fighter1.strength = 0;
            fighter2.strength = 0;
        }
    }
}

void print_status(const vector<Warrior>& warriors) {
    cout << "There are: " << warriors.size() << " warriors\n";
    for (size_t index = 0; index < warriors.size(); ++index) {
        cout << "Warrior: " << warriors[index].name << ", strength: " 
        << warriors[index].strength << endl;
    } 
}