#include "GeneratorL_N.hpp"

GeneratorL_N::GeneratorL_N(int keySize)
{
	reg = nullptr;
	net = nullptr;
	_keySize = keySize;
	_name = "Generator based on Hopfield neural network and LFSR";
}

GeneratorL_N::GeneratorL_N(std::string pathToRegisterState,
	std::string pathToNeuronWidths, int keySize)
{
	Parser parser;
	reg = parser.parseLSFRfile(pathToRegisterState);
	net = parser.parseNNHfile(pathToNeuronWidths);
	_keySize = keySize;
	_name = "Generator based on Hopfield neural network and LFSR";
}

GeneratorL_N::GeneratorL_N(std::string pathToRegisterState, ui8 N, ui64 state, int keySize)
{
	Parser parser;
	reg = parser.parseLSFRfile(pathToRegisterState);
	net = new NNH(N, state);
	net->generateWeightMatrix();
	_keySize = keySize;
	_name = "Generator based on Hopfield neural network and LFSR";
}

GeneratorL_N::~GeneratorL_N()
{
	delete reg;
	delete net;
}

ui8 GeneratorL_N::doStep()
{
	reg->doStep();
	net->setVecNeuronState(reg->getState());
	ui8 out = net->doStep();
	return out;
}

ui64 GeneratorL_N::getKey()
{
	ui64 out = 0;
	int i;
	for (i = 0; i < _keySize; i++)
	{
		out = out << 1 | doStep() & 1;
	}
	return out;
}

void GeneratorL_N::showStates()
{
	std::cout << "reg: ";
	reg->showState();
	std::cout << ", net: ";
	net->showState();
	std::cout << std::endl;
}


void GeneratorL_N::showMatrix()
{
	net->showMatrix();
}