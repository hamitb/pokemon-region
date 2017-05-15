//
// Created by Hamit Burak Emre on 11/05/17.
//

#include "trainer.h"

Trainer::Trainer(const Trainer &other) {
    m_name = other.m_name;
    m_firstPokemon = other.m_firstPokemon;
    for(std::vector<const Pokemon*>::iterator it = pokeVector.begin(); it != pokeVector.end(); ++it) {
        pokeVector.push_back(*it);
    }

    for(int i = 0; i < 3; i++) {
        m_minView[i] = other.m_minView[i];
        m_maxView[i] = other.m_maxView[i];
    }
}

Trainer::~Trainer() {

}

Trainer::Trainer(const string &name, const Pokemon &pokemon, const int minView[3], const int maxView[3]) {
    m_name = name;
    m_firstPokemon = &pokemon;
    catchPokemon(pokemon);
    for(int i = 0; i < 3; i++) {
        m_minView[i] = minView[i];
        m_maxView[i] = maxView[i];
    }
}

void Trainer::scanRegion(Region &region) {

    for(int i = region.getMinBorder('x') ; i <= region.getMaxBorder('x'); i++) {
        for(int j = region.getMinBorder('y') ; j <= region.getMaxBorder('y'); j++) {
            for(int k = region.getMinBorder('z') ; k <= region.getMaxBorder('z'); k++) {
                if(isBetween(i, j, k)){

                    try {
                        Pokemon* pokeFound = &(region(i, j, k));
                        pokeVector.push_back(pokeFound);
                    }
                    catch (exception& e) {
                    }
                }
            }
        }
    }

}

ostream &showPokemons(ostream &stream, const Trainer &trainer) {
    for(std::vector<const Pokemon*>::const_iterator it = trainer.pokeVector.begin(); it != trainer.pokeVector.end(); ++it) {
        stream << (**it).getName() << endl;
    }
}

bool Trainer::isBetween(int x, int y, int z) {
    if((m_minView[0] <= x) && (m_maxView[0] >= x) && (m_minView[1] <= y) && (m_maxView[1] >= y) && (m_minView[2] <= z) && (m_maxView[2] >= z))
        return true;

    return false;
}

