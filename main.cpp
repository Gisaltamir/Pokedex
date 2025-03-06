#include <iostream>
#include <cctype>
#include "Pokedex.h"

using namespace std;

int main() {
    int option;
    Pokemon pokemon = Pokemon();
    pokemon.readJson();
    Pokedex myPokedex = Pokedex();

    while (true) {
        cout << "Select an option:\n"
            << "1: See all pokemons\n"
            << "2: Add a pokemon to your pokedex\n"
            << "3: See my pokemons\n"
            << "4: Transfer a pokemon to Professor Oak\n"
            << "5: Save your Pokedex\n"
            << "6: Load your Pokedex\n"
            << "7: Exit\n" << endl;

        cin >> option;

        switch (option) {
        case 1:
            pokemon.showAll();
            break;

        case 2: {
            int pokeId;
            cout << "Insert the pokemon number you want to capture: ";
            cin >> pokeId;

            if (pokeId > 151 || pokeId < 1) {
                cout << "Not a valid pokemon number.\n  " << endl;
                break;
            }

            Pokemon newPokemon = pokemon.searchPokemon(pokeId);
            if (newPokemon.id != 0)
                myPokedex.capturePokemon(newPokemon);
            break;
        }

        case 3: {
            myPokedex.showMyPokemons();
            break;
        }

        case 4: {
            int pId;
            cout << "Loading your pokemon..." << endl;
            myPokedex.showMyPokemons();
            cout << "Insert the pokemon number you want to transfer: ";
            cin >> pId;
            myPokedex.deletePokemon(pId);
            break;
        }

        case 5: {
            string nameS;
            cout << "Write the name of your pokedex: ";
            cin >> nameS;
            transform(nameS.begin(), nameS.end(), nameS.begin(),
                [](unsigned char c) { return std::tolower(c); });
            myPokedex.saveMyPokedex(nameS);
            break;
        }

        case 6: {
            string nameL;
            cout << "Write the name of your pokedex: ";
            cin >> nameL;
            transform(nameL.begin(), nameL.end(), nameL.begin(),
                [](unsigned char c) { return std::tolower(c); });
            myPokedex.loadMyPokedex(nameL);
            break;
        }

        case 7:
            cout << "Exiting...\n";
            return 0;

        default:
            cout << "Invalid option. Try again.\n" << endl;
            break;
        }
    }

    return 0;
}
