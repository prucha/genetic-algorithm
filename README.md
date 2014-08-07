Genetic Algorithm
=================

Please refer to the sites below for an introduction into Genetic Algorithms and their uses:

[www.ai-junkie.com](http://www.ai-junkie.com/)

[cs.felk.cvut.cz/~xobitko/ga/](http://www.obitko.com/tutorials/genetic-algorithms/)


This project contains my own Genetic Algorithm C++ classes. I have implemented these classes in an example Win32 Console application (compiled using Visual Studio 2012). You are free to use this code under a [MIT License](LICENSE).

The main source files are as follows:

 * [genetic.h](genetic.h) - G.A. class declarations
 * [genetic.cpp](genetic.cpp) - class definitions
 * [testGenetic.cpp](testGenetic.cpp) - test program using the G.A. classes
 
The Genetic Algorithm uses 2 classes; a **chromosome** class and a **population** class. Full documentation of these classes can be found in: [genetic.pdf](genetic.pdf) . In brief, the chromosome class defines the properties of an individual chromosome object. The population class is used to create whole populations of these chromosomes, and defines the selection and mating processes of all the chromosomes within the group. My classes currently support the following functions:

 * Roulette Wheel and Tournament Selection methods
 * Single-Point, Two-Point and Multi-Point crossover
 * Elitism
 * Mutation
