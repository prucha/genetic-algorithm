/*
 * GENETIC ALGORITHM Class Library 
 * -------------------------------
 * by Milan Prucha
 * 
 * Website: www.milanprucha.com
 * GitHub:  github.com/prucha
 */

#include "genetic.h"

//this array is used to determine the values of specific bits
//within an 8-bit data type (using uniary &).
unsigned char bitAt[8] =
{
	0x80,	//element [0] => Highest bitorder	( 1000 0000 )
	0x40,	//									( 0100 0000 )
	0x20,	//									( 0010 0000 )
	0x10,	//									( 0001 0000 )
	0x08,	//									( 0000 1000 )
	0x04,	//									( 0000 0100 )
	0x02,	//									( 0000 0010 )
	0x01	//element [7] => Lowest bitorder	( 0000 0001 )
};



//default constructor - no parameters supplied
Cchromosome::Cchromosome() : fitness(0), length(32), arraySize(4)
{
	//allocate memory for new chromosome and attach pointer
	genes=NULL; //'CreateGenes' needs to be called before this is used
}//end of default constructor


//============================================================================


//custom constructor
Cchromosome::Cchromosome(unsigned int newlength) : fitness(0)
{
	if(newlength<4)   //chromosomes shorter than 4 genes are probably
   newlength=4;   //too short (make them at least 4 genes in length)!

   genes=NULL; //flags genes pointer as not being attached to an array yet
   length=newlength; //set the 'length' data member


   //CREATE THE GENES:
   unsigned int temp;  //temporarily holds new value of an allele
   unsigned int arrayElement = 0; //tracks which element is currently being assigned
   unsigned int bitPos = 0;  //tracks which bit of an 8-bit gene 'element' is currently 
							//being assigned 

   //calculate the array size of 'genes' needed to hold the entire chromosome
	arraySize = newlength / 8; 

	//in the event that newlength does not divide by 8 perfectly, then an 
	//addition element needs to be included to hold the remaining alleles
	if(arraySize%8) //if modulus returns a remainder (TRUE)
		arraySize++;

	//dynamically allocate mem space for genes array
	genes = new unsigned char[arraySize];
	genes[0] = 0x00; //make sure next 'element' is zeroed out


	//Assign a random allele at each locus of the chromosome
	for(unsigned int locus=0; locus<length; locus++)
	{	
		//check whether all 8-bits of the current element have been
		//set and if so move onto the next element
		if(bitPos > 7)
		{
			bitPos = 0;
			arrayElement++;

			//make sure next 'element' is zeroed out
			genes[arrayElement] = 0x00; 
		}
		
		//generate a allele value at random (0 or 1)
		temp = rand()%2;

		if(temp == 1)
		{
			//This should update the value at 'gene[arrayElement]'
			//so that the correct bit is set to '1'
			genes[arrayElement] = genes[arrayElement] | bitAt[bitPos];
		}
		

		bitPos++;
	}//end of for

}//end of custom constructer


//============================================================================
//Copy Constructor: called when a chromosome object is passed 'by value'
//A default copy constructor will not assign new target memory to the 'genes'
//pointer, therefore, it must be assigned manually.

Cchromosome::Cchromosome(const Cchromosome& copyChromosome) :
fitness(copyChromosome.fitness), length(copyChromosome.length),
arraySize(copyChromosome.arraySize)
{
	genes = new unsigned char[length]; //dynamically allocate memory space for 
	//'genes' array (genes is the pointer to this memory)

   //now transfer the values in the genes string to the new memory space
   //(accessed by the 'genes' pointer)
   for(unsigned int locus=0; locus<arraySize; locus++)
   {
   		genes[locus] = copyChromosome.genes[locus];
	   //*(genes+locus) = *(copyChromosome.genes+locus);
   }

   printf("\nCopy Constructor Called\n");
}

//============================================================================

//Destructor
Cchromosome::~Cchromosome()
{
	if(genes!=NULL)
	{
		delete [] genes;  //deletes dynamically allocated array to which 'genes' is
   							//a pointer
	}
}

//============================================================================
//============================================================================

void Cchromosome::CreateGenes(unsigned int newlength=32)
{
	

	if(genes==NULL)
	{

			if(newlength<4)   //chromosomes shorter than 4 genes are probably
				newlength=4;   //too short (make them at least 4 genes in length)!

			length=newlength;

			//calculate the array size of 'genes' needed to hold the entire chromosome
			arraySize = newlength / 8; 

			//in the event that newlength does not divide by 8 perfectly, then an 
			//addition element needs to be included to hold the remaining alleles
			if(arraySize%8) //if modulus returns a remainder (TRUE)
				arraySize++;
				
			//CREATE THE GENES:
			unsigned int temp; //temporarily holds new value of an allele
			unsigned int arrayElement = 0; //tracks which element is currently being assigned
			unsigned int bitPos = 0; //tracks which bit of an 8-bit gene 'element' is currently 
							//being assigned

			//dynamically allocate mem space for genes array
			genes = new unsigned char[arraySize];
			genes[0] = 0x00; //make sure next 'element' is zeroed out

			//Assign a random allele at each locus of the chromosome
			for(unsigned int locus=0; locus<length; locus++)
			{	
				//check whether all 8-bits of the current element have been
				//set and if so move onto the next element
				if(bitPos > 7)
				{
					bitPos = 0;
					arrayElement++;

					//make sure next 'element' is zeroed out
					genes[arrayElement] = 0x00; 
				}

				//generate a allele value at random (0 or 1)
				temp = rand()%2;
	

				if(temp == 1)
				{
					//This should update the value at 'gene[arrayElement]'
					//so that the correct bit is set to '1'
					genes[arrayElement] = genes[arrayElement] | bitAt[bitPos];
				}

				bitPos++;
			}//end of for
		
	}//end of if


}//end of Create Genes




//============================================================================
//============================================================================

