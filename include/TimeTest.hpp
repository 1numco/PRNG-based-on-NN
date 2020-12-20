#pragma once
#include "own.hpp"
#include "Test.hpp"

class TimeTest: public Test
{
public:
	TimeTest(Generator * gen);
	~TimeTest();
	void generateSamples();
	void test();
};