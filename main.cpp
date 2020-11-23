#include "NNH.hpp"
#include "Parser.hpp"
#include "GeneratorL_N.hpp"
#include "GeneratorN.hpp"
#include "HiTest.hpp"

int main()
{
	GeneratorL_N * gen = new GeneratorL_N("../register.txt", 48, 0);
	gen->showStates();
	ui8 tmp = 0;
	gen->showMatrix();
	std::cout << "Test PRNG based on neural network Hopfield and LFSR" << std::endl;
	GeneratorN * gen1 = new GeneratorN;
	HiTest * hitest = new HiTest(pow(2, 31), 31, gen);
	hitest->generateSamples();
	hitest->test();
	gen->writeToFile(100000000);
	delete hitest;
	std::cout << std::endl;
	std::cout << "Test PRNG based on neural network Hopfield with float matrix" << std::endl;
	HiTest * hitest1 = new HiTest(pow(2, 31), 31, gen1);
	hitest1->generateSamples();
	hitest1->test();
	delete hitest1;
	return 0;
}