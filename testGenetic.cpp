//***********************************************************************************
//*																					*
//*			testGenetic.cpp - Used to test the genetic alg. classes					*
//*																					*
//*						      Version: 25 February 2003								*
//*								by Milan Prucha										*
//*																					*
//***********************************************************************************

#include "genetic.h"

//====================================================================================
//====================================================================================

//TEST PROGRAM - Performs the following:

//	1) Sets up a population of chromosome objects
//  2) Assigns a fitness score to each chromosome depending on how many
//	'1's appear in its gene-string. The fitness score is incremented for 
//		every '1' encountered
//	3) The Mating & Mutation process is applied to the population to create
//		generation
//	4) Go back to 2


//	If this algorithm is run enough times it should produce chromosomes that
//	mostly, if not entirely consist of '1's


int main(int argc, char* argv[])
{
	srand( (unsigned)time( NULL ) ); //seeds the rand() function


	//set up a population with 20 chromosomes of gene-length: 10
	//crossover probability is 80%, mutational probability is 0.5%.
	// ELITISM is active: The algorithm selects the top 2 
	// chromosomes and makes 2 copies of each (therefor, 4 
	// top chromosomes are copied directly into the next 
	// generation).

	Cpopulation myPop(20,10,800,5,2,2);

	int ext; //stores value extracted from gene string

	int size;
	size=myPop.GetSize();

	int length;
	length=myPop.GetChromoLen();

	int fitness=0;

	char exit;

	printf("This simple test creates a population of 20\n");
	printf("chromosomes containing 10 genes(bits) each.\n");
	printf("The more '1's a chromosome contains the 'fitter'\n");
	printf("it is. Therefore, the chromosomes should converge\n");
	printf("towards the perfect solution of '1111111111'.\n\n");
	printf("<PRESS A KEY TO START>\n");

	_getch();


	while(1)
	{
		//----------------------------------------------------------------
		//The code below constitutes the 'FITNESS FUNCTION'
		//go through each chromosome and set a fitness
		for(int c=0; c<size; c++)
		{	
			fitness=0; //reset 'ones' count for current chromosome
			for(int g=0; g<length; g++)
			{
				ext = myPop.ExtractValue(c,g,1);

				if(ext==1)
					fitness++;
			}

		myPop.AssignFitness(c, fitness);
		}//end of forloop - used to determine each chromosome's fitness
		//-----------------------------------------------------------------

		myPop.Select(0); //'Roulette Wheel' selection is used
		myPop.DisplayCurrent();
		_getch();
	
		myPop.DisplayMating();
		_getch();

		myPop.Mate(0);
		myPop.Mutate();
		myPop.NextGeneration();
	

		printf("\nExit GA test?\n");
		exit = _getch();
		exit = tolower(exit);

		if(exit == 'y')
			break;
		

	}//end of while loop

	return 0;
}

//==============================================================
//==============================================================

 