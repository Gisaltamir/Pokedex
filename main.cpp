#include <iostream>
#include <cctype>
#include "Pokedex.h"
#include "PokemonCenter.h"

using namespace std;

void clean_screen() {
    cout << "Press any key to return to menu...";
    cin.get();
    cin.get();
    system("cls");
}

int main() {
    srand(time(0));
    int option;
    PokemonCenter pokemonCenter = PokemonCenter();
    Pokemon pokemon = Pokemon();
    pokemon.readJson();
    Pokedex myPokedex = Pokedex();
    myPokedex.selectFirstPokemon(pokemon);

    while (true) {
        cout << "Pokemon World Menu:\n"
        << "1: See all Pokemon\n"
        << "2: Capture Pokemon\n"
        << "3: See my Pokemon\n"
        << "4: Transfer a Pokemon to Professor Oak\n"
        << "5: Send your Pokemon to Pokemon Center\n"
        << "6: Save your Pokedex\n"
        << "7: Load your Pokedex\n"
        << "8: Exit\n" << endl;

        cout << "Select an option: ";
        cin >> option;

        switch (option) {
        case 1:
            pokemon.showAll();
            clean_screen();
            break;

        case 2: {
            int pokeId, myP, index;
            cout << "Insert the Pokemon number (#) you want to capture: ";
            cin >> pokeId;
            Pokemon newPokemon = pokemon.searchPokemon(pokeId);

            if (newPokemon.getId() == 0)
                break;

            cout << "Time to fight for " << newPokemon.getName() << "!" << endl;
            cout << "Select your Pokemon number (#) and Id: \n";
            myPokedex.showMyPokemons();
            cout << "Pokemon number (#): ";
            cin >> myP;
            cout << "Id: ";
            cin >> index;
            cout << endl;

            Pokemon *myPokemon = myPokedex.selectMyPokemon(myP, index - 1);
            
            if (!myPokemon) {
                clean_screen();
                break;
            }

            bool won = myPokedex.battle(myPokemon, newPokemon);

            if (!won)
                cout << "You didn't capture " << newPokemon.getName() << ". \n" << endl;
            
            
            clean_screen();
            break;
        }

        case 3: {
            myPokedex.showMyPokemons();
            clean_screen();
            break;
        }

        case 4: {
            int pId, pIndex;
            cout << "Loading your Pokemon to transfer..." << endl;
            cout << "Select your pokemon number (#) and Id: \n";
            myPokedex.showMyPokemons();
            cout << "Pokemon number (#): ";
            cin >> pId;
            cout << "Id: ";
            cin >> pIndex;
            cout << endl;
            myPokedex.deletePokemon(pId, pIndex - 1);
            clean_screen();
            break;
        }
        case 5: {
            
            cout << "Welcome to the Pokemon Center\n";
            int newId, pokeNumber;
            cout << "Enter all the Pokemon you want to cure. When you finish press 0 to start curing them...\n"
            << "Which Pokemon do you want to cure? \n" << endl;
            cout << "Select your Pokemon number (#) and Id: \n";
            myPokedex.showMyPokemons();
            do{
                cout << "Pokemon number (#): ";
                cin >> pokeNumber;
                if (pokeNumber == 0) {
                    break;
                }
                cout << "Id: ";
                cin >> newId;
                cout << endl;    
                if (newId == 0) {
                    break;
                }
                if (!myPokedex.isMine(pokeNumber, newId - 1)) {
                    cout << "You don't have that Pokemon" << endl;
                    continue;
                }
                Pokemon* illPokemon= myPokedex.selectMyPokemon(pokeNumber, newId - 1);
                if(illPokemon != nullptr)
                    pokemonCenter.enqueue(illPokemon);
                
            } while (newId != 0 || pokeNumber != 0);

            while (!pokemonCenter.isEmpty()){
                pokemonCenter.dequeue();
            }
            cout << endl;
            clean_screen();
            break;
        }

        case 6: {
            string nameS;
            cout << "Write the name of your Pokedex: ";
            cin >> nameS;
            transform(nameS.begin(), nameS.end(), nameS.begin(),
                [](unsigned char c) { return std::tolower(c); });
            myPokedex.saveMyPokedex(nameS);
            clean_screen();
            break;
        }

        case 7: {
            string nameL;
            cout << "Write the name of your Pokedex: ";
            cin >> nameL;
            transform(nameL.begin(), nameL.end(), nameL.begin(),
                [](unsigned char c) { return std::tolower(c); });
            myPokedex.loadMyPokedex(nameL);
            clean_screen();
            break;
        }

        case 8:
            cout << "Exiting...\n";
            return 0;

        default:
            cout << "Invalid option. Try again.\n" << endl;
            clean_screen();
            break;
        }
    }

    return 0;
}