void Cchromosome::Randomise()
{
	unsigned int temp; //temporarily holds the new value of the allele
	unsigned int arrayElement = 0; //tracks which element is currently being assigned
	unsigned int bitPos = 0;	//tracks which bit of an 8-bit gene 'element' 
								// is currently being assigned

	//Seed the random-number generator with current time so that 
	//the numbers will be different every time we run
	srand( (unsigned)time( NULL ) );

	if(genes==NULL)
   	return;
	
	//zero out the values in the first element
	genes[0] = 0x00;

	//Assign a ramdom allele at each locus of the chromosome
   for(unsigned int locus=0; locus<length; locus++)
   {
		//check whether all 8-bits of the current element have been 
		//set and if so move onto the next element
	   if(bitPos > 7)
	   {
			bitPos = 0;
			arrayElement++;

			//make sure the next 'element' is zeroed out
			//before assigning new values to it
			genes[arrayElement] = 0x00;
	   }

	   //generate an allele value at random (0 or 1)
	   temp = rand()%2;


	   if(temp == 1)
	   {
			//This should update the value at 'gene[arrayElement]'
			//so that the correct bit is set to '1'
		   genes[arrayElement] = genes[arrayElement] | bitAt[bitPos];
	   }
		
		bitPos++;
   } //end of for




}// end of 'Randomise'

//============================================================================

unsigned int Cchromosome::GetFitness()
{
	return fitness;
}

//=============================================================================

void Cchromosome::AssignFitness(unsigned int newfitness)
{
	fitness=newfitness;
}

//=============================================================================

