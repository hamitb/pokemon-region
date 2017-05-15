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

    constructSub(minBorder, maxBorder);

}

Region::Region(const int minBorder[3], const int maxBorder[3], char parentDivDim, Region* parent) {
    setBorders(minBorder, maxBorder);

    if(isCell()) {
        m_parent = parent;
        m_divDimension = 'x';
    } else {
        m_parent = parent;
        m_divDimension = nextDivDim(parentDivDim, minBorder, maxBorder);

        constructSub(minBorder, maxBorder);
    }
}

void Region::constructSub(const int minBorder[3], const int maxBorder[3]){
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
    pokemon = other.pokemon;
    mid = other.mid;
    secondStart = other.secondStart;
    m_divDimension = other.m_divDimension;

    for(int i = 0; i < 3; i++) {
        leftMax[i] = other.leftMax[i];
        rightMin[i] = other.rightMin[i];
    }

    if(other.m_rightPart)
        m_rightPart = new Region(*other.m_rightPart);
    else
        m_rightPart = NULL;

    if(other.m_leftPart)
        m_leftPart = new Region(*other.m_leftPart);
    else
        m_leftPart = NULL;
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

    if(m_parent)
        m_parent->goUpAndClean();
}

Pokemon &Region::operator()(int xPos, int yPos, int zPos) {
    if (isCell()) {
        if(!pokemon){
            throw pokemonException();
        }
        Pokemon* result = pokemon;

        pokemon = NULL;

        goUpAndClean();


        return *result;
    }

    if (placePosition(xPos, yPos, zPos) == 'l') {
        if(m_leftPart)
            return m_leftPart->operator()(xPos, yPos, zPos);
        else
            throw pokemonException();
    } else {
        if(m_rightPart)
            return m_rightPart->operator()(xPos, yPos, zPos);
        else
            throw pokemonException();
    }
}

int Region::getPokemonCount(const int givenMin[3], const int givenMax[3]) const {
    bool result = true;
    for (int i = 0; i < 3; i++) {
        result = result && (m_minBorder[i] == givenMin[i]) && (m_maxBorder[i] == givenMax[i]);
    }

    if(result){
        return m_getPokemonCount();
    }

    if(placePosition(givenMin[0], givenMin[1], givenMin[2]) == 'l') {
        if(m_leftPart)
            return m_leftPart->getPokemonCount(givenMin, givenMax);
        else{
            return 0;
        }

    } else {
        if(m_rightPart)
            return m_rightPart->getPokemonCount(givenMin, givenMax);
        else{
            return 0;
        }
    }
}

int Region::m_getPokemonCount() const {
    if(isCell() && pokemon){
        return 1;
    }
    else if(isCell())
        return 0;
    else if(m_leftPart && m_rightPart)
        return m_leftPart->m_getPokemonCount() + m_rightPart->m_getPokemonCount();
    else if(m_leftPart)
        return m_leftPart->m_getPokemonCount();
    else if(m_rightPart)
        return m_rightPart->m_getPokemonCount();

    return 0;
}

Region Region::crop(const int givenMin [3], const int givenMax [3]) const {
    bool result = true;
    for (int i = 0; i < 3; i++) {
        result = result && (m_minBorder[i] == givenMin[i]) && (m_maxBorder[i] == givenMax[i]);
    }

    if(result){
        return *this;
    }

    if(placePosition(givenMin[0], givenMin[1], givenMin[2]) == 'l') {
        if(m_leftPart)
            return m_leftPart->crop(givenMin, givenMax);

    } else {
        if(m_rightPart)
            return m_rightPart->crop(givenMin, givenMax);

    }
}

