#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <bitset>
#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <set> 
#include <map>
#include <iterator> 
#include <math.h>
#include <cmath>
#include <typeinfo>
#include <algorithm>
#include <vector>
#include <numeric>

typedef int8_t i8;
typedef uint8_t ui8;
typedef int16_t i16;
typedef uint16_t ui16;
typedef int32_t i32;
typedef uint32_t ui32;
typedef int64_t i64;
typedef uint64_t ui64;

#define CHAR_BIT 8


inline void showKey(int size, ui64 key)
{
	switch (size)
	{
	case 8: std::cout << std::bitset<1 * CHAR_BIT>(key) << std::endl;
		break;
	case 16: std::cout << std::bitset<2 * CHAR_BIT>(key) << std::endl;
		break;
	case 32: std::cout << std::bitset<4 * CHAR_BIT>(key) << std::endl;
		break;
	case 64: std::cout << std::bitset<8 * CHAR_BIT>(key) << std::endl;
		break;
	}
}