//
// Created by Hamit Burak Emre on 11/05/17.
//

#include "region.h"

Region::Region(const int minBorder[3] , const int maxBorder[3]) {
    for (int i = 0; i < 3; i++) {
        m_minBorder[i] = minBorder[i];
        m_maxBorder[i] = maxBorder[i];
    }

    m_divDimension = 'x';

    m_parent = this;
}

Region::Region(const int minBorder[3], const int maxBorder[3], char parentDivDim, Region* parent) {
    setBorders(minBorder, maxBorder);

    if(isCell(minBorder, maxBorder)) {
        m_parent = parent;
        m_divDimension = 'x';

        m_leftPart = NULL;
        m_rightPart = NULL;
    } else {
        m_parent = parent;
        m_divDimension = nextDivDim(parentDivDim, minBorder, maxBorder);

        if(m_divDimension == 'x') {
            int total = minBorder[0] + maxBorder[0];
            int passNext = (total > 0) ? 1 : -1 ;
            int mid = total / 2;
            int secondStart = mid + passNext;
            const int leftMax[3] = {mid, maxBorder[1], maxBorder[2]};
            const int rightMin[3] = {secondStart, minBorder[1], minBorder[2]};
            m_leftPart = new Region(minBorder,leftMax, m_divDimension, this);
            m_rightPart = new Region(rightMin, maxBorder, m_divDimension, this);
        }else if(m_divDimension == 'y') {
            int total = minBorder[1] + maxBorder[1];
            int passNext = (total > 0) ? 1 : -1 ;
            int mid = total / 2;
            int secondStart = mid + passNext;
            const int leftMax[3] = {maxBorder[0], mid, maxBorder[2]};
            const int rightMin[3] = {maxBorder[0], secondStart, maxBorder[2]};
            m_leftPart = new Region(minBorder,leftMax, m_divDimension, this);
            m_rightPart = new Region(rightMin, maxBorder, m_divDimension, this);
        }else if(m_divDimension == 'z') {
            int total = minBorder[2] + maxBorder[2];
            int passNext = (total > 0) ? 1 : -1 ;
            int mid = total / 2;
            int secondStart = mid + passNext;
            const int leftMax[3] = {maxBorder[0], maxBorder[1], mid};
            const int rightMin[3] = {maxBorder[0], maxBorder[1], secondStart};
            m_leftPart = new Region(minBorder,leftMax, m_divDimension, this);
            m_rightPart = new Region(rightMin, maxBorder, m_divDimension, this);
        }
    }
}

char Region::nextDivDim(char currentDivDim, const int minBorder[3], const int maxBorder[3]) {
    if(currentDivDim == 'x') {
        if(minBorder[1] != maxBorder[1])
            return 'y';
        else if(minBorder[2] != maxBorder[2])
            return 'z';
        else if(minBorder[0] != maxBorder[0])
            return 'x';
    } else if(currentDivDim == 'y') {
        if(minBorder[2] != maxBorder[2])
            return 'z';
        else if(minBorder[0] != maxBorder[0])
            return 'x';
        else if(minBorder[1] != maxBorder[1])
            return 'y';
    } else if(currentDivDim == 'z') {
        if(minBorder[0] != maxBorder[0])
            return 'x';
        else if(minBorder[1] != maxBorder[1])
            return 'y';
        else if(minBorder[2] != maxBorder[2])
            return 'z';
    }

    return 'y';
}

bool Region::isCell(const int minBorder[3], const int maxBorder[3]) {
    bool result = true;

    for (int i = 0; i < 3; i++) {
        result = result && (minBorder[i] == maxBorder[i]);
    }

    return result;
}

void Region::setBorders(const int minBorder[3], const int maxBorder[3]) {
    for(int i = 0; i < 3; i++) {
        m_minBorder[i] = minBorder[i];
        m_maxBorder[i] = maxBorder[i];
    }
}

int Region::getMinBorder(char dim) const {
    if (dim == 'x'){
        return m_minBorder[0];
    } else if (dim == 'y') {
        return m_minBorder[1];
    }

    return m_minBorder[2];
}

int Region::getMaxBorder(char dim) const {
    if (dim == 'x'){
        return m_maxBorder[0];
    } else if (dim == 'y') {
        return m_maxBorder[1];
    }

    return m_maxBorder[2];
}


Region::~Region() {

}

Region::Region(const Region &other) {
    setBorders(other.m_minBorder, other.m_maxBorder);

    m_parent = other.m_parent;
    m_rightPart = other.m_rightPart;
    m_leftPart = other.m_leftPart;
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


long Region::isCell(const int *, const int *) {
    return 0;
}
