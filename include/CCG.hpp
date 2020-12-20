#pragma once
#include "own.hpp"
#include "Generator.hpp"

class CCG : public Generator
{
private:
    ui64 seed;
    const static ui64 a = 214013U;
	const static ui64 m = 262133;
public:
	CCG();
	CCG(CCG const& other) = default;
	CCG(CCG && other) = default;
	CCG & operator=(CCG const& other) = default;
	CCG & operator=(CCG && other) = default;
	ui64 getKey();
    void setSeed(ui64 newSeed);
	~CCG() {};
};