int Cchromosome::Mate(Cchromosome* partner, unsigned int method,
unsigned int crossProb, unsigned int swapRate)
{
	//defensive programming - check that both current and recieved chromosomes
	//are the same length. If they are not then return false (so long as a
	//'population' object has been used to initialise a chromosome array
	//everything should be fine).
	if(this->genes==NULL || partner->genes==NULL)
		return 0; //i.e. cannot mate (genes not pointing to an array)

	if(this->length != partner->length)
		return 0;   //i.e. cannot mate chromosomes (lengths are different)

	if(method > 2)
		method=2;

	//-----------------------------------------------------------------------------

	unsigned int r=rand()%1000;  //a crossProb value of 10 would equate to 1 percent
	r++;

	if(r<=crossProb)
	{//CROSS OVER PROCEEDURE
		
		// Local vars-----------------------------------------------------------------
		unsigned int arrayElement = 0; //tracks which element is currently being assigned
		unsigned int bitPos = 0;	//tracks which bit of an 8-bit gene 'element' is currently
									//being assigned
		unsigned int lastBit=0; //the last bit to be included in the splice

	   	unsigned int locus; //current position in genes string
		unsigned int spliceF=0; //First 'bit' of slice 
		unsigned int spliceL=0; //Last 'bit' of slice 
	   	unsigned int range = (length-1);  //valid range of random number. Then used to store the
		//index of the gene element(char) in which spliceL occurs.
		//(Two-Point Crossover only)
		
		unsigned char* tmpgenes;   //pointer to temporary genes-string (used to
      	//achieve crossover).

		tmpgenes=new unsigned char[arraySize]; //MUST DELETE BEFORE FUNCTION RETURNS
	  
		//--------------------------------------------------------------------------------
		
		//Multi-Point Crossover does not use splice points
		if(method != 0)
		{
		//--------------------------------------------------------------------------------
		// SINGLE-POINT AND TWO-POINT CROSSOVER
		//--------------------------------------------------------------------------------

			spliceF=rand()%range;
			spliceF++;

			//If the splice point is the last element then
			//we only need to use the Single-Point Crossover method
			if(spliceF == range)
				method = 1;

			if(method == 2)
			{
				spliceL=rand()%range;
				spliceL++;

				if(spliceL == range)
				{
					//again, if spliceL is the last element then
					//single point crossover will suffice
					method = 1;
				}
				else
				{
					if(spliceF==spliceL)
					{
						spliceL++;
					}
					else
					if(spliceF>spliceL)
					{
						//swap the points
						range = spliceF;
						spliceF = spliceL;
						spliceL = range;
					}
					range = spliceL/8;
				}

			}

			

			//-------------------------------------------------------
			printf("\nSPLICE STARTS ON ELEMENT: %d",spliceF);
			if(method==2)
			{
					printf("\nSPLICE ENDS ON ELEMENT: %d",spliceL);
			}


			//Take the genes of the first parent (this->genes) and store them in the
			//temporary genes array
			for(locus=0; locus<arraySize; locus++)
			{
				tmpgenes[locus] = this->genes[locus];
			}


			//-----------------------------------------------------------------------------------
			//set 'arrayElement' and 'bitPos' to correspond to the FIRST splice point 
			arrayElement = spliceF / 8;	
			bitPos = spliceF % 8;

			if(method==1)
			{
				range = arraySize;
			}

			//------------------------------------------------------------------------------------
			// 1 & 2 POINT CROSSOVER
			//------------------------------------------------------------------------------------
			//copy SECOND PARENTS genes AFTER THE SPLICE POINT (rightside)
			//into the first parents

			//FIRST PARENT: We need to analyse the 'arrayElement' containing 
			//the splice point and zero out all the element's bits from the splice 
			//point onwards. We can then copy in the relevant genes (from the splice point)
			//from the SECOND PARENT.
		
			while(bitPos < 8)
			{	
				//use XOR (^) operator to zero out any 1's from the splice point onwards.
				if(this->genes[arrayElement] & bitAt[bitPos])
				{
					this->genes[arrayElement] = this->genes[arrayElement] ^ bitAt[bitPos];
				}

				//now read the value of the SECOND PARENT (using uniary &) at the same position
				//If the SECOND PARENT's gene is a 1 then set the FIRST PARENT's gene to 1 also
				//(in essence, we are copying genes from the SECOND PARENT TO THE FIRST
				if(partner->genes[arrayElement] & bitAt[bitPos])
				{
					this->genes[arrayElement] = this->genes[arrayElement] | bitAt[bitPos];	
				}
			
				bitPos ++;
			}

			//We can now copy the remaining elements from the SECOND PARENT to the FIRST
		
			arrayElement++;
			
			for(locus=arrayElement; locus<range; locus++)
			{
				this->genes[arrayElement] = partner->genes[arrayElement];
			}
			
			//-------------------------------------------------------------------------------
			// TWO-POINT CROSSOVER ONLY
			//-------------------------------------------------------------------------------
			if(method==2)
			{
				arrayElement = spliceL / 8;
				bitPos =0;

				if(arrayElement==(spliceF / 8))
					bitPos = spliceF % 8; 						

				lastBit = spliceL % 8;


				//copy SECOND PARENT genes from element 0 up to and including the last splice
				//element (spliceL)
				while(bitPos <= lastBit)
				{
						//use XOR (^) operator to zero out any 1's up to and including 
						//the end splice point .
						if(this->genes[arrayElement] & bitAt[bitPos])
						{
							this->genes[arrayElement] = this->genes[arrayElement] ^ bitAt[bitPos];
						}

						//now read the value of the SECOND PARENT (using uniary &) at the same position
						//If the SECOND PARENT's gene is a 1 then set the FIRST PARENT's gene to 1 also
						//(in essence, we are copying genes from the SECOND PARENT TO THE FIRST
						if(partner->genes[arrayElement] & bitAt[bitPos])
						{
							this->genes[arrayElement] = this->genes[arrayElement] | bitAt[bitPos];	
						}
			
						bitPos ++;
				}

			}//end 'if(method==2)'
			


			//------------------------------------------------------------------------------------
			//COPY GENES HELD IN TEMPORARY ARRAY INTO THE SECOND PARENT

			arrayElement=spliceF / 8;
			bitPos=spliceF%8;


			while(bitPos < 8)
			{	
				//use XOR (^) operator to zero out any 1's from the splice point onwards.
				if(partner->genes[arrayElement] & bitAt[bitPos])
				{
					partner->genes[arrayElement] = partner->genes[arrayElement] ^ bitAt[bitPos];
				}

				//now read the value of the TEMP GENES (using uniary &) at the same position
				//If the TEMP GENES's allele is a 1 then set the FIRST PARENT's gene to 1 also
				//(in essence, we are copying genes from the TEMP GENES to the SECOND PARENT
				//(PARTNER)

				if(tmpgenes[arrayElement] & bitAt[bitPos])
				{
					partner->genes[arrayElement] = partner->genes[arrayElement] | bitAt[bitPos];	
				}
			
				bitPos ++;
			}

			//We can now copy the remaining elements from the TEMP GENES to the SECOND PARENT
			arrayElement++;

			for(locus=arrayElement; locus<range; locus++)
			{
				partner->genes[arrayElement] = tmpgenes[arrayElement];
			}

			if(method==2)
			{
				arrayElement = spliceL / 8;
				bitPos =0;

				if(arrayElement==(spliceF / 8))
					bitPos = spliceF % 8; 

				lastBit = spliceL % 8;
					
				while(bitPos <= lastBit)
				{
					//use XOR (^) operator to zero out any 1's up to and including 
					//the end splice point .
					if(partner->genes[arrayElement] & bitAt[bitPos])
					{
						partner->genes[arrayElement] = partner->genes[arrayElement] ^ bitAt[bitPos];
					}

					//now read the value of the TEMP GENES (using uniary &) at the same position
					//If the TEMP GENES's allele is a 1 then set the FIRST PARENT's gene to 1 also
					//(in essence, we are copying genes from the TEMP GENES to the SECOND PARENT	
					//(PARTNER)
					if(tmpgenes[arrayElement] & bitAt[bitPos])
					{
						partner->genes[arrayElement] = partner->genes[arrayElement] | bitAt[bitPos];	
					}

					bitPos ++;
				}
			}
			
		
		}//end of: if(method != 0)
		else
		{
		//====================================================================================
		//  MULTI-POINT CROSSOVER
		//====================================================================================

			r=0;
			arrayElement=0;
			bitPos=0;
			unsigned int thisGene=0;
			unsigned int partnerGene=0;

			

			for(unsigned int locus=0; locus<length; locus++)
			{
				//check whether all 8-bits of the current element have been
				//considered and if so move onto the next element
				if(bitPos > 7)
				{
					bitPos = 0;
					arrayElement++;
				}

   				r=rand()%1000;
				r++;

				if(r<=swapRate)//then crossover occurs at the current 'bit'
				{	
					printf("\nGENE SWAPPED AT ELEMENT: %d", locus);					
			
					thisGene=this->genes[arrayElement] & bitAt[bitPos];
					if(thisGene>0)
						thisGene=1;
			
					printf("\nTHIS gene: %d",thisGene);


					partnerGene=partner->genes[arrayElement] & bitAt[bitPos];
					if(partnerGene>0)
						partnerGene=1;

					printf("\nPARTNER gene: %d",partnerGene);

					//compare the bits in each chromosome:
					//If they are NOT equal then flip the 'bits' of
					// both parents
					if(thisGene != partnerGene)
					{	

						printf("  THIS GENE VALUE: %d",thisGene);
						if(thisGene == 1)
						{//turn the '1' to a '0' (using XOR)
						  // on 'this' chromosome
						  this->genes[arrayElement] = this->genes[arrayElement] ^ bitAt[bitPos];

							//printf("\nTHIS Was 1 change to zero");

						  //do the reverse on 'partner'
						  partner->genes[arrayElement] = partner->genes[arrayElement] | bitAt[bitPos];
						}
						else
						{//turn the '0' to a '1' (using OR)
						  //on 'this' chromosome
							partner->genes[arrayElement] = partner->genes[arrayElement] ^ bitAt[bitPos];

							//do the reverse on 'partner'
							this->genes[arrayElement] = this->genes[arrayElement] | bitAt[bitPos];
						}
					}

     
				}//end of 'if(r <= swapRate)'

				bitPos++;
			} //end for

		}

		//IMPORTANT: DE-ALLOCATE (delete) TEMPORARY genes-STRING
		delete [] tmpgenes;

		return 1; //'Crossover' was performed

   }//end of crossover section (if Statement)
	



return 2; //Chromosomes were compatible but no Crossover took place
} //end of 'chromosome::mate' 

