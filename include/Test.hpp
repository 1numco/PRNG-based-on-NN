#pragma once
#include "own.hpp"
#include "Generator.hpp"
#include "GeneratorN.hpp"
#include "GeneratorL_N.hpp"

class Test
{
protected:
	Generator * _gen = nullptr;
public:
	Test(Generator * gen) : _gen(gen) {}
	virtual void generateSamples(){}
	virtual void test() {}
	virtual void setGen(Generator * gen){ _gen = nullptr; _gen = gen;}
	virtual ~Test(){}
};