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
    m_parent = NULL;
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
        leftMax[2] = maxBorder[2];

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
        leftMax[2] = maxBorder[2];

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
        leftMax[2] = mid;

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
            leftMax[2] = maxBorder[2];

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
            leftMax[2] = maxBorder[2];

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
            leftMax[2] = mid;

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

bool Region::isCell() const{
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

char Region::placePosition(int xPos, int yPos, int zPos) const {
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

void Region::goUpAndClean() {
    if(m_parent && m_getPokemonCount() == 0){
        if(m_parent->m_leftPart == this)
            m_parent->m_leftPart = NULL;
        else if(m_parent->m_rightPart == this)
            m_parent->m_rightPart = NULL;
    }
}

Pokemon &Region::operator()(int xPos, int yPos, int zPos) {
    if (isCell()) {
        //TODO go up get pokemon count and delete node if count is 1

        if(!pokemon){
            //TODO return exception if no pokemon found
        }

        Pokemon result = *pokemon;

        pokemon = NULL;


        goUpAndClean();


        return result;
    }

    if (placePosition(xPos, yPos, zPos) == 'l') {
        return m_leftPart->operator()(xPos, yPos, zPos);
    } else {
        return m_rightPart->operator()(xPos, yPos, zPos);
    }
}

int Region::getPokemonCount(const int givenMin[3], const int givenMax[3]) const {

    Region const *founded = findRegion(givenMin, givenMax);

    founded->m_getPokemonCount();

}

int Region::m_getPokemonCount() const {
    if(isCell() && pokemon)
        return 1;
    else if(isCell())
        return 0;
    else if(m_leftPart && m_rightPart)
        return m_leftPart->m_getPokemonCount() + m_rightPart->m_getPokemonCount();
    else if(m_leftPart)
        return m_leftPart->m_getPokemonCount();
    else if(m_rightPart)
        return m_rightPart->m_getPokemonCount();
}

 Region const * Region::findRegion(const int givenMin [3], const int givenMax [3]) const {
    bool result = true;
    for (int i = 0; i < 3; i++) {
        result = result && (m_minBorder[i] == givenMin[i]) && (m_maxBorder[i] == givenMax[i]);
    }

    if(result)
        return this;

    if(placePosition(givenMin[0], givenMin[1], givenMin[2]) == 'l') {
        return m_leftPart->findRegion(givenMin, givenMax);
    } else {
        return m_rightPart->findRegion(givenMin, givenMax);
    }
}


/*

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
*/