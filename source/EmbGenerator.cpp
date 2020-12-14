#include "EmbGenerator.hpp"

EmbGenerator::EmbGenerator()
{
    dist = std::uniform_int_distribution<>(0, std::numeric_limits<unsigned int>::max());
}

ui64 EmbGenerator::getKey()
{
    return dist(rd) & 0xffffffff;
}