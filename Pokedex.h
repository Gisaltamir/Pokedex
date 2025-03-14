#ifndef POKEDEX_H
#define POKEDEX_H
#include <iostream>
#include <vector>
#include "Pokemon.h"

using namespace std;

class Pokedex {
private:
    unordered_map<int, vector<Pokemon>> myPokedex;

public:
    Pokedex::Pokedex() { cout << "Pokedex created... \n"; };
    void selectFirstPokemon(Pokemon& pokemon);
    void capturePokemon(Pokemon p);
    void deletePokemon(int id, int index);
    void showMyPokemons();
    void saveMyPokedex(const string& filename);
    void loadMyPokedex(const string& filename);
    Pokemon* selectMyPokemon(int id, int index);
    bool battle(Pokemon* mine, Pokemon& newPokemon);
    bool attackPokemon(Pokemon* attacker, Pokemon& defender);
    bool isMine(int pokeIndex, int index);

};
#endif
