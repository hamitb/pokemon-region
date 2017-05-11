//
// Created by Hamit Burak Emre on 11/05/17.
//

#include "region.h"

Region::Region(const int *, const int *) {

}

Region::Region(const Region &) {

}

Region::~Region() {

}

int Region::getMinBorder(char) const {
    return 0;
}

int Region::getMaxBorder(char) const {
    return 0;
}

void Region::placePokemon(const Pokemon &, int, int, int) {

}

Pokemon &Region::operator()(int, int, int) {
    return <#initializer#>;
}

int Region::getPokemonCount(const int *, const int *) const {
    return 0;
}

Region Region::crop(const int *, const int *) const {
    return Region(NULL, NULL);
}

void Region::patch(Region) {

}

Region &Region::operator=(const Region &) {
    return <#initializer#>;
}
