#include <fstream>
#include "json.hpp"
#include "Pokedex.h"

using namespace std;

using json = nlohmann::json;

void Pokedex::capturePokemon(const Pokemon p) {
    cout << p.name << " added to your Pokedex\n" << endl;
    myPokedex.push_back(p);
}

void Pokedex::deletePokemon(int id) {
    string name;
    auto it = std::find_if(myPokedex.begin(), myPokedex.end(), [id](const Pokemon& p) {
        return p.id == id;
        });
    if (it != myPokedex.end()){
        cout << "Pokemon transferred\n" << endl;
        myPokedex.erase(it);
    }
    else
        cout << "You don't have that pokemon\n" << endl;
}

void Pokedex::showMyPokemons() {
    for (auto p : myPokedex) {
        cout << "- " << p.id << " " << p.name << " -" << endl;
        cout << "Type: " << p.type << endl << endl;
    }
    cout << endl;
}

void Pokedex::saveMyPokedex(const string& filename) {
    ofstream file(filename + ".json");

    if (!file) {
        cout << "Error while creating file";
        return;
    }

    json j;
    j["pokemon"] = json::array();  // Convierte el set a JSON

    for (const auto& p : myPokedex) {
        j["pokemon"].push_back({ {"id", p.id}, {"name", p.name}, {"type", p.type}, {"img", p.image} });
    }


    file << j.dump(4);  // Guarda el JSON con formato bonito
    file.close();
    cout << "Pokemon saved in " << filename << "\n" << endl;
}


void Pokedex::loadMyPokedex(const string& filename) {
    ifstream file(filename + ".json");
    if (!file) {
        cout << "Pokedex " << filename << " not found\n" << endl;
        return;
    }

    myPokedex.clear();
    json j;
    file >> j;
    
    for (const auto& item : j["pokemon"]) {
        Pokemon p;
        p.id = item["id"];
        p.name = item["name"];
        p.type = item["type"];
        p.image = item["img"];
        myPokedex.push_back(p);
    }

    cout << "Pokedex '" << filename << "' load correctly\n" << endl;
}
