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
	GeneratorL_N();
	GeneratorL_N(std::string pathToRegisterState, std::string pathToNeuronWidths);
	GeneratorL_N(std::string pathToRegisterState, ui8 N, ui64 state);
	~GeneratorL_N();
	ui8 doStep();
	ui64 getKey(int size);
	void showStates();
	void showMatrix();
	//void showAttractors();
	//void showTableOfAttractors();
};