char Region::findPatchPos (const int givenMin[3], const int givenMax[3]) const {
    int totalArr[3];
    int _leftMaxX[3];
    int _rightMinX[3];
    int _leftMaxY[3];
    int _rightMinY[3];
    int _leftMaxZ[3];
    int _rightMinZ[3];
    bool checkX = true;
    bool checkY = true;
    bool checkZ = true;

    for(int i = 0; i < 3; i++)
        totalArr[i] = (m_minBorder[i] + m_maxBorder[i]);

    int _midX = totalArr[0] / 2;
    int _passNextX = (totalArr[0] > 0) ? 1 : -1;
    int _secondStartX = _midX + _passNextX;

    int _midY = totalArr[1] / 2;
    int _passNextY = (totalArr[1] > 0) ? 1 : -1;
    int _secondStartY = _midY + _passNextY;

    int _midZ = totalArr[2] / 2;
    int _passNextZ = (totalArr[2] > 0) ? 1 : -1;
    int _secondStartZ = _midZ + _passNextZ;

    _leftMaxX[0] = _midX;
    _leftMaxX[1] = m_maxBorder[1];
    _leftMaxX[2] = m_maxBorder[2];

    _rightMinX[0] = _secondStartX;
    _rightMinX[1] = m_minBorder[1];
    _rightMinX[2] = m_minBorder[2];

    _leftMaxY[1] = _midY;
    _leftMaxY[0] = m_maxBorder[0];
    _leftMaxY[2] = m_maxBorder[2];

    _rightMinY[1] = _secondStartY;
    _rightMinY[0] = m_minBorder[0];
    _rightMinY[2] = m_minBorder[2];

    _leftMaxZ[2] = _midZ;
    _leftMaxZ[0] = m_maxBorder[0];
    _leftMaxZ[1] = m_maxBorder[1];

    _rightMinZ[2] = _secondStartZ;
    _rightMinZ[0] = m_minBorder[0];
    _rightMinZ[1] = m_minBorder[1];


    for(int i = 0; i < 3; i++){
        checkX = checkX && (m_minBorder[i] == givenMin[i]) && (_leftMaxX[i] == givenMax[i]);
        checkY = checkY && (m_minBorder[i] == givenMin[i]) && (_leftMaxY[i] == givenMax[i]);
        checkZ = checkZ && (m_minBorder[i] == givenMin[i]) && (_leftMaxZ[i] == givenMax[i]);
    }

    if(checkX || checkY || checkZ)
        return 'l';

    checkX = checkY = checkZ = true;

    for(int i = 0; i < 3; i++){
        checkX = checkX && (_rightMinX[i] == givenMin[i]) && (m_maxBorder[i] == givenMax[i]);
        checkY = checkY && (_rightMinY[i] == givenMin[i]) && (m_maxBorder[i] == givenMax[i]);
        checkZ = checkZ && (_rightMinZ[i] == givenMin[i]) && (m_maxBorder[i] == givenMax[i]);
    }

    if(checkX || checkY || checkZ)
        return 'r';

    return 'n';
}

void Region::patch(Region other) {
    bool result = true;
    for (int i = 0; i < 3; i++) {
        result = result && (m_minBorder[i] == other.m_minBorder[i]) && (m_maxBorder[i] == other.m_maxBorder[i]);
    }

    if(result){
        copyHelper(other);
    }

    int otherMinX = other.m_minBorder[0];
    int otherMinY = other.m_minBorder[1];
    int otherMinZ = other.m_minBorder[2];

    char pos = placePosition(otherMinX, otherMinY, otherMinZ);
    char directPut = findPatchPos(other.m_minBorder, other.m_maxBorder);

    if(directPut == 'l'){
        m_leftPart->copyHelper(other);
    }
    else if(directPut == 'r'){
        m_rightPart->copyHelper(other);
    } else{
        if(pos == 'l') {
            if (!m_leftPart)
                m_leftPart = new Region(m_minBorder, leftMax, m_divDimension, this);

            m_leftPart->patch(other);
        } else {
            if (!m_rightPart)
                m_rightPart = new Region(rightMin, m_maxBorder, m_divDimension, this);

            m_rightPart->patch(other);
        }
    }
}

Region &Region::operator=(const Region &other) {
    copyHelper(other);

    return *this;
}

void Region::copyHelper(const Region &other) {
    setBorders(other.m_minBorder, other.m_maxBorder);

    m_parent = other.m_parent;
    pokemon = other.pokemon;
    mid = other.mid;
    secondStart = other.secondStart;
    m_divDimension = other.m_divDimension;

    for(int i = 0; i < 3; i++) {
        leftMax[i] = other.leftMax[i];
        rightMin[i] = other.rightMin[i];
    }

    if(other.m_rightPart)
        m_rightPart = new Region(*other.m_rightPart);
    else
        m_rightPart = NULL;

    if(other.m_leftPart)
        m_leftPart = new Region(*other.m_leftPart);
    else
        m_leftPart = NULL;
}
