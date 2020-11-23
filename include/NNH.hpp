#pragma once
#include "own.hpp"

class NNH
{
private:
	ui8 _numNeurons;
	ui64 _vecNeuronState;
	i8 **_widthMatrix;
public:
	NNH();
	NNH(ui8 numNeurons, ui64 vecNeuronState=0, i8 **widthMatrix=nullptr);
	NNH(NNH const& other);
	NNH(NNH && other);
	NNH & operator=(NNH const& other);
	NNH & operator=(NNH && other);
	void setNumNeurons(ui8 N);
	void setVecNeuronState(ui64 state);
	ui8 doStep();
	void generateWeightMatrix();
	ui64 getVecNeuronState();
	void showState();
	void showMatrix();
	void writeMatrixToFile();
	~NNH();
};