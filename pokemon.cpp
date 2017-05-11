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

Pokemon::Pokemon(const Pokemon &other) {
    m_name = other.m_name;
    m_min = other.m_min;
    m_type = other.m_type;
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

    bool canEvolve = (m_exp >= nextVersion.m_min) ;

    if (canEvolve) {
        m_name = nextVersion.m_name ;
        m_type = nextVersion.m_type ;
        m_min  = nextVersion.m_min ;

        return true;
    }

    return false;
}

Pokemon &Pokemon::operator=(const Pokemon &) {
    return <#initializer#>;
}


