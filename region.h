#ifndef REGION_H
#define REGION_H

#include "pokemon.h"
#include <iostream>
#include <exception>

using namespace std;

class Region {
	private:
		// Add private members, methods and constructors here as you need
		int m_minBorder[3];
		int m_maxBorder[3];
		int leftMax[3];
		int rightMin[3];
		int mid;
		int secondStart;
		char m_divDimension;

		Region *m_parent;
		Region *m_rightPart;
		Region *m_leftPart;

		Pokemon *pokemon;

		Region(const int[3], const int[3], char divDim, Region*);
		bool isCell() const;
		void setBorders(const int[3], const int[3]);
		char nextDivDim(char , const int[3], const int[3]);
		char placePosition(int, int, int) const;
		char rootDivDim();
		int m_getPokemonCount() const;
		void goUpAndClean();
		Region const* findRegion(const int[3], const int[3]) const;
	public:
		// Do NOT make any modifications below
		Region(const int[3], const int[3]);
		Region(const Region&);
		~Region();
		int getMinBorder(char) const;
		int getMaxBorder(char) const;
		void placePokemon(const Pokemon&, int, int, int);
		Pokemon& operator()(int, int, int);
		int getPokemonCount(const int[3], const int[3]) const;
		Region crop(const int[3], const int[3]) const;
		void patch(Region);
		Region& operator=(const Region&);
};

class pokemonException: public exception {
 	virtual const char* what() const throw() {
    		return "There does not exist any pokemon in the given coordinates!";
	}
};

#endif
