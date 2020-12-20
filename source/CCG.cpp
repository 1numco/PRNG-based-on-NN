#include "CCG.hpp"

CCG::CCG() : seed(time(NULL)) {}

ui64 CCG::getKey()
{
    seed = (seed * seed * seed * a) & 0xffffffff;
    return seed;
}

void CCG::setSeed(ui64 newSeed)
{
    seed = newSeed;
}