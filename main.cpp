#include "NNH.hpp"
#include "Parser.hpp"
#include "GeneratorL_N.hpp"
#include "GeneratorN.hpp"
#include "HiTest.hpp"

int main()
{
	GeneratorL_N * gen = new GeneratorL_N("C:\\Users\\vtroynya\\source\\repos\\sci_work\\sci_work\\register.txt", 48, 0);
	//Parser parser;
	//LFSR lfsr = parser.parseLSFRfile("C:\\Users\\vtroynya\\source\\repos\\sci_work\\sci_work\\register.txt");"C:\\Users\\vtroynya\\source\\repos\\sci_work\\sci_work\\widthMatrix.txt"
	ui8 tmp = 0;
	gen->showMatrix();
	GeneratorN * gen1 = new GeneratorN;
	/*gen1->showState();
	gen1->showMatrix();
	showKey(16, gen1->getKey(16));
	gen1->showState();*/
	HiTest * hitest = new HiTest(pow(2, 32), 32, gen);
	hitest->generateSamples();
	//hitest->test();
	while(!hitest->test())
	{
		delete gen;
		gen = new GeneratorL_N("C:\\Users\\vtroynya\\source\\repos\\sci_work\\sci_work\\register.txt", 48, 0);
		hitest->setGen(gen);
		hitest->generateSamples();
	}
	delete hitest;

	HiTest * hitest1 = new HiTest(pow(2, 32), 32, gen1);
	hitest1->generateSamples();
	hitest1->test();
	delete hitest1;
	//gen->showTableOfAttractors();
	system("pause");
	//delete gen;
	return 0;
}