#ifndef POKEMON_H
#define POKEMON_H

#include <string>

using namespace std;

class Pokemon {
	private:
		std::string m_name;
		std::string m_type;
		int m_exp;
		int m_min;

        void gainExp();
		// Add private members, methods and constructors here as you need
	public:
		// Do NOT make any modifications below
		mutable int t_ref_cnt;	// stores how many trainers have this pokemon
		Pokemon(const string&, const string&, int);
		Pokemon(const Pokemon&);
		~Pokemon();
		const string& getName() const;
		bool operator>>(const Pokemon&);
		friend Pokemon operator&(Pokemon&, Pokemon&);
		Pokemon& operator=(const Pokemon&);
};

#endif
