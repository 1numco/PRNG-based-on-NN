#include "Parser.hpp"


LFSR * Parser::parseLSFRfile(std::string path)
{
	std::string line;
	ui8 size = 0;
	ui64 state = 0;
	ui64 coeffPolynom = 0;
	
	std::ifstream in(path);
	if (in.is_open())
	{
		getline(in, line);
		size = std::stoi(line);
		getline(in, line);
		state = std::stoi(line, 0, 16);
		getline(in, line);
		for (int i = 0; i < line.length(); ++i)
		{
			coeffPolynom = coeffPolynom << 4 | (std::stoi(std::string(1,line[i]), 0, 16) & 15);
		}
	}
	in.close();
	LFSR * tmp = new LFSR(size, state, coeffPolynom);
	return tmp;
}

NNH * Parser::parseNNHfile(std::string path)
{
	std::string line;
	std::string delimiter = " ";
	ui8 numNeurons = 0;
	ui64 vecNeuronState = 0;
	i8 **widthMatrix = 0;

	int pos;
	int t;
	std::ifstream in(path);
	if (in.is_open())
	{
		getline(in, line);
		numNeurons = stoi(line);
		vecNeuronState = 0;
		widthMatrix = new i8 *[numNeurons];
		for (int i = 0; i < numNeurons; ++i)
			widthMatrix[i] = new i8[numNeurons];
		int ind = 0;
		while (getline(in, line))
		{
			while ((pos = line.find(delimiter)) != std::string::npos) {
				widthMatrix[ind / numNeurons][ind % numNeurons] = stoi(line.substr(0, pos));
				line.erase(0, pos + delimiter.length());
				ind++;
			}
			widthMatrix[ind / numNeurons][ind % numNeurons] = stoi(line);
			ind++;
		}
	}
	in.close();
	NNH * tmp = new NNH(numNeurons, vecNeuronState, widthMatrix);
	widthMatrix = nullptr;
	return tmp;
}