/*
 * GENETIC ALGORITHM Class Library 
 * -------------------------------
 * by Milan Prucha
 * 
 * Website: www.milanprucha.com
 * GitHub:  github.com/prucha
 */

#ifndef GENETIC_H
#define GENETIC_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

typedef int BOOL;
enum {FALSE, TRUE};




//-------------------------------------------------------------------------------

class Chromosome
{
private:

	//pointer to the gene-string that forms the chromosome
	unsigned char* genes;  //each element of 'genes' holds 8 alleles 
							// (8 bit data type)				

	unsigned int arraySize; //holds the size of the array needed to store
	//the whole gene-string (the number of 8-bit elements in the 'genes' array).

	//stores the current 'fitness score' assigned to the chromosome
	unsigned int fitness;


	//length of the genes string (all chromosomes in a given population should
	//have the same number of genes)
	unsigned int length;

	//**** may include a character string data member that holds a character
	//representation of the genes string for display purposes only ***

public:

	Chromosome(); //default constructor - if this is NOT called via the
	//'population' object, an explicite call to CreateGenes must be executed
	// before the chromosome is usuable (otherwise 'genes' will point to null)

	Chromosome(unsigned int newlength);
	Chromosome(const Chromosome& copyChromosome); //copy constructor
	~Chromosome(); //destructor

	void CreateGenes(unsigned int newlength);//sets up and DMAs the gene array
	//(if default constructor is called this needs to be called explicitly)

	void Randomise(); //re-randomises the genes-string of a chromosome
	//(note: this is done automatically by the constructor when an 'chromosome'
	//object is created).

	// *** may also include a function that sets genes-strings explicitly ***

	unsigned int GetFitness(); //returns 'Fitness Score' of chromosome
	unsigned int GetLength();  //returns 'genes-String Length' of chromosome

	char* GetString();  //NOT YET DEFINED (see below)
	//returns a pointer to a character string
	//which holds the genes values of the current chromosome
	//(could use this in display routines in the main program)

	void AssignFitness(unsigned int newfitness); //Assigns a new 'Fitness
	//Score' to the chromosome (this will depend on the fitness function which
	//will need to be defined in the main program).

	//Mates current chromosome with a selected 'partner' chromosome, which
	//become the 2 'children' chromosomes to be used in the next generation.
	//Crossover probablitity is also passed to the function.
	//Chromosomes must have the same number of genes in order to mate (if
	//'chromosomes' are being initialised via a 'population' object then this
	//is not an issue).
	int Mate(Chromosome* partner, unsigned int method=1, 
	unsigned int crossProb=800, unsigned int swapRate=500);
	//return: 0=ERROR		 1=CROSSOVER		 2=NO CROSSOVER
	//method: 0=Multi-Point Crossover		1=Single-Point		2=Two-Point
	//CrossProb: 800 equates to 80% probability
	//swapRate: (applies to Multi-Point ONLY) 50% probability

	//moves through each genes of a chromosome and decides whether it should be
	// changed (according to the mutational probabililty)
	void Mutate(unsigned int mutaProb=5); //probability of 0.5%

	//all chromosome info in the received chromosome is copied into the
	//current chromosome object
	BOOL Copy(Chromosome* received);
	//return: 0=ERROR		 1=SUCCESSFULL COPY

	// Extracts a value from a defined portion of the genes-string and
	// returns a value which is then, presumably, used as a control parameter
	// (-1 signifies that no value could be returned - ERROR)
	int ExtractValue(unsigned int position=0, unsigned int valsize=4);
	// a maximum 'valsize' of 15 bits is allowed

	//***********************TO BE DEFINED*********************************
  	// This is the reverse of 'ExtractValue', user passes the position in the
	// bitstring where the value is to be placed, the "binary" equivalent is
	// then inserted (0 signifies that value could be inserted - ERROR)

	BOOL InsertValue(unsigned int position=0, unsigned int bitlength=4,
    unsigned int value=15); //the value 15 can be represented in 4 bits
	// a maximum 'value' of 32767 is allowed
	//*********************************************************************

