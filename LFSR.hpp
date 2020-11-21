#pragma once
#include "own.hpp"

class LFSR
{
private:
	ui8 _size;
	ui64 _state;
	ui64 _coeffPolynom;
public:
	LFSR();
	LFSR(ui8 size, ui64 state, ui64 coeffPolynom);
	LFSR(LFSR const& other);
	LFSR(LFSR && other);
	LFSR & operator=(LFSR const& other);
	LFSR & operator=(LFSR && other);
	~LFSR();
	ui64 getState();
	ui8 doStep();
	ui64 getKey(int size);
	void showState();
	void showPolynom();
};