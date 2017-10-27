#include <iostream>
#include <fstream>
#include <time.h>
#include "Chromosome.h"
#include "Population.h"

#define POP_SIZE 25
#define NUM_GENERATIONS 6000

void printHelp();

enum flags{
	goal_flag,
	gen_flag,
	pop_flag,
	out_flag,
	help_flag,
	no_flag,
	all_flags
};

int main(int argc, char *argv[])
{
	std::string goalString;
	std::string outFileName;
	bool fileIO = false;
	unsigned int populationSize;
	unsigned int maxGenerations;
	
	goalString = "Hello World!";
	populationSize = POP_SIZE;
	maxGenerations = NUM_GENERATIONS;
		
	if(argc >= 2)
	{
		flags myFlag = no_flag;
		for(int i = 1; i < argc; i++)
		{
			std::string argvString = argv[i];
			if(myFlag == no_flag)
			{
				if(argvString.compare("-g") == 0 || argvString.compare("-G") == 0)
					myFlag = goal_flag;
				else if(argvString.compare("-p") == 0 || argvString.compare("-P") == 0)
					myFlag = pop_flag;
				else if(argvString.compare("-n") == 0 || argvString.compare("-N") == 0)
					myFlag = gen_flag;
				else if(argvString.compare("-o") == 0 || argvString.compare("-O") == 0)
					myFlag = out_flag;
				else if(argvString.compare("-h") == 0 || argvString.compare("-H") == 0)
				{
					myFlag = help_flag;
					printHelp();
					exit(1);
				}
				
			}
			else
			{
				if(myFlag == goal_flag)
					goalString = argvString;
				else if(myFlag == gen_flag)
					maxGenerations = std::stoi(argvString);
				else if(myFlag == pop_flag)
					populationSize = std::stoi(argvString);
				else if(myFlag == out_flag)
				{
					outFileName = argvString;
					fileIO = true;
				}
				else if(myFlag == help_flag)
					;	
				else
					std::cerr << "Unknown flag <" << argv[i - 1] << " passed!\n";
				
				myFlag = no_flag;
			}
		}
	}
	
	std::streambuf *buff;
	std::ofstream myOutputFile;
	
	if(fileIO == true)
	{
		myOutputFile.open(outFileName);
		buff = myOutputFile.rdbuf();
	}
	else
		buff = std::cout.rdbuf();
	
	std::ostream myStream(buff);
	
	srand(time(NULL));
	
	Population myPop(POP_SIZE, goalString);
	
	unsigned int best = 9999;
	unsigned int numGen = 0;
	
	while(best && numGen <= maxGenerations - 1)
	{
		best = myPop.Generation();
		if(fileIO == true)
			if(numGen % (unsigned int)(maxGenerations * .10) == 0)
				myPop.Print(numGen, myStream);
		numGen++;
	}
	
	myPop.Print(numGen, myStream);
	
	if(fileIO == true)
	{
		myOutputFile.close();
	}
	
	return 1;
}


void printHelp()
{
	std::cout << "String based genetic algorithm.\nInput flags are:\n";
	std::cout << "-g/-G\tEnter goal string, no spaces, ascii characters only\n";
	std::cout << "-p/-P\tEnter population size, positive numbers only\n";
	std::cout << "-n/-N\tEnter maximum generation number, positive numbers only\n";
	std::cout << "-o/-O\tEnter output file name, if not entered data is output to terminal\n";
	std::cout << "-h/-H\tPrint this help dialog\n\n";
}


