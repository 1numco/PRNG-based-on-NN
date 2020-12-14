#pragma once
#pragma once
#include "NNH.hpp"
#include "LFSR.hpp"
#include "Parser.hpp"
#include "Generator.hpp"

class GeneratorL_N: public Generator
{
private:
	LFSR * reg;
public:
	NNH * net;
	GeneratorL_N(int keySize = 32);
	GeneratorL_N(std::string pathToRegisterState, std::string pathToNeuronWidthsint, int keySize = 32);
	GeneratorL_N(std::string pathToRegisterState, ui8 N, ui64 state, int keySize = 32);
	~GeneratorL_N();
	ui8 doStep();
	ui64 getKey();
	void showStates();
	void showMatrix();
	//void showAttractors();
	//void showTableOfAttractors();
};