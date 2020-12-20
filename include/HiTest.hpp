#pragma once
#include "own.hpp"
#include "Test.hpp"

class HiTest: public Test
{
private:
	int k = 101;
	ui64 _maxValue;
	int n = 5000;
	double samples[5000] = { 0 };
	double etalonHi = 124.3421134;
	int frequency[101] = { 0 };
	double etalonFreq = 1.0 / k;
	double etalonNum = (double)n / k;
	double calculateHi();
	double _mean;
	double _variance;
public:
	HiTest(Generator * gen);
	~HiTest();
	void generateSamples();
	void mean();
	void variance();
	void test();
};