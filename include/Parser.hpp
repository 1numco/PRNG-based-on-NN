#pragma once
#include "own.hpp"
#include "LFSR.hpp"
#include "NNH.hpp"

class Parser
{
public:
	LFSR * parseLSFRfile(std::string);
	NNH * parseNNHfile(std::string);
};