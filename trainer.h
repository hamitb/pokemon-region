#ifndef TRAINER_H
#define TRAINER_H

#include "pokemon.h"
#include "region.h"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Trainer {
	private:
	std::vector<const Pokemon*>pokemons;
		// Add private members, methods and constructors here as you need
	public:
		// Do NOT make any modifications below
		Trainer(const string&, const Pokemon&, const int[3], const int[3]);
		Trainer(const Trainer&);
		~Trainer();
		void catchPokemon(const Pokemon& newPokemon) {
			newPokemon.t_ref_cnt++;
			pokemons.push_back(&newPokemon);
		};
		void scanRegion(Region&);
		friend ostream& showPokemons(ostream&, const Trainer&);
};

#endif
