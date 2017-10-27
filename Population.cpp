#include "Population.h"

Population::Population(unsigned int size, const std::string goal)
{
	_size = size;
	_codeLength = goal.length();
	_goalCode = goal;
	Initialize();
}

Population::~Population()
{

}

void Population::Initialize()
{
	for(int i = 0; i < _size; i++)
		_pop.push_back(Chromosome(_codeLength));
	
}

unsigned int Population::Generation()
{
	for(std::vector<Chromosome>::size_type i = 0; i != _pop.size(); i++)
		_pop[i].CalculateCost(_goalCode);
	
	Chromosome parent1 = _pop[Select()];
	Chromosome parent2 = _pop[Select()];
	
	unsigned int mutatedChromosome = rand() % _size;
	
	_pop[_size-1].Crossover(parent1, parent2, _goalCode);
	_pop[mutatedChromosome].Mutate(_goalCode);
	_pop[_size-1].CalculateCost(_goalCode);
	if(mutatedChromosome != _size - 1)
		_pop[mutatedChromosome].CalculateCost(_goalCode);
	
	unsigned int best = Sort();
	
	return best;
}

unsigned int Population::Select()
{
	float num = (rand() % 101)/100.0 * (rand() % 101)/100.0;
	return std::min((unsigned int)(num * _size), _size - 1);
}



void Population::Print(unsigned int gen, std::ostream& theStream)
{
	theStream << "Generation\tCode\tCost\n";
	for(std::vector<Chromosome>::size_type i = 0; i != _pop.size(); i++)
	{
		theStream << gen << '\t';
		_pop[i].Print(theStream);
	}
	theStream << '\n';
}

unsigned int Population::Sort()
{
	static Chromosome _BestCost = _pop[0];
	std::sort(_pop.begin(), _pop.end());
	
	if(_pop[0].GetCost() < _BestCost.GetCost())
		_BestCost = _pop[0];
	
	return _BestCost.GetCost();
}