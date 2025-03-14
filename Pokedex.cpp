#include <fstream>
#include "json.hpp"
#include "Pokedex.h"

using namespace std;

using json = nlohmann::json;

void Pokedex::selectFirstPokemon(Pokemon& pokemon) {
    int id;
    do {
        cout << "Enter the number and select your first Pokemon:\n"
            << "1. Bulbasaur\n"
            << "2. Charmander\n"
            << "3. Squirtle\n"
            << endl;
        cout << "Select your first Pokemon: ";
        cin >> id;
    } while (id < 1 || id > 3);

    if (id == 2)
        id = 4;
    if (id == 3)
        id = 7;
    Pokemon firstPokemon = pokemon.searchPokemon(id);
    myPokedex[firstPokemon.getId()].push_back(firstPokemon);
    cout << firstPokemon.getName() << " added to your Pokedex...\n" << endl;
}

void Pokedex::capturePokemon(const Pokemon p) {
    cout << p.getName() << " added to your Pokedex...\n" << endl;
    myPokedex[p.getId()].push_back(p);
}

void Pokedex::deletePokemon(int id, int index) {
    auto it = myPokedex.find(id);
    if (it != myPokedex.end() && index >= 0 && index < it->second.size()) {
        it->second.erase(it->second.begin() + index);
        cout << "Pokemon transferred\n" << endl;
        if (it->second.empty())
            myPokedex.erase(it);  
    }
    else
        cout << "You don't have that Pokemon\n" << endl;
}

void Pokedex::showMyPokemons() {
    for (const auto& pair : myPokedex) {
        int id = pair.first; 
        const auto& pokemon = pair.second; 

        for (int i = 0; i < pokemon.size(); i++) {
            const auto& p = pokemon[i];
            cout << "- #" << p.getId() << " " << p.getName() << " -" << endl;
            cout << "  [Id:" << i + 1 << "]" << endl;
            cout << "  Type: " << p.getType() << endl
                <<"  Health: " << p.getHealth() << endl << endl;
        }
    }
}

void Pokedex::saveMyPokedex(const string& filename) {
    ofstream file(filename + ".json");

    if (!file) {
        cout << "Error while creating file";
        return;
    }

    json j;
    j["pokemon"] = json::array(); 

    for (const auto& pair : myPokedex) {
        int id = pair.first;
        const auto& pokemon = pair.second;
        for (const auto& p : pokemon) {
            j["pokemon"].push_back({
                {"id", p.getId()},
                {"name", p.getName()}, {"health", p.getHealth()},
                {"type", p.getType()}, {"img", p.getImage()}
                });
        }
    }

    file << j.dump(4);  
    cout << "Pokemon saved in " << filename << "\n" << endl;
}


void Pokedex::loadMyPokedex(const string& filename) {
    ifstream file(filename + ".json");
    if (!file) {
        cout << "Pokedex " << filename << " not found\n" << endl;
        return;
    }

    json j;
    file >> j;
    myPokedex.clear();

    for (const auto& item : j["pokemon"]) {
        Pokemon p;
        p.setId(item["id"]);
        p.setName(item["name"]);
        p.setHealth(item["health"]);
        p.setType(item["type"]);
        p.setImage(item["img"]);
        myPokedex[p.getId()].push_back(p);
    }

    cout << "Pokedex '" << filename << "' load correctly\n" << endl;
}

Pokemon* Pokedex::selectMyPokemon(int pokeIndex, int index) {
    auto it = myPokedex.find(pokeIndex);
    if (it != myPokedex.end() && index >= 0 && index < it->second.size()) {
        return &(it->second[index]);
    }
    cout << "You don't have that Pokemon\n" << endl;
    return nullptr;
}

bool Pokedex::isMine(int id, int index) {
    auto it = myPokedex.find(id);
    if (it != myPokedex.end() && index >= 0 && index < it->second.size())
        return true;
    return false;
}

bool Pokedex::attackPokemon(Pokemon* attacker, Pokemon& defender) {
    int damage = attacker->attack();
    int health = defender.getHealth();
    defender.setHealth( health -= damage);
    cout << attacker->getName() << " has dealt " << damage << " damage to " << defender.getName() << endl;

    if (defender.getHealth() <= 0) {
        defender.setHealth(0);
        return true; 
    }
    return false; 
}


bool Pokedex::battle(Pokemon* myPokemon, Pokemon& newPokemon) {
    while (myPokemon->getHealth() > 0 && newPokemon.getHealth() > 0) {
        cout << "---- " << myPokemon->getName() << "'s health: " << myPokemon->getHealth()
            << " ---- " << newPokemon.getName() << "'s health: " << newPokemon.getHealth() << " ---- " << endl;

        if (attackPokemon(myPokemon, newPokemon)) {
            cout << "\n" << myPokemon->getName() << " has won!" << endl;
            capturePokemon(newPokemon);
            return true;
        }

        if (attackPokemon(&newPokemon, *myPokemon)) {
            cout << "\n" << myPokemon->getName() << " has lost!" << endl;
            return false;
        }
    }
    return false;
}
