#include "HiTest.hpp"

HiTest::HiTest(ui64 maxValue, Generator * gen) : Test(maxValue, gen), _mean(0), _variance(0) {}

HiTest::~HiTest()
{
	delete _gen;
}

void HiTest::generateSamples()
{
	for (int i = 0; i < n; ++i)
	{
		ui64 tmp = _gen->getKey();
		samples[i] = tmp / (double)_maxValue;
		frequency[(int)(samples[i] / etalonFreq)] += 1;
	}
}

double HiTest::calculateHi()
{
	double hi = 0;
	for (int i = 0; i < k; ++i)
	{
		hi += pow(frequency[i] - etalonNum, 2);
	}
	hi *= 1 / etalonNum;
	for (int i = 0; i < 101; ++i)
	{
		frequency[i] = 0;
	}
	return hi;
}

void HiTest::mean()
{
	for (int i = 0; i < n; ++i)
		_mean += samples[i];
	_mean /= n;
}

void HiTest::variance()
{
	mean();
	for (int i = 0; i < n; ++i)
		_variance += pow(samples[i] - _mean, 2);
	_variance /= n;
}

bool HiTest::test()
{
	variance();
	double hi = calculateHi();
	std::cout << "Calculated Hi^2 value: " << hi << std::endl;
	std::cout << "Etalon Hi^2 value: " << etalonHi << std::endl;
	if (hi > etalonHi)
	{
		std::cout << "Calculated Hi^2 > Etalon Hi^2 => reject null hypothesis " << std::endl;
		std::cout << "Mean: " << _mean << std::endl;
		std::cout << "Variance: " << _variance << std::endl;
		return false;
	}
		
	else
	{
		std::cout << "Calculated Hi^2 > Etalon Hi^2 => failed to reject null hypothesis " << std::endl;
		std::cout << "Mean: " << _mean << std::endl;
		std::cout << "Variance: " << _variance << std::endl;
		return true;
	}
}

void HiTest::setGen(Generator * gen)
{
	_gen = gen;
}