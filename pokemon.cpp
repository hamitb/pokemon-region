//
// Created by Hamit Burak Emre on 11/05/17.
//
#include "pokemon.h"

Pokemon::Pokemon(const string &n, const string &t, int m) {
    m_min = m;
}

Pokemon::Pokemon(const Pokemon &other) {
    m_min = other.m_min;
}

Pokemon::~Pokemon() {

}

const string &Pokemon::getName() const {
    return "";
}

bool Pokemon::operator>>(const Pokemon &) {
    return false;
}

Pokemon operator&(Pokemon &, Pokemon &) {
    return Pokemon(__1::basic_string<char, char_traits<char>, allocator<char>>(),
                   __1::basic_string<char, char_traits<char>, allocator<char>>(), 0);
}

Pokemon &Pokemon::operator=(const Pokemon &) {

    return <#initializer#>;
}
