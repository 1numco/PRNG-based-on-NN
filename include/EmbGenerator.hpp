#pragma once
#include "own.hpp"
#include "Generator.hpp"

class EmbGenerator : public Generator
{
private:
    std::random_device rd;
    std::uniform_int_distribution<> dist;
public:
	EmbGenerator();
	EmbGenerator(EmbGenerator const& other) = default;
	EmbGenerator(EmbGenerator && other) = default;
	EmbGenerator & operator=(EmbGenerator const& other) = default;
	EmbGenerator & operator=(EmbGenerator && other) = default;
	ui64 getKey();
	~EmbGenerator() {};
};