#pragma once
#include "own.hpp"
#include "NNH.hpp"

class Generator
{
public:
	NNH * net;
	virtual ui64 getKey(int size) = 0;
	virtual ~Generator(){}
};