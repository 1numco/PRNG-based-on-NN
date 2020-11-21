#include "GeneratorL_N.hpp"

GeneratorL_N::GeneratorL_N()
{
	reg = nullptr;
	net = nullptr;
}

GeneratorL_N::GeneratorL_N(std::string pathToRegisterState,
	std::string pathToNeuronWidths)
{
	Parser parser;
	reg = parser.parseLSFRfile(pathToRegisterState);
	net = parser.parseNNHfile(pathToNeuronWidths);
}

GeneratorL_N::GeneratorL_N(std::string pathToRegisterState, ui8 N, ui64 state)
{
	Parser parser;
	reg = parser.parseLSFRfile(pathToRegisterState);
	net = new NNH(N, state);
	net->generateWeightMatrix();
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
	//this->attractors.insert(net->getVecNeuronState());
	//this->table_attractors[net->getVecNeuronState()].insert(reg->getState());
	return out;
}

ui64 GeneratorL_N::getKey(int size)
{
	ui64 out = 0;
	int i;
	for (i = 0; i < size; i++)
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


//void GeneratorL_N::showAttractors()
//{
//	std::set <uint64_t> ::iterator itr;
//	for (itr = this->attractors.begin(); itr != this->attractors.end(); ++itr)
//	{
//		std::cout << '\n' << std::bitset<1 * CHAR_BIT>(*itr);
//	}
//	std::cout << std::endl;
//}
//
//void GeneratorL_N::showTableOfAttractors()
//{
//	std::ofstream out;
//	out.open("C:\\Users\\vtroynya\\source\\repos\\sci_work\\sci_work\\attractors.txt");
//	std::set <uint64_t> ::iterator itr;
//	std::map<uint64_t, std::set<uint64_t>>::iterator itr1;
//	for (itr1 = this->table_attractors.begin(); itr1 != this->table_attractors.end(); ++itr1)
//	{
//		std::cout << "attractor:" << std::bitset<1 * CHAR_BIT>(itr1->first) << std::endl;
//		out << std::bitset<1 * CHAR_BIT>(itr1->first) << std::endl;
//		for (itr = itr1->second.begin(); itr != itr1->second.end(); ++itr)
//		{
//			std::cout << "    state:" << std::bitset<1 * CHAR_BIT>(*itr) << std::endl;
//			out << std::bitset<1 * CHAR_BIT>(*itr) << std::endl;
//		}
//		std::cout << std::endl;
//		out << std::endl;
//	}
//	out.close();
//	std::cout << std::endl;
//}