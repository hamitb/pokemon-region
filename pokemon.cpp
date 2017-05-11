//
// Created by Hamit Burak Emre on 11/05/17.
//
#include "pokemon.h"

Pokemon::Pokemon(const string &n, const string &t, int m) {
    m_min = m;
    m_name = n;
    m_type = t;
}

Pokemon::Pokemon(const Pokemon &other) {
    m_name = other.m_name;
    m_min = other.m_min;
    m_type = other.m_type;
}

Pokemon::~Pokemon() {

}

const string &Pokemon::getName() const {
    return "";
}

bool Pokemon::operator>>(const Pokemon &) {
    return false;
}

Pokemon &Pokemon::operator=(const Pokemon &) {
    return <#initializer#>;
}