//=============================================================================

void Cchromosome::Mutate(unsigned int mutaProb)
{

	if(genes==NULL)
   	return;


	//Go through each genes in turn and decided whether it is to be mutated
	//(flipped). The probability of this should be very low.
	unsigned int r; //random number
	unsigned int arrayElement = 0; //tracks which element is currently being considered
	unsigned int bitPos = 0;  //tracks which bit of an 8-bit gene 'element' is currently 
							//being considered

	for(unsigned int locus=0; locus<length; locus++)
	{
		//check whether all 8-bits of the current element have been
		//considered and if so move onto the next element
		if(bitPos > 7)
		{
			bitPos = 0;
			arrayElement++;
		}

   		r=rand()%1000;
	    r++;

	    if(r<=mutaProb)//then mutation occurs (bool value is flipped)
	    {	
			//printf("Mutation occured at element: %d",locus);

			//determine whether the current bit is a '1' or '0'
			//and set accordingly

			if(genes[arrayElement] & bitAt[bitPos]) 
			{ //turn the '1' to a '0' (using XOR)
				genes[arrayElement] = genes[arrayElement] ^ bitAt[bitPos];
			}
			else
			{ //turn the '0' to a '1' (using OR)
				genes[arrayElement] = genes[arrayElement] | bitAt[bitPos];
			}
     
	    }//end of if

		bitPos++;
   } //end for

} //end of 'chromosome::mutate'

//=============================================================================

int Cchromosome::ExtractValue(unsigned int position, unsigned int valsize)
{//values in bool array are treated as a bit string
//the value at 'position' is treated as part of the genes-string that forms the
//value

	if(genes==NULL) //defensive programming
	   	return (-1);


	if(valsize>15)
		valsize=15; //a max 15 bit length gives you a maximum value of 32763
    //this is more than enough! Also, using ints, a 16 bit value would
    //cause an overflow into negative numbers

	if(valsize==0)
		valsize=1; //valsize must be at least 1 bit
	//---------------------------------------------------------------------------
	//test whether position + valsize out of range
	if((position+valsize)>length)
		return (-1);
	
	//---------------------------------------------------------------------------
	//CONVERT THE SELECTED PORTION OF THE CHROMOSOME INTO A VALUE

	unsigned int arrayElement = 0; //tracks which element is currently being read
	unsigned int bitPos = 0; //tracks which bit of an 8-bit gene 'element' is currently 
							//being read

	int bitvalue=1;		//value of bit in corresponding gene-string section
	int totalvalue=0;	//total value of gene-string portion

	//set arrayElement and bitPos so that they correspond to the 'position' 
	//in the gene-string
	arrayElement = position/8;
	bitPos = position%8;

	for(unsigned int locus=0; locus<valsize; locus++)
	{
		//move onto the next element once all the bits
		//in the current element have been read
		if(bitPos > 7)
		{
			bitPos = 0;
			arrayElement++;	
		}

		for(int i=(valsize-(locus+1)); i>0; i--)
		{
			bitvalue = bitvalue << 1; //multiplies 'bitvalue' by 2
		}
		
		//if the current bit element is 'true' then add to the total value
		if(genes[arrayElement] & bitAt[bitPos])
		{
			totalvalue += bitvalue;
		}

		bitvalue=1; //reset bit order value ready for next bit order
					//value calculation


		bitPos++;
	} //end of for 


	//Return the corresponding value
	//(returns a negative value if the process has failed)
	return totalvalue;
}

//=============================================================================

BOOL Cchromosome::InsertValue(unsigned int position, unsigned int bitlength,
 unsigned int value) //default value=15
{

	unsigned int bitorder=0; //e.g. 6th bit from low end bit order
	unsigned int bitorderval=0;	//value of the CURRENT bit order
	unsigned int bitsrequired=0;	//number of bits required to store value
    unsigned int bitvalue=1;	//value of the CURRENT bit order

	unsigned int arrayElement = 0; //tracks which element is currently being assigned
	unsigned int bitPos = 0;  //tracks which bit of an 8-bit gene 'element' is currently 
							//being assigned 

	unsigned int remainingval; //remainder of value to be converted into binary
	unsigned int i;	//used in forloops

	//--------------------------------------------------------------------
	//CHECK FOR ERROR
	//check whether it is legal to insert value at specified position...
	//...by finding how many BITs are needed to store the value
	//		=> check that maximum value has not been execeeded
	if(value>32767 || bitlength>15)
	   	return 0;

	for(i=1; i<=value; i*=2)
		bitsrequired++;

	if(value<1)
		bitsrequired=1; //still need a bit to store a zero value


	//if 'bitlength' is shorter than the number os bits required to store value...
	//...then adjust 'bitlength' to accomodate this value
	if(bitlength < bitsrequired)
		bitlength = bitsrequired;

	//Check whether insertion (taking 'position' into account) is in the legal range
	if((position+bitlength)>length)
		return 0; //can't do it!

	//--------------------------------------------------------------------
	//Everythings OK - Perform insertion

	//store the remaining value that needs to be 
	remainingval = value;
	
	//set arrayElement and bitPos so that they correspond to the 'position' 
	//in the gene-string
	arrayElement = position/8;
	bitPos = position%8;

	//calculate bitorder
	bitorder=bitlength-1;

	//start with the High Bit Order and work right
	for(i=0; i<bitlength; i++)
	{
		//check whether all 8-bits of the current element have been 
		//set and if so move onto the next element
		if(bitPos > 7)
		{
			bitPos = 0;
			arrayElement++;
		}

		//printf("\nBit Order: %d",bitorder);
		
		bitorderval=1;

		//calculate value of bitorder
		for(unsigned int f=0; f<bitorder; f++)
			bitorderval *= 2;

		//printf("\nBitorder Value: %d",bitorderval);
		//getch();

		//zero out the current bit (using XOR)
		if(genes[arrayElement] & bitAt[bitPos])
		{
			genes[arrayElement] = genes[arrayElement] ^ bitAt[bitPos];
		}
		

		//find out if bitorder value divides into the passed value
		if((remainingval/bitorderval)!=0)
		{ 
			//it does - insert a '1' at the corresponding position
			genes[arrayElement] = genes[arrayElement] | bitAt[bitPos];
			//printf("\nONE ASSIGNED");
			
			//take current 'bitvalue'
			remainingval = remainingval - bitorderval;
		}
	

		bitorder--;
		bitPos++;
	}//end of for

   return 1;
}

