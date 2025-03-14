#ifndef POKEMON_H
#define POKEMON_H
#include <set>
#include <iostream>
#include "json.hpp"

using namespace std;

class Pokemon {
private:
    int id;
    string name;
    string type;
    string image;
    int health;
    set<Pokemon> pokemon;

public:
    //Getters:
    int getId() const { return id; }
    string getName() const { return name; }
    string getType() const { return type; }
    string getImage() const { return image; }
    int getHealth() const { return health; }

    //Setters
    void setId(int newId) { id = newId; }
    void setName(string newName) { name = newName; }
    void setType(string newType) { type = newType; }
    void setImage(string newImage) { image = newImage; }
    void setHealth(int newHealth) { health = max(0, newHealth); }



    Pokemon() : id(0), health(100) {}
    bool operator<(const Pokemon& other) const;
    int attack();
    void showAll();
    void readJson();
    Pokemon searchPokemon(int id);
};

#endif
