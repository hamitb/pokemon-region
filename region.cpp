//
// Created by Hamit Burak Emre on 11/05/17.
//

#include "region.h"

Region::Region(const int minBorder[3] , const int maxBorder[3]) {
    for (int i = 0; i < 3; i++) {
        m_minBorder[i] = minBorder[i];
        m_maxBorder[i] = maxBorder[i];
    }

    m_divDimension = rootDivDim();
    m_parent = this;
    m_leftPart = NULL;
    m_rightPart = NULL;

    pokemon = NULL;

    if(m_divDimension == 'x') {
        int total = minBorder[0] + maxBorder[0];
        int passNext = (total > 0) ? 1 : -1 ;
        mid = total / 2;
        secondStart = mid + passNext;
        leftMax[0] = mid;
        leftMax[1] = maxBorder[1];
        leftMax[3] = maxBorder[2];

        rightMin[0] = secondStart;
        rightMin[1] = minBorder[1];
        rightMin[2] = minBorder[2];
    }else if(m_divDimension == 'y') {
        int total = minBorder[1] + maxBorder[1];
        int passNext = (total > 0) ? 1 : -1 ;
        mid = total / 2;
        secondStart = mid + passNext;
        leftMax[0] = maxBorder[0];
        leftMax[1] = mid;
        leftMax[3] = maxBorder[2];

        rightMin[0] = minBorder[0];
        rightMin[1] = secondStart;
        rightMin[2] = minBorder[2];
    }else if(m_divDimension == 'z') {
        int total = minBorder[2] + maxBorder[2];
        int passNext = (total > 0) ? 1 : -1 ;
        mid = total / 2;
        secondStart = mid + passNext;
        leftMax[0] = maxBorder[0];
        leftMax[1] = maxBorder[1];
        leftMax[3] = mid;

        rightMin[0] = minBorder[0];
        rightMin[1] = minBorder[1];
        rightMin[2] = secondStart;
    }
}

Region::Region(const int minBorder[3], const int maxBorder[3], char parentDivDim, Region* parent) {
    setBorders(minBorder, maxBorder);

    if(isCell()) {
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
            mid = total / 2;
            secondStart = mid + passNext;
            leftMax[0] = mid;
            leftMax[1] = maxBorder[1];
            leftMax[3] = maxBorder[2];

            rightMin[0] = secondStart;
            rightMin[1] = minBorder[1];
            rightMin[2] = minBorder[2];
            m_leftPart = new Region(minBorder,leftMax, m_divDimension, this);
            m_rightPart = new Region(rightMin, maxBorder, m_divDimension, this);
        }else if(m_divDimension == 'y') {
            int total = minBorder[1] + maxBorder[1];
            int passNext = (total > 0) ? 1 : -1 ;
            mid = total / 2;
            secondStart = mid + passNext;
            leftMax[0] = maxBorder[0];
            leftMax[1] = mid;
            leftMax[3] = maxBorder[2];

            rightMin[0] = minBorder[0];
            rightMin[1] = secondStart;
            rightMin[2] = minBorder[2];
            m_leftPart = new Region(minBorder,leftMax, m_divDimension, this);
            m_rightPart = new Region(rightMin, maxBorder, m_divDimension, this);
        }else if(m_divDimension == 'z') {
            int total = minBorder[2] + maxBorder[2];
            int passNext = (total > 0) ? 1 : -1 ;
            mid = total / 2;
            secondStart = mid + passNext;
            leftMax[0] = maxBorder[0];
            leftMax[1] = maxBorder[1];
            leftMax[3] = mid;

            rightMin[0] = minBorder[0];
            rightMin[1] = minBorder[1];
            rightMin[2] = secondStart;
            m_leftPart = new Region(minBorder,leftMax, m_divDimension, this);
            m_rightPart = new Region(rightMin, maxBorder, m_divDimension, this);
        }
    }
}

char Region::rootDivDim() {
    if(m_minBorder[0] != m_maxBorder[0])
        return 'x';
    else if(m_minBorder[1] != m_maxBorder[1])
        return 'y';
    else if(m_minBorder[2] != m_maxBorder[2])
        return 'z';

    return 'x';
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

bool Region::isCell() {
    bool result = true;

    for (int i = 0; i < 3; i++) {
        result = result && (m_minBorder[i] == m_maxBorder[i]);
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


void Region::placePokemon(const Pokemon &givenPokemon, int xPos, int yPos, int zPos) {
     if (isCell()) {
         pokemon = new Pokemon(givenPokemon);
     } else {
        if(placePosition(xPos, yPos, zPos) == 'l'){
            if(m_leftPart){
                m_leftPart->placePokemon(givenPokemon, xPos, yPos, zPos);
            }else {
                m_leftPart = new Region(m_minBorder, leftMax, m_divDimension, this);
                m_leftPart->placePokemon(givenPokemon, xPos, yPos, zPos);
            }
        }else {
            if(m_rightPart){
                m_rightPart->placePokemon(givenPokemon, xPos, yPos, zPos);
            }else {
                m_rightPart = new Region(rightMin, m_maxBorder, m_divDimension, this);
                m_rightPart->placePokemon(givenPokemon, xPos, yPos, zPos);
            }
        }
     }
}

char Region::placePosition(int xPos, int yPos, int zPos) {
    char result = 'l';

    if(m_divDimension == 'x'){
        if(secondStart < 0) {
            if (xPos <= secondStart)
                result = 'r';
            else
                result = 'l';
        }else {
            if (xPos >= secondStart)
                result = 'r';
            else
                result = 'l';
        }
    }else if(m_divDimension == 'y'){
        if(secondStart < 0) {
            if (yPos <= secondStart)
                result = 'r';
            else
                result = 'l';
        }else {
            if (yPos >= secondStart)
                result = 'r';
            else
                result = 'l';
        }
    }else if(m_divDimension == 'z'){
        if(secondStart < 0) {
            if (zPos <= secondStart)
                result = 'r';
            else
                result = 'l';
        }else {
            if (zPos >= secondStart)
                result = 'r';
            else
                result = 'l';
        }
    }

    return result;
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