//=============================================================================

void Cchromosome::DisplayGenes() //Displays chromosome's 'genes Sequence'
{
	if(genes==NULL)
	   	return;

	unsigned int value = 0; // the current allele value to be printed
	unsigned int arrayElement = 0; //tracks which element is currently being read
	unsigned int bitPos = 0; //tracks which bit of an 8-bit gene 'element' is currently
	//being read
	
	//printf("\nDisplay  Chromosome: ");

	for(unsigned int locus=0; locus<length; locus++)
	{
		//check whether all 8-bits of the current element have been
		//read, and if so, move onto the next element.

		if(bitPos > 7)
		{
			bitPos = 0;
			arrayElement++;
			//printf(", ");
		}

		if(genes[arrayElement] & bitAt[bitPos])
		{
			value = 1;
		}
		else
		{
			value = 0;
		}


   		printf("%d", value);
	

		bitPos++;
   }//end of for

}//end of 'DisplayGenes'

//=============================================================================

void Cchromosome::DisplayFitness()//Displays current 'Fitness Score'
{
	if(genes==NULL)
	   	return;
	
	printf("%d",fitness);
}

//=============================================================================

BOOL Cchromosome::Copy(Cchromosome* received)
{
	//test to see if chromosomes are the same length - defensive programming
	if(this->genes==NULL || received->genes==NULL)
	return 0; //i.e. cannot mate (genes not pointing to an array)

	if(this->length != received->length)
		return 0;   //i.e. cannot mate chromosomes (lengths are different)

	//-----------------------------------------------------------------------
	//Everythings OK - genes can be copied from 'recieved' into current
	//chromosome object

	for(unsigned int locus=0;locus<arraySize;locus++)
	{
		this->genes[locus]=received->genes[locus];
	}

	//assign 'received' fitness to current chromosome
	this->fitness = received->fitness;

	return 1;
}



//=============================================================================
//						POPULATION OBJECT
//=============================================================================



//Definition of Population object

//default constructor
Cpopulation::Cpopulation() : size(8), chromolen(32), generation(0),
crossProb(800), mutaProb(5), elitism(0), eliteCopies(1),
fitness(0), meanFitness(0), swapRate(500)
{
	//allocate memory for new chromosome and attach pointer
	currentPool= new Cchromosome[size]; //DMA- the current population
	matingPool=new Cchromosome[size]; //DMA - the selection pool...
	//...these chromosomes are then mated/mutated and placed back into
	//the 'currentPool'.

   //initialise the genes-string of each chromosome in both 'currentPool'
   //and 'matingPool' using the CreateGenes(...) function  (need to pass
   //chromolen)
	for(unsigned int l=0; l<size; l++)
	{
  		currentPool[l].CreateGenes(chromolen);
	    matingPool[l].CreateGenes(chromolen);
	}

}//end of default constructor

//============================================================================
//custom constructor

Cpopulation::Cpopulation(unsigned int newsize, unsigned int newchromolen,
unsigned int newcrossProb, unsigned int newmutaProb, unsigned int newelitism,
unsigned int neweliteCopies, unsigned int newswapRate) :
size(newsize), chromolen(newchromolen), generation(0), crossProb(newcrossProb),
mutaProb(newmutaProb), elitism(newelitism), eliteCopies(neweliteCopies),
fitness(0), meanFitness(0), swapRate(newswapRate)
{
	//make sure size is an even number (if not adjust so that it is)
	if(newsize%2)
	{
		newsize++;
	}

	//allocate memory for new chromosome and attach pointer
	currentPool= new Cchromosome[newsize]; //DMA- the current population
	matingPool=new Cchromosome[newsize]; //DMA - the selection pool...
   //...these chromosomes are then mated/mutated and placed back into
   //the 'currentPool'.

   //initialise the genes-string of each chromosome in both 'currentPool'
   //and 'matingPool' using the CreateGenes(...) function  (need to pass
   //chromolen)
   for(unsigned int l=0; l<newsize; l++)
   {
		currentPool[l].CreateGenes(newchromolen);
		matingPool[l].CreateGenes(newchromolen);
   }

	//make sure that the number of elite chromosomes does not exceed 'size'
   if(elitism != 0)
   {
	   //Must have at least one copy of every 'elite' chromosome 
		if(eliteCopies == 0)
			eliteCopies = 1;

		if(elitism > size)
		{
			elitism = size;
			eliteCopies = 1;
		}

		if(eliteCopies > size)
		{
			eliteCopies = size;
		}

		
		if((elitism*eliteCopies) > size)
		{
			//find the maximum number of 'copies'
			//allowed given the current number of
			//'elite chromosomes'
			eliteCopies = size / elitism;		
		}
   }


}//end of custom constructor

//===========================================================================

//copy constructor

