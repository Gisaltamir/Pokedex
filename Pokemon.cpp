#include <fstream>
#include "Pokemon.h"

using namespace std;

using json = nlohmann::json;

bool Pokemon::operator<(const Pokemon& other) const {
    return id < other.id;
}

void Pokemon::readJson() {
    ifstream file("pokedex.json");
    if (!file.is_open()) {
        cout << "Error trying to open JSON\n";
        return;
    }

    json j;
    file >> j;

    for (const auto& item : j["pokemon"]) {
        Pokemon p;
        p.id = item["id"];
        p.name = item["name"];
        p.type = item["type"][0];
        p.image = item["img"];
        pokemon.insert(p);
    }
}

void Pokemon::showAll() {
    for (auto p : pokemon) {
        cout << "- " << p.id << " " << p.name << " -" << endl;
        cout << "Type: " << p.type << endl << endl;
    }
}

Pokemon Pokemon::searchPokemon(int id) {
    Pokemon poke = Pokemon();
    for (Pokemon p : pokemon) {
        if (p.id == id)
            poke = p;
    }
    return poke;
}

