#include "TimeTest.hpp"

TimeTest::TimeTest(Generator * gen) : Test(gen) {}

TimeTest::~TimeTest()
{
    _gen = nullptr;
}

void TimeTest::generateSamples()
{
	for (int i = 0; i < 100000; ++i)
	{
		_gen->getKey();
	}
}


void TimeTest::test()
{
	ui32 start_time =  clock();
    generateSamples();
    ui32 end_time =  clock();
    std::cout << "Time testing for " << _gen->getName() << ": " << std::endl;
    std::cout << "    Total time of generating 100000 samples: " << (end_time - start_time) / (double) CLOCKS_PER_SEC << " sec;" << std::endl;
    std::cout << "    Time of generating single sample: " << (end_time - start_time) / 100000.0 / CLOCKS_PER_SEC << " sec;" << std::endl;
}