Cpopulation::Cpopulation(const Cpopulation& copyPopulation) :
size(copyPopulation.size), chromolen(copyPopulation.chromolen), 
generation(copyPopulation.generation), mutaProb(copyPopulation.mutaProb),
elitism(copyPopulation.elitism), eliteCopies(copyPopulation.eliteCopies),
crossProb(copyPopulation.crossProb), fitness(copyPopulation.fitness),
meanFitness(copyPopulation.meanFitness), swapRate(copyPopulation.swapRate)
{

	//allocate memory for new  chromosome and attach pointer
	currentPool = new Cchromosome[copyPopulation.size]; //DMA - the current population
	matingPool = new Cchromosome[copyPopulation.size];  //DMA - the selection pool

	//initialise the genes-string of each chromosome in both 'currentPool'
	//and 'matingPool' using the CreateGene(...) function
	// (need to pass chromolen). 
	for(unsigned int l=0; l<size; l++)
	{
		currentPool[l].CreateGenes(copyPopulation.chromolen);
		matingPool[l].CreateGenes(copyPopulation.chromolen);
	}

	//the genes in each pool's chromosomes have been assigned random values
	//therefore the actual values need to be transferred
	for(unsigned int l=0; l<size; l++)
	{
		currentPool[l].Copy(&copyPopulation.currentPool[l]);	
		matingPool[l].Copy(&copyPopulation.matingPool[l]);
	}



}//end of copy constructor



//===========================================================================
//destructor

Cpopulation::~Cpopulation()
{
	delete [] currentPool;
	delete [] matingPool;
}

//===========================================================================

unsigned int Cpopulation::GetGeneration()
{
	return generation;
}

//===========================================================================

unsigned int Cpopulation::GetSize()
{
	return size;
}

//===========================================================================

unsigned int Cpopulation::GetChromoLen()
{
	return chromolen;
}

//===========================================================================

unsigned int Cpopulation::GetmutaProb()
{
	return mutaProb;
}

//===========================================================================

unsigned int Cpopulation::GetcrossProb()
{
	return crossProb;
}

//===========================================================================

unsigned int Cpopulation::GetFitness()
{
	return fitness;
}

//===========================================================================

float Cpopulation::GetMeanFitness()
{
	return meanFitness;
}

//===========================================================================
//===========================================================================
void Cpopulation::Select(unsigned int method, unsigned int sample)
{

	if(sample > size)
		sample = size;

	if(sample < 1)
		sample = 1;

	//printf("Sample: %d",sample);
//---------------------------------------------------------------------------
// Selection process vars
	unsigned int l; //used in forloops
	unsigned int r; //stores random value
	unsigned int upper; //used to define a portion of 'roulette' wheel...
	unsigned int lower; //...corresponding to a particular chromosome
	bool found=0;
	unsigned int candidate; //used to test whether chromosome is to be placed
	//into the selection pool

	//seed the random number generator
	srand( (unsigned)time( NULL ) );

	//temporary sample pool used in 'Tournament selection'
	unsigned int* tempPool; 
	tempPool = new unsigned int[sample];

	

//----------------------------------------------------------------------------
// Elitism vars
	unsigned int bestC=0; //keeps track of the best chromosome 
	unsigned int bestF=0; //tracks the current best Fitness
	unsigned int tempfit=0;
	unsigned int currfit=0;
	unsigned int marker=0; //marks the beginning point of the sort
	Cchromosome* sort;
	Cchromosome tempChromo(chromolen);

//-----------------------------------------------------------------------------
// ASSIGN POPULATION FITNESS
//-----------------------------------------------------------------------------
// FIND THE SUM OF ALL FITNESS' IN THE CURRENT POPULATION, 
// THEIR AVERAGE FITNESS, AND ALSO THE FITTEST (BEST) CHROMOSOME.

	sort = currentPool;
	
		for(l=0; l<size; l++)
		{
			//use a pointer instead

			//currfit=currentPool[l].GetFitness();
			currfit=sort->GetFitness();
			tempfit=tempfit+currfit;

			if(currfit > bestF)
			{
				bestF = currfit;
				bestC = l;
			}
			sort++;
		}

	//assign the total fitness
	fitness=tempfit;

	//assign the mean fitness
	meanFitness = (float)fitness/size;

//------------------------------------------------------------
   // ENSURE THAT THE BEST CHROMOSOME IS ALWAYS AT ELEMENT ZERO

   //If the fittest chromosome isn't at element
   //zero store the value at element zero so that
   //it can be swapped with the fittest chromosome.
   //Therefore the fittest chromosome is ALWAYS at
   //element one.
	if(bestC != 0)
	{
		//store the best Chromosome in a temporary chromosome
		tempChromo.Copy(&currentPool[bestC]);

		//copy the chromosome at element zero to the address
		//of the best chromosome
		currentPool[bestC].Copy(&currentPool[0]);

		//copy the temp chromosome into element zero
		currentPool[0].Copy(&tempChromo);
	}


//------------------------------------------------------------
// ELITISM
//------------------------------------------------------------
	//SORT ELITE CHROMOSOMES (Selection Sort)

	//Only need to go futher if elitism is turned on
	//and then only have to sort for how ever many
    //candidates need to be 'preserved' for the next 
	//generation.

	
	marker=0;
	if(elitism != 0)
	{
		marker = 1;

		for(marker=1; marker < elitism; marker++)
		{
			sort = currentPool;
			sort += marker;

			bestC=0;
			bestF=0;

				//go through remaining array and find the next 
				//best chromosome
				for(l = marker; l < size; l++)
				{
					currfit=sort->GetFitness();

					if(currfit > bestF)
					{
						bestF = currfit;
						bestC = l;
					}
					sort++;
				}//end of for

			//Found next best candidate
			if(bestC != marker)
			{
				//store the best Chromosome in a temporary chromosome
				tempChromo.Copy(&currentPool[bestC]);

				//copy the chromosome at element marker to the address
				//of the best chromosome
				currentPool[bestC].Copy(&currentPool[marker]);

				//copy the temp chromosome into element marker
				currentPool[marker].Copy(&tempChromo);
			}


		}//end of for

	

//---------------------------------------------------------------------
// Now transfer Elite Chromosomes (and their copies) into the Mating 
// Pool. Elite chromosome will NOT have crossover or mutation applied
// and so they will eventually be copied, unchanged, into the next
// generation.
	
		marker = 0;
		bestC=0; //index of the current copy

		for(l=0; l < elitism; l++)
		{

			for(r=0; r < eliteCopies; r++)
			{
				//copy entire chromosome to Mating Pool
				matingPool[marker].Copy(&currentPool[bestC]);

				marker++;	
			}

			bestC++;
	
		}//end of for


	}//end of 'if(elitism !=0)'

//---------------------------------------------------------------------
// SELECTION METHODS: 
//		0 => Roulette Wheel Selection
//      1 => Tournament Selection
//---------------------------------------------------------------------

	if(method == 0)
	{
//---------------------------------------------------------------------
// ROULETTE SELECTION
//---------------------------------------------------------------------
		//run this algorithm on NON-Elite chromosomes

		//printf("\nROULETTE WHEEL SELECTION\n");
		for(l=marker; l<size; l++)
		{
   			//generate a random number (max: total fitness of population)
			r=rand()%(fitness);
			r++;
		
			//find the chromosome who's range the random number falls into
			found=0;
			lower=0;
			upper=0;
			candidate=0;

   			while(found==0)
   			{
      			upper += currentPool[candidate].GetFitness();

				if(r>lower && r<=upper)
				{//random value within candidate chromosomes range!
					//copy this chromosome into the 'matingPool'
					matingPool[l].Copy(&currentPool[candidate]);
					found=1;
				}
			
				//what was the upper bound of this chromosome becomes 
				//the lower bound value for the next chromosome
				lower =  lower + currentPool[candidate].GetFitness();
				candidate++; //increment chromosome
			}

		}//end of forloop



	} //end of 'Roulette Select'
	else
	{
//--------------------------------------------------------------------
// TOURNAMENT SELECTION
//--------------------------------------------------------------------
		//run this algorithm on NON-Elite chromosomes

		//printf("\nTOURNAMENT SELECTION\n");
		for(l= marker; l<size; l++)
		{
			unsigned int i;
			currfit=0;
			bestF=0;
			bestC=0;
			r=0;
		

			// First, pick a bunch of chromosome at random and place them 	
			// in the sample pool
			for(i=0; i < sample; i++)
			{
				//pick a chromosome at random
				r=rand()%(size);

				//store it's index in the 'sample pool' array
				tempPool[i] = r;
				//printf("\nRandom number: %d",tempPool[i]);
			}

			//Now, find the fittest chromosome in this pool		
			for(i = 0; i < sample; i++)
			{

				//printf("\nValue at element: %d",tempPool[i]);
				currfit= currentPool[ tempPool[i] ].GetFitness();
				
				if(currfit > bestF)
				{
					bestF = currfit;
					bestC = tempPool[i];
				}

			}//end of for
			
			//copy this chromosome into the mating pool
			matingPool[l].Copy(&currentPool[bestC]);

		} //end of for

	} //end of 'Tournament Select'

delete[] tempPool; //IMPORTANT deallocate memory from pointer

//by the end of this function there should be as many chromosomes in the
//'matingPool' as there are in the 'currentpool'.

}//end of 'Select' function

