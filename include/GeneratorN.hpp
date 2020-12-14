#pragma once
#include "own.hpp"
#include "Generator.hpp"

class GeneratorN : public Generator
{
private:
	bool _isFirstIteration;
	double _vecNeuronState[100] = { 0 };
	double _widthMatrix[100][100] = { {0} };
public:
	GeneratorN(int keySize = 32);
	GeneratorN(GeneratorN const& other);
	GeneratorN(GeneratorN && other);
	GeneratorN & operator=(GeneratorN const& other);
	GeneratorN & operator=(GeneratorN && other);
	ui64 getKey();
	void showState();
	void showMatrix();
	~GeneratorN();
};