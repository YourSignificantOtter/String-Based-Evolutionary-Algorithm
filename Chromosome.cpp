#include "Chromosome.h"

Chromosome::Chromosome(std::string code)
{
	_code = code;
	_length = code.length();
	_cost = 0;
}

Chromosome::Chromosome(unsigned int codeLength)
{
	_length = codeLength;
	_cost = 0;
	Randomize();
}

void Chromosome::Randomize()
{
	for(int i = 0; i < _length; i++)
		_code += ASCII_MIN + (rand() % (ASCII_MAX - ASCII_MIN + 1));
}

void Chromosome::Crossover(Chromosome parent1, Chromosome parent2, std::string goalCode)
{
	unsigned int start = rand() % _length + 1;
	unsigned int stop  = rand() % _length + 1;
	
	if(start > stop)
	{
		unsigned int tmp = start;
		start = stop;
		stop = tmp;
	}
	
	std::string crossoverCode = parent1.GetCode();
	std::string temp = parent2.GetCode().substr(start, stop);
	crossoverCode.replace(start, stop, temp);
	SetCode(crossoverCode);	
}

void Chromosome::Mutate(std::string goalCode)
{
	std::string mutatedCode = GetCode();
	std::string oldCode = GetCode();
	
	unsigned int numToChange = rand() % 4;
	unsigned int charToChange;
	for(int i = 0; i < numToChange; i++)
	{
		charToChange = rand() % _length;
		unsigned int mutationChange = rand() % 5;
		if(rand() % 2 == 1)
			mutatedCode[charToChange] += mutationChange;
		else
			mutatedCode[charToChange] -= mutationChange;
		
		if(mutatedCode[charToChange] > ASCII_MAX)
			mutatedCode[charToChange] = ASCII_MAX;
		else if(mutatedCode[charToChange] < ASCII_MIN)
			mutatedCode[charToChange] = ASCII_MIN;
	}
	
	unsigned int cost = GetCost();
	SetCode(mutatedCode);
	CalculateCost(goalCode);
	unsigned int m_cost = GetCost();
	if(m_cost > cost)
		SetCode(oldCode);
}

void Chromosome::CalculateCost(const std::string goalCode)
{
	if(_length != goalCode.length())
	{
		std::cerr << "Goal string and chromosome string must be same length!\n";
	}
	else
	{
		unsigned int cost = 0;
		
		for(int i = 0; i < goalCode.length(); i++)
		{
			cost += ((int)goalCode[i] - (int)_code[i]) * ((int)goalCode[i] - (int)_code[i]);
		}
		_cost = cost;
	}
}

unsigned int Chromosome::GetCost()
{
	return _cost;
}

std::string Chromosome::GetCode()
{
	return _code;
}

void Chromosome::SetCode(std::string toSet)
{
	if(toSet.length() == _length)
	{
		_code = toSet;
		_cost = 0;
	}
	else
		std::cerr << "SetCode Error!: Input string is not correct length!\n";
}

void Chromosome::Print(std::ostream& theStream)
{
	theStream << _code << '\t' << GetCost() << '\n';
}