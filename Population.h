#ifndef __POPULATION_H_
#define __POPULATION_H_

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Chromosome.h"

#define ELITE_PERCENT 0.05
#define TOURNAMENT_PROB 0.65

class Population
{
	public:
		Population(unsigned int size, const std::string goal);
		~Population();
		
		unsigned int Generation();
		
		//utils
		unsigned int Sort();
		void Print(unsigned int gen, std::ostream& theStream);
		
	private:
		std::vector<Chromosome> _pop;
		unsigned int _size;
		unsigned int _codeLength;
		std::string _goalCode;
		
		void Initialize();
		
		unsigned int Select();
};

#endif