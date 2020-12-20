#include "NNH.hpp"
#include "Parser.hpp"
#include "GeneratorL_N.hpp"
#include "GeneratorN.hpp"
#include "HiTest.hpp"
#include "LCG.hpp"
#include "CCG.hpp"
#include "EmbGenerator.hpp"
#include "TimeTest.hpp"

int main()
{
	int keyLen = 32;
	std::cout << "Test PRNG based on neural network Hopfield and LFSR" << std::endl;
	GeneratorL_N * gen1 = new GeneratorL_N("../register.txt", 48, 0, keyLen);
	HiTest * hitest = new HiTest(gen1);
	hitest->test();
	TimeTest * timetest = new TimeTest(gen1);
	// timetest->test();
	//gen1->writeSamplesToBinFile(1000000, "../generated_samples_1_1.bin");
	delete gen1;

	std::cout << std::endl;
	std::cout << "Test PRNG based on neural network Hopfield with float matrix" << std::endl;
	GeneratorN * gen2 = new GeneratorN(keyLen);
	hitest->setGen(gen2);
	hitest->test();
	timetest->setGen(gen2);
	// timetest->test();
	// gen2->writeSamplesToBinFile(1000000, "../generated_samples_2.bin");
	delete gen2;

	std::cout << std::endl;
	std::cout << "Test LCG" << std::endl;
	LCG * gen3 = new LCG;
	hitest->setGen(gen3);
	hitest->test();
	timetest->setGen(gen3);
	timetest->test();
	gen3->writeSamplesToBinFile(1000000, "../generated_samples_4.bin");
	delete gen3;

	std::cout << std::endl;
	std::cout << "Test embedded non-deterministic generator" << std::endl;
	EmbGenerator * gen4 = new EmbGenerator;
	hitest->setGen(gen4);
	hitest->test();
	timetest->setGen(gen4);
	timetest->test();
	//gen4->writeSamplesToBinFile(1000000, "../generated_samples_5.bin");
	delete gen4;

	std::cout << std::endl;
	std::cout << "Test CCG" << std::endl;
	CCG * gen5 = new CCG;
	hitest->setGen(gen5);
	hitest->test();
	timetest->setGen(gen5);
	timetest->test();
	gen5->writeSamplesToBinFile(1000000, "../generated_samples_6.bin");
	delete gen5;

	delete timetest;
	delete hitest;
	return 0;
}