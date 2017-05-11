//
// Created by Hamit Burak Emre on 11/05/17.
//
#include "pokemon.h"

Pokemon::Pokemon(const string &n, const string &t, int m) {
    m_min = m;
    m_name = n;
    m_type = t;
    m_exp = 0;
}

Pokemon::Pokemon(const Pokemon &otherPokemon) {
    m_name = otherPokemon.m_name;
    m_min = otherPokemon.m_min;
    m_type = otherPokemon.m_type;
}

Pokemon::~Pokemon() {
    // Nothing to destruct
}

const string &Pokemon::getName() const {
    return m_name;
}

bool Pokemon::operator>>(const Pokemon &nextVersion) {
    if (m_min < 0) {
        return false;
    }

    bool canEvolve = (m_exp >= m_min) ;

    if (canEvolve) {
        m_name = nextVersion.m_name;
        m_type = nextVersion.m_type;
        m_min  = nextVersion.m_min;
    }

    return canEvolve;
}

Pokemon operator&(Pokemon& firstPokemon, Pokemon& secondPokemon) {
    firstPokemon.gainExp();
    secondPokemon.gainExp();

    if(firstPokemon.m_type == "fire") {
        if(secondPokemon.m_type == "water"){
            return secondPokemon;
        }else if(secondPokemon.m_type == "grass"){
            return firstPokemon;
        }else if(secondPokemon.m_type == "electric"){
            return firstPokemon;
        }else if(secondPokemon.m_type == "flying"){
            return secondPokemon;
        }
    }else if(firstPokemon.m_type == "water"){
        if(secondPokemon.m_type == "fire"){
            return firstPokemon;
        }else if(secondPokemon.m_type == "grass"){
            return secondPokemon;
        }else if(secondPokemon.m_type == "electric"){
            return secondPokemon;
        }else if(secondPokemon.m_type == "flying"){
            return firstPokemon;
        }
    }else if(firstPokemon.m_type == "grass"){
        if(secondPokemon.m_type == "fire"){
            return secondPokemon;
        }else if(secondPokemon.m_type == "water"){
            return firstPokemon;
        }else if(secondPokemon.m_type == "electric"){
            return firstPokemon;
        }else if(secondPokemon.m_type == "flying"){
            return secondPokemon;
        }
    }else if(firstPokemon.m_type == "electric"){
        if(secondPokemon.m_type == "fire"){
            return secondPokemon;
        }else if(secondPokemon.m_type == "water"){
            return firstPokemon;
        }else if(secondPokemon.m_type == "grass"){
            return secondPokemon;
        }else if(secondPokemon.m_type == "flying"){
            return firstPokemon;
        }
    }else if(firstPokemon.m_type == "flying"){
        if(secondPokemon.m_type == "fire"){
            return firstPokemon;
        }else if(secondPokemon.m_type == "water"){
            return secondPokemon;
        }else if(secondPokemon.m_type == "grass"){
            return firstPokemon;
        }else if(secondPokemon.m_type == "electric"){
            return secondPokemon;
        }
    }
}

Pokemon &Pokemon::operator=(const Pokemon &otherPokemon) {
    if(this == &otherPokemon)
        return *this;

    m_name = otherPokemon.m_name;
    m_type = otherPokemon.m_type;
    m_min = otherPokemon.m_min;
    m_exp = otherPokemon.m_exp;

    return *this;
}

void Pokemon::gainExp() {
    m_exp++;
}