//============================================================================

void Cpopulation::Mate(unsigned int method)
{
	unsigned int l;			//used in loop
	int result;   //used to store result of mating attempt
	unsigned int marker;

	//-----------------------------------------------------------------------
	// Elitism - move the marker past the 'Elite chromosomes' so that they are
	// untouched by the crossover process
	marker = elitism*eliteCopies;

	//Make sure mating process starts with the next chromosome 'pairing'
	if(marker%2)
		marker++;
	
	if(marker>size)
		marker=size;

	//-----------------------------------------------------------------------
	//go through each chromosome pair in turn calling the 'chromosome.Mate'
	//function (also need to pass the population's crossover probability 
	//to this function)

	for(l=marker; l<size; l += 2)
	{
		//Display the state of the Chromosomes before mating
		printf("\n\nBefore mating...");
		printf("\nCHROMOSOME %d: ",l);
		matingPool[l].DisplayGenes();

		printf("\nCHROMOSOME %d: ",l+1);
		matingPool[l+1].DisplayGenes();

		//Try and mate the current CHROMOSOME pair
		result=matingPool[l].Mate(&matingPool[l+1], method, crossProb, swapRate);

		//Display the results of the mating process
		printf("\n\nAfter mating...");
		printf("\nCHROMOSOME %d: ",l);
		matingPool[l].DisplayGenes();

		printf("\nCHROMOSOME %d: ",l+1);
		matingPool[l+1].DisplayGenes();


		switch(result)
		{
			case 0:
  				printf("\nERROR - chromosomes incompatible");
  					break;
			case 1:
				printf("\nCrossover occured");
		   			break;
			default:
   			printf("\nNO Crossover occured");
		   			break;
		}

		printf("\n");
	} //end of forloop


}//end of Mate function

//============================================================================

void Cpopulation::Mutate()
{
	unsigned int marker;
	//-----------------------------------------------------------------------
	// Elitism - move the marker past the 'Elite chromosomes' so that they are
	// untouched by the mutation process
	marker = elitism*eliteCopies;

	//Make sure mating process starts with the next chromosome 'pairing'
	if(marker%2)
		marker++;
	
	if(marker>size)
		marker=size;

	//-----------------------------------------------------------------------

	//run the chromosome::mutate function on every chromosome in the
   //matingPool (passing the population's mutational probability)
   for(unsigned int l=marker;l<size;l++)
   {
		matingPool[l].Mutate(mutaProb);
   }
}//end of Mutate function

//============================================================================

//void Cpopulation::AssignPopFitness() //of current population only
//{
	//Aswell as finding the population's total and mean fitness
	//score. We need to sort the current populations chromosome
	//array in order of fitness so that the fittest chromosome
	//is in element[0]. Use a SELECTION SORT algorithm 


