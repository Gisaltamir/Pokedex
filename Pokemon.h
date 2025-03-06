#include <set>
#include <iostream>
#include "json.hpp"

using namespace std;

class Pokemon {
public:
    int id;
    string name;
    string type;
    string image;
    set<Pokemon> pokemon;
    bool operator<(const Pokemon& other) const;
    void readJson();
    void showAll();
    Pokemon searchPokemon(int id);
    Pokemon() : id(0) {}
};