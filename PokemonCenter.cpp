#include "PokemonCenter.h"
#include <iostream>

using namespace std;

void PokemonCenter::enqueue(Pokemon* p) {
    if (isHealed(p))
        cout << p->getName() << " has already max health.\n" <<endl;
    else{
        cout << p->getName() << " is added to the healing queue!" << endl;
        healingQueue.push(p);
    }
}

void PokemonCenter::dequeue() {
    if (!healingQueue.empty()) {
        Pokemon* p = healingQueue.front();
        p->setHealth(100);  // Set the health back to 100 
        
        cout << p->getName() << " has been healed to full health!" << endl;
        healingQueue.pop();  // Remove from queue
    }
    else {
        cout << "No Pokemon in the queue!" << endl;
    }
}

void PokemonCenter::showQueue() {
    if (isEmpty()) {
        cout << "The healing queue is empty!" << endl;
        return;
    }

    queue<Pokemon*> tempQueue = healingQueue;;
    while (!tempQueue.empty()) {
        cout <<  tempQueue.front()->getName() << ", " << endl;
        tempQueue.pop();
    }
}

bool PokemonCenter::isEmpty() {
    if (healingQueue.empty())
        return true;
    return false;
}

bool PokemonCenter::isHealed(const Pokemon *p) {
    if (p->getHealth() == 100)
        return true;
    return false;
}
