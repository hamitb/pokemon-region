//
// Created by Hamit Burak Emre on 11/05/17.
//

#include "region.h"

Region::Region(const int minBorder[3] , const int maxBorder[3]) {
    for (int i = 0; i < 3; i++) {
        m_minBorder[i] = minBorder[i];
        m_maxBorder[i] = maxBorder[i];
    }
}

Region::Region(const Region &) {

}

Region::~Region() {

}

int Region::getMinBorder(char dim) const {
    if (dim == 'x'){
        return m_minBorder[0];
    } else if (dim == 'y') {
        return m_minBorder[1];
    } else if (dim == 'z') {
        return m_minBorder[2];
    }
}

int Region::getMaxBorder(char dim) const {
    if (dim == 'x'){
        return m_maxBorder[0];
    } else if (dim == 'y') {
        return m_maxBorder[1];
    } else if (dim == 'z') {
        return m_maxBorder[2];
    }
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
