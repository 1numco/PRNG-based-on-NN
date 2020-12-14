#pragma once
#include "own.hpp"
#include "Generator.hpp"
#include "GeneratorN.hpp"
#include "GeneratorL_N.hpp"

class Test
{
protected:
	ui64 _maxValue;
	int n = 5000;
	double samples[5000] = { 0 };
	Generator * _gen = nullptr;
public:
	Test(ui64 maxValue, Generator * gen) : _maxValue(maxValue), _gen(gen){}
	virtual void generateSamples(){}
	virtual bool test() { return false; }
	virtual void setGen(){}
	virtual ~Test(){}
};