//	unsigned int bestC=0; //keeps track of the best chromosome 
//	unsigned int bestF=0; //tracks the current best Fitness
//	unsigned int tempfit=0;
//	unsigned int currfit=0;
//	unsigned int marker=0; //marks the beginning point of the sort
//	Cchromosome* sort;
//	Cchromosome tempChromo(chromolen);

//	sort = currentPool;
	//sum up all fitness' while simultaneous finding the fittest
	//chromosome
//	for(unsigned int l=0; l<size; l++)
//	{
		//use a pointer instead

		//currfit=currentPool[l].GetFitness();
//		currfit=sort->GetFitness();
//		tempfit=tempfit+currfit;

//		if(currfit > bestF)
//		{
//			bestF = currfit;
//			bestC = l;
//		}
//		sort++;
//	}

	//assign the total fitness
//   fitness=tempfit;

   //assign the mean fitness
//   meanFitness = (float)fitness/size;

   
   //------------------------------------------------------------
   // ENSURE THAT THE BEST CHROMOSOME IS ALWAYS AT ELEMENT ZERO

	//tempfit = currentPool[0].GetFitness();
	//printf("\nCHROMO FITNESS at element zero: %d", tempfit);
	//printf("\nThe BEST CHROMO was at element: %d", bestC);

   //If the fittest chromosome isn't at element
   //zero store the value at element zero so that
   //it can be swapped with the fittest chromosome.
   //Therefore the fittest chromosome is ALWAYS at
   //element one.
//	if(bestC != 0)
//	{
		//store the best Chromosome in a temporary chromosome
//		tempChromo.Copy(&currentPool[bestC]);

		//copy the chromosome at element zero to the address
		//of the best chromosome
//		currentPool[bestC].Copy(&currentPool[0]);

		//copy the temp chromosome into element zero
//		currentPool[0].Copy(&tempChromo);
//	}

	//------------------------------------------------------------
	//SORT ELITE CHROMOSOMES

	//Only need to go futher if elitism is turned on
	//and then only have to sort for how ever many
    //candidates need to be 'preserved' for the next 
	//generation.

//	marker = 1;

//	if(elitism != 0)
//	{

//		for(marker=1; marker < elitism; marker++)
//		{
//			sort = currentPool;
//			sort += marker;

//			bestC=0;
//			bestF=0;

			//go through remaining array and find the next 
			//best chromosome
//			for(unsigned int i = marker; i < size; i++)
//			{
//				currfit=sort->GetFitness();

//				if(currfit > bestF)
//				{
//					bestF = currfit;
//					bestC = i;
//				}
//				sort++;
//			}//end of for

			//Found next best candidate
//			if(bestC != marker)
//			{
				//store the best Chromosome in a temporary chromosome
//				tempChromo.Copy(&currentPool[bestC]);

				//copy the chromosome at element zero to the address
				//of the best chromosome
//				currentPool[bestC].Copy(&currentPool[marker]);

				//copy the temp chromosome into element zero
//				currentPool[marker].Copy(&tempChromo);
//			}


//		}//end of for

//	}//end of if

	//------------------------------------------------------------
   
   

//}//end of 'AssignPopFitness'

//============================================================================

void Cpopulation::AssignFitness(unsigned int element, unsigned int newfitness)
{

	if(element>=size)    //makes sure that a value greater than max elements
	   	element=(size-1); //isn't used

	currentPool[element].AssignFitness(newfitness);
}//end of 'AssignFitness'

//============================================================================



//============================================================================

int Cpopulation::ExtractValue(unsigned int element, unsigned int position,
unsigned int valsize)
{
	int value;

	value=currentPool[element].ExtractValue(position,valsize);

	return value;
}//end of 'ExtractValue'

//============================================================================

//insert a value into the gene-string of a chromosome
int Cpopulation::InsertValue(unsigned int element, unsigned int position,
unsigned int bitlength, unsigned int value)
{
	int result;

	result=currentPool[element].InsertValue(position, bitlength, value);

	return result;
}//end of InsertValue


//============================================================================

void Cpopulation::NextGeneration()
{//copy 'matingPool' chromosomes into 'currentPool'

	for(unsigned int l=0; l<size; l++)
	{
   		currentPool[l].Copy(&matingPool[l]);
	}

	//increment the generation counter
	generation++;
}//end of 'NextGeneration'

//============================================================================

void Cpopulation::DisplayCurrent()
{
	unsigned int l; //used in for-loops


	printf("\n\nCurrent Population:\tGeneration: %d\n",generation);
	for(l=0; l<size; l++)
	{
 		printf ("\nChromo %d: ",l);
		currentPool[l].DisplayGenes();
		printf("   FITNESS: %d",currentPool[l].GetFitness());
	}

	printf("\nPopulations TOTAL FITNESS: %d\n",fitness);
	printf("Populations MEAN  FITNESS: %f\n",meanFitness);
	//printf("The best candidate is: %d\n"
}// end of 'DisplayCurrent'

//============================================================================

void Cpopulation::DisplayMating()
{
	unsigned int l;
	//--------------------------------------------------------
	//make sure the total fitness of the mating pool is
	//assigned


	unsigned int tempfit=0;
	float tempMean;

	for(l=0; l<size; l++)
	{
		tempfit=tempfit+matingPool[l].GetFitness();
	}

	tempMean = (float)tempfit/size;


	//---------------------------------------------------------

	printf("\n\nMating Pool:\tGeneration: %d\n",generation);
	for(l=0; l<size; l++)
	{
   		printf ("\nChromo %d: ",l);
		matingPool[l].DisplayGenes();
		printf("   FITNESS: %d",matingPool[l].GetFitness());
	}

	printf("\nPopulations TOTAL FITNESS: %d\n", tempfit);
	printf("Populations MEAN  FITNESS: %f\n", tempMean);
}// end of 'DisplayMating'

