#pragma once
#include "own.hpp"
#include "Generator.hpp"

class LCG : public Generator
{
private:
    ui64 seed;
    const static ui64 a = 1123161;
    const static ui64 c = 0;
public:
	LCG();
	LCG(LCG const& other) = default;
	LCG(LCG && other) = default;
	LCG & operator=(LCG const& other) = default;
	LCG & operator=(LCG && other) = default;
	ui64 getKey();
    void setSeed(ui64 newSeed);
	~LCG() {};
};