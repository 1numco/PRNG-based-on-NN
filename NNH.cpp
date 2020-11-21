#include "NNH.hpp"

NNH::NNH() : _numNeurons(0),
			 _vecNeuronState(0),
			 _widthMatrix(nullptr)
			 {}

NNH::NNH(ui8 numNeurons, ui64 vecNeuronState, i8 **widthMatrix) : _numNeurons(numNeurons), 
																   _vecNeuronState(vecNeuronState), 
																   _widthMatrix(widthMatrix) 
																   {}

NNH::NNH(NNH const& other) : _numNeurons(other._numNeurons), _vecNeuronState(other._vecNeuronState), _widthMatrix(new i8 *[_numNeurons])
{
	for (int i = 0; i < _numNeurons; ++i)
		_widthMatrix[i] = new i8[_numNeurons];
	for (int i = 0; i < _numNeurons; ++i)
		for (int j = 0; j < _numNeurons; ++j)
			_widthMatrix[i][j] = other._widthMatrix[i][j];
}

NNH::NNH(NNH && other) : _numNeurons(other._numNeurons), _vecNeuronState(other._vecNeuronState), _widthMatrix(other._widthMatrix)
{
	other._numNeurons = 0;
	other._vecNeuronState = 0;
	other._widthMatrix = nullptr;
}

NNH & NNH::operator=(NNH const& other)
{
	if (this != &other)
	{
		for (int i = 0; i < this->_numNeurons; ++i)
			delete[] _widthMatrix[i];
		delete _widthMatrix;
		_numNeurons = other._numNeurons;
		_vecNeuronState = other._vecNeuronState;
		_widthMatrix = new i8 *[_numNeurons];
		for (int i = 0; i < _numNeurons; ++i)
			_widthMatrix[i] = new i8[_numNeurons];
		for (int i = 0; i < _numNeurons; ++i)
			for (int j = 0; j < _numNeurons; ++j)
				_widthMatrix[i][j] = other._widthMatrix[i][j];
	}
	return *this;
}

NNH & NNH::operator=(NNH && other)
{
	for (int i = 0; i < this->_numNeurons; ++i)
		delete[] _widthMatrix[i];
	delete _widthMatrix;
	_numNeurons = other._numNeurons;
	_vecNeuronState = other._vecNeuronState;
	_widthMatrix = other._widthMatrix;
	other._numNeurons = 0;
	other._vecNeuronState = 0;
	other._widthMatrix = nullptr;
	return *this;
}

uint8_t NNH::doStep() {
	uint64_t tmp = 0;
	uint64_t preTmp = 1;
	uint64_t prePreTmp = 1;
	/*while (preTmp != tmp || tmp != prePreTmp)
	{
		prePreTmp = preTmp;*/
	for (int i = 0; i < this->_numNeurons; ++i)
	{
		int sum = 0;
		for (int j = 0; j < this->_numNeurons; ++j)
		{
			sum += (_widthMatrix[i][j] * ((_vecNeuronState >> (_numNeurons - j - 1)) & 1));
		}
		tmp = tmp << 1;
		if (sum > 0)
			tmp = tmp | 1;
		else
			if (sum <= 0)
				tmp = tmp | 0;
			else
				tmp = tmp | ((_vecNeuronState >> (_numNeurons - i - 1)) & 1);
		//tmp = tmp | ((sum >= 0) ? 1 : 0);
	}
	/*preTmp = this->vecNeuronState;
	this->vecNeuronState = tmp;
}*/
	return (tmp & 1) ^ ((tmp >> (_numNeurons - 1)) & 1) ^ ((tmp >> (_numNeurons - 1) / 2) & 1);
}


void NNH::showState()
{
	switch (this->_numNeurons)
	{
	case 8: std::cout << std::bitset<1 * CHAR_BIT>(_vecNeuronState) << std::endl;
		break;
	case 16: std::cout << std::bitset<2 * CHAR_BIT>(_vecNeuronState) << std::endl;
		break;
	case 32: std::cout << std::bitset<4 * CHAR_BIT>(_vecNeuronState) << std::endl;
		break;
	case 64: std::cout << std::bitset<8 * CHAR_BIT>(_vecNeuronState) << std::endl;
		break;
	}
}


void NNH::showMatrix()
{
	for (int i = 0; i < _numNeurons; ++i)
	{
		for (int j = 0; j < _numNeurons; ++j)
			if (_widthMatrix[i][j] == -1)
				std::cout << (int)_widthMatrix[i][j] << "  ";
			else
				std::cout << (int)_widthMatrix[i][j] << "   ";
		std::cout << std::endl << std::endl;
	}

}


NNH::~NNH()
{
	for (int i = 0; i < _numNeurons; ++i)
		delete[] _widthMatrix[i];
	delete _widthMatrix;
}

uint64_t NNH::getVecNeuronState()
{
	return this->_vecNeuronState;
}

void NNH::generateWeightMatrix()
{
	ui8 sum = 0;
	ui8 countZero = 0;
	ui8 tmp1 = 0;
	ui8 tmp2 = 0;
	std::vector<i8> rowMatrix(_numNeurons);
	std::iota(rowMatrix.begin(), rowMatrix.end(), 0);
	_widthMatrix = new i8 *[_numNeurons];
	for (int i = 0; i < _numNeurons; ++i)
		_widthMatrix[i] = new i8[_numNeurons];
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib;
	for (int i = 0; i < _numNeurons; ++i)
	{
		bool f = false;
		while(!f)
		{
			/*for (int j = 0; j < _numNeurons; ++j)
			{
				if (i != j)
				{
					std::uniform_int_distribution<> distrib(0, 1);

					_widthMatrix[i][j] = distrib(gen);
					if (!_widthMatrix[i][j])
						_widthMatrix[i][j] = -1;
					sum += _widthMatrix[i][j];
				}
			}
			std::uniform_int_distribution<> distrib1(0, _numNeurons - 1);
			tmp1 = distrib1(gen);
			tmp2 = distrib1(gen);
			if ((sum == 0) && (countZero == 2))
				f = true;
			countZero = 0;*/

			std::random_shuffle(rowMatrix.begin(), rowMatrix.end());
			for (int j = 0; j < _numNeurons / 2; ++j)
			{
				_widthMatrix[i][rowMatrix[j]] = 1;
			}
			for (int j = _numNeurons / 2; j != _numNeurons; ++j)
			{
				_widthMatrix[i][rowMatrix[j]] = -1;
			}

			distrib = std::uniform_int_distribution<>(0, _numNeurons / 2 - 1);
			tmp1 = distrib(gen);
			_widthMatrix[i][tmp1] = 0;
			distrib = std::uniform_int_distribution<>(_numNeurons / 2, _numNeurons - 1);
			tmp2 = distrib(gen);
			_widthMatrix[i][tmp2] = 0;
			if (_widthMatrix[i][i] == 1)
			{
				f = true;
			}
				
		}
		
	}
}

void NNH::writeMatrixToFile()
{
	std::ofstream myfile;
	myfile.open("C:\\Users\\vtroynya\\source\\repos\\new_sci_work\\new_sci_work\\widthMatrix.txt");
	if (myfile.is_open())
	{
		for (int i = 0; i < _numNeurons; ++i)
		{
			for (int j = 0; j < _numNeurons; ++j)
			{
				myfile << (int)_widthMatrix[i][j] << " ";
			}
			myfile << "\n";
		}
	}
	myfile.close();
}

void NNH::setNumNeurons(ui8 N)
{
	_numNeurons = N;
}

void NNH::setVecNeuronState(ui64 state)
{
	_vecNeuronState = state;
}