	//----------------------------------------------------------------------
	//following used to test output in DOS ONLY:
	void DisplayGenes(); //Displays chromosome's 'genes Sequence'  (cout << )
	void DisplayFitness(); //Displays current 'Fitness Score'  		(cout << )
};



//----------------------------------------------------------------------------



//'population' objects manipulate entire populations of 'chromosome' objects
class Population
{
private:
   //total number of chromosomes in population (this should remain constant)
   //(must be an even number to facilitate pairing off before mating)
   const unsigned int size;

   //length to be assigned to all chromosomes in a population
   const unsigned int chromolen;


   //'Generation' counter
   unsigned int generation;

   //'Mutational probability' to be used in population's mutation phase
   unsigned int mutaProb;

   //'Cross-over probability'
   unsigned int crossProb;
	
   //the probability of 'bit' swap during MULTI-POINT crossover
   unsigned int swapRate; 


   Chromosome* currentPool; //pointer to first chromosome in current population
   Chromosome* matingPool; //pointer to first chromosome in selected pool

   unsigned int fitness; //Overall Fitness of population
   //(relates to the chromosomes in the 'currentPool')

   float meanFitness; //the average fitness of a chromosome in the population

   unsigned int elitism; //number of 'elite' chromosomes to be transferred 
	//directly into the next generation (no crossover or mutation).
   // 0 = NO ELITISM

   unsigned int eliteCopies; //number of copies to be made of each 'elite' 
							 //chromosome

public:

	Population(); //default constructor

	Population(unsigned int newsize, unsigned int newchromolen=32,
	unsigned int newcrossProb=800, unsigned int newmutaProb=5,
	unsigned int newelitism=0, unsigned int neweliteCopies=1,
	unsigned int newswapRate=500);
	
	//copy constructor
	Population(const Population& copyPopulation);

	~Population(); //destructor

   // *** insert copy constructor? ***

   unsigned int GetSize();//returns the number of chromosomes in the population
   unsigned int GetGeneration(); //returns the generation count
   unsigned int GetChromoLen(); //returns length of chromosomes in population
   unsigned int GetmutaProb(); //returns mutational probability
   unsigned int GetcrossProb(); //returns cross-over probablity
   unsigned int GetFitness(); //returns the sum of all chromosome fitness'
   float GetMeanFitness(); //returns the average fitness of the population


	void Select(unsigned int method, unsigned int sample=1);  
	// 'Roulette Wheel' selection process -
	//the population's total 'fitness' and the 'fitness' of each chromosome
	//(in the current population) needs to have been determined by an external
	// 'fitness function' before this is called.
	// Should eventually support a number of different selection techniques.
	//Currently supports:
	//	0 = Roulette Wheel Selection
	//	1 = Tournament Selection ('sample' param specifies the size of the
	//  'sample pool' in this mode)


   void Mate(unsigned int method=1); // mate all chromosome in selection pool to produce
   // next generation's (children) chromosomes.

   void Mutate(); //run mutation process on each chromosome

   //void AssignPopFitness(); //finds the sum total (and mean) of all chromosome fitnesses
   //in the population (make sure all chromosomes have been assigned a current
   //fitness before you call this). It also assigns 'bestChromo' and 'bestFitness' for
   //the current population.

  	//Assigns a fitness to a particular 'element' in the 'currentPool' array
   //(fitness is determined by an external fitness function)
   void AssignFitness(unsigned int element, unsigned int newfitness);

   int ExtractValue(unsigned int element=0, unsigned int position=0,
   unsigned int valsize=4);

	//insert a value into the gene-string of a chromosome
	int InsertValue(unsigned int element=0, unsigned int position=0,
	unsigned int bitlength=4, unsigned int value=15);

   //??? FindChromoByFitness(???)  //will this return a pointer to a
   //??? FindChromoByLocation(???) //chromosome object

   void NextGeneration(); //creates the next generation of chromosome objects

   //-------------------------------------------------------------------------
   //following used to test output in DOS ONLY:
   void DisplayCurrent();  //Display data on current population
   void DisplayMating(); //Display data on selection pool
};

#endif