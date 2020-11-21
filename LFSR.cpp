#include "LFSR.hpp"



LFSR::LFSR(ui8 size, ui64 state, ui64 coeffPolynom) : _size(size), _state(state), _coeffPolynom(coeffPolynom) {}


LFSR::LFSR() : _size(0), _state(0), _coeffPolynom(0) {}

LFSR::LFSR(LFSR const& other) : _size(other._size), _state(other._state), _coeffPolynom(other._coeffPolynom) {}

LFSR::LFSR(LFSR && other) : _size(other._size), _state(other._state), _coeffPolynom(other._coeffPolynom) 
{
	other._size = 0;
	other._state = 0;
	other._coeffPolynom = 0;
}

LFSR & LFSR::operator=(LFSR const& other)
{
	if (this != &other)
	{
		_size = other._size;
		_state = other._state;
		_coeffPolynom = other._coeffPolynom;
	}
	return *this;
}

LFSR & LFSR::operator=(LFSR && other)
{
	_size = other._size;
	_state = other._state;
	_coeffPolynom = other._coeffPolynom;
	other._size = 0;
	other._state = 0;
	other._coeffPolynom = 0;
	return *this;
}

LFSR::~LFSR()
{

}

void LFSR::showState()
{
	switch (this->_size)
	{
	case 8: std::cout << std::bitset<1 * CHAR_BIT>(this->_state);
		break;
	case 16: std::cout << std::bitset<2 * CHAR_BIT>(this->_state);
		break;
	case 32: std::cout << std::bitset<4 * CHAR_BIT>(this->_state);
		break;
	case 64: std::cout << std::bitset<8 * CHAR_BIT>(this->_state);
		break;
	}
}


void LFSR::showPolynom()
{
	switch (this->_size)
	{
	case 8: std::cout << std::bitset<1 * CHAR_BIT>(this->_coeffPolynom);
		break;
	case 16: std::cout << std::bitset<2 * CHAR_BIT>(this->_coeffPolynom);
		break;
	case 32: std::cout << std::bitset<4 * CHAR_BIT>(this->_coeffPolynom);
		break;
	case 64: std::cout << std::bitset<8 * CHAR_BIT>(this->_coeffPolynom);
		break;
	}
}

ui8 LFSR::doStep()
{
	ui64 tmp = 0;
	ui64 out = 0;
	out = this->_state;
	ui8 coeff = 0;
	for (ui64 i = 0; i < this->_size; ++i)
	{
		coeff = (this->_coeffPolynom >> i) & 1;
		if (coeff)
		{
			tmp ^= this->_state >> i;
		}
	}
	tmp &= 1;
	tmp = (tmp << this->_size - 1) | (this->_state >> 1);
	this->_state = tmp;
	return out & 1;
}

ui64 LFSR::getKey(int size)
{
	ui64 out = 0;
	for (int i = 0; i < size; ++i)
	{
		out = out << i | doStep() & 1;
	}
	return out;
}

ui64 LFSR::getState()
{
	return this->_state;
}