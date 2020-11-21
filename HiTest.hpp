#pragma once
#include "own.hpp"
#include "Test.hpp"

class HiTest: public Test
{
private:
	int k = 101;
	double etalonHi = 124.3421134;
	int frequency[101] = { 0 };
	double etalonFreq = 1.0 / k;
	double etalonNum = (double)n / k;
	double calculateHi();
	double _mean;
	double _variance;
public:
	HiTest(ui64 maxValue, int keyLength, Generator * gen);
	~HiTest();
	void generateSamples();
	void mean();
	void variance();
	void setGen(Generator * gen);
	bool test();
};