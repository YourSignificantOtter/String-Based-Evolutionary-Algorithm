#ifndef __CHROMOSOME_H
#define __CHROMOSOME_H

#include <string>
#include <cstdlib>
#include <math.h>
#include <iostream>

#define ASCII_MIN 32
#define ASCII_MAX 122

class Chromosome{	
	public:
		Chromosome(std::string code);
		Chromosome(unsigned int codeLength);
		
		void Crossover(Chromosome parent1, Chromosome parent2, std::string goalCode);
		void Mutate(std::string goalCode);
		void CalculateCost(const std::string goalCode);
		
		void Print(std::ostream& theStream);
		
		unsigned int GetCost();
		std::string GetCode();
		void SetCode(std::string toSet);
		
		bool operator < (Chromosome &rhs) const {return _cost < rhs.GetCost(); }
		
	private:
		unsigned int _cost;
		std::string _code;
		unsigned int _length;
		
		void Randomize();
};

#endif