#include "NNH.hpp"
#include "Parser.hpp"
#include "GeneratorL_N.hpp"
#include "GeneratorN.hpp"
#include "HiTest.hpp"
#include "LCG.hpp"
#include "EmbGenerator.hpp"

int main()
{
	int keyLen = 32;
	GeneratorL_N * gen1 = new GeneratorL_N("../register.txt", 48, 0, keyLen);
	std::cout << "Test PRNG based on neural network Hopfield and LFSR" << std::endl;
	GeneratorN * gen2 = new GeneratorN(keyLen);
	HiTest * hitest = new HiTest(pow(2, keyLen), gen1);
	hitest->generateSamples();
	hitest->test();
	gen1->writeSamplesToBinFile(1000000, "../generated_samples_1_1.bin");
	delete hitest;

	std::cout << std::endl;
	std::cout << "Test PRNG based on neural network Hopfield with float matrix" << std::endl;
	HiTest * hitest1 = new HiTest(pow(2, keyLen), gen2);
	hitest1->generateSamples();
	hitest1->test();
	// gen2->writeSamplesToBinFile(1000000, "../generated_samples_2.bin");
	delete hitest1;

	std::cout << std::endl;
	std::cout << "Test LCG" << std::endl;
	LCG * gen3 = new LCG;
	HiTest * hitest2 = new HiTest(pow(2, keyLen), gen3);
	hitest2->generateSamples();
	hitest2->test();
	//gen3->writeSamplesToBinFile(1000000, "../generated_samples_4.bin");
	delete hitest2;

	std::cout << std::endl;
	std::cout << "Test embedded non-deterministic generator" << std::endl;
	EmbGenerator * gen4 = new EmbGenerator;
	HiTest * hitest3 = new HiTest(pow(2, keyLen), gen4);
	hitest3->generateSamples();
	hitest3->test();
	//gen4->writeSamplesToBinFile(1000000, "../generated_samples_5.bin");
	delete hitest3;
	return 0;
}