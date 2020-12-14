#include "LCG.hpp"

LCG::LCG() : seed(time(NULL)) {}

ui64 LCG::getKey()
{
    seed = (seed * a + c) & 0xffffffff;
    return seed;
}

void LCG::setSeed(ui64 newSeed)
{
    seed = newSeed;
}