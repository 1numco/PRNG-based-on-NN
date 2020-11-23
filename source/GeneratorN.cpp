#include "GeneratorN.hpp"

GeneratorN::GeneratorN()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 0.1);
	for (int i = 0; i < 100; ++i)
		_vecNeuronState[i] = dis(gen);
	dis = std::uniform_real_distribution<>(0.05, 0.1);
	for (int i = 0; i < 100; ++i)
		_widthMatrix[i][i] = dis(gen);
	dis = std::uniform_real_distribution<>(0.001, 0.01);
	for (int i = 0; i < 100; ++i)
		for (int j = i + 1; j < 100; ++j)
			_widthMatrix[i][j] = dis(gen);
	dis = std::uniform_real_distribution<>(-0.01, -0.001);
	for (int i = 1; i < 100; ++i)
		for (int j = 0; j < i; ++j)
			_widthMatrix[i][j] = dis(gen);
	_isFirstIteration = true;
}

GeneratorN::GeneratorN(GeneratorN const& other)
{
	for (int i = 0; i < 100; ++i)
		_vecNeuronState[i] = other._vecNeuronState[i];
	for (int i = 0; i < 100; ++i)
		for (int j = 0; j < 100; ++j)
			_widthMatrix[i][j] = other._widthMatrix[i][j];
}

GeneratorN::GeneratorN(GeneratorN && other)
{
	for (int i = 0; i < 100; ++i)
	{
		_vecNeuronState[i] = other._vecNeuronState[i];
		other._vecNeuronState[i] = 0.0;
	}
		
	for (int i = 0; i < 100; ++i)
		for (int j = 0; j < 100; ++j)
		{
			_widthMatrix[i][j] = other._widthMatrix[i][j];
			other._widthMatrix[i][j] = 0.0;
		}
}

GeneratorN & GeneratorN::operator=(GeneratorN const& other)
{
	if (this != &other)
	{
		for (int i = 0; i < 100; ++i)
			_vecNeuronState[i] = other._vecNeuronState[i];
		for (int i = 0; i < 100; ++i)
			for (int j = 0; j < 100; ++j)
				_widthMatrix[i][j] = other._widthMatrix[i][j];
	}
	return *this;
}

GeneratorN & GeneratorN::operator=(GeneratorN && other)
{
	for (int i = 0; i < 100; ++i)
	{
		_vecNeuronState[i] = other._vecNeuronState[i];
		other._vecNeuronState[i] = 0.0;
	}

	for (int i = 0; i < 100; ++i)
		for (int j = 0; j < 100; ++j)
		{
			_widthMatrix[i][j] = other._widthMatrix[i][j];
			other._widthMatrix[i][j] = 0.0;
		}
	return *this;
}

ui64 GeneratorN::getKey(int size) 
{
	ui64 out = 0;
	double Enew = 0;
	double Eold = 0;
	double tmp[100] = { 0 };
	while (abs(abs(Eold) - abs(Enew)) < 0.00001)
	{
		for (int i = 0; i < 100; ++i)
		{
			double sum = 0;
			for (int j = 0; j < 100; ++j)
			{
				sum += _widthMatrix[i][j] * _vecNeuronState[i];
			}
			if (_isFirstIteration)
				sum += 1;
			tmp[i] = tanh(sum);
		}
		for (int i = 0; i < 100; ++i)
		{
			for (int j = 0; j < 100; ++j)
			{
				Eold += _widthMatrix[i][j] * _vecNeuronState[i] * _vecNeuronState[j];
				Enew += _widthMatrix[i][j] * tmp[i] * tmp[j];
			}
		}
		Eold *= -0.5;
		Enew *= -0.5;
		for (int i = 0; i < 100; ++i)
			_vecNeuronState[i] = tmp[i];
		_isFirstIteration = false;
	}
	int tmp_size = 0;
	int i = 0;
	while (tmp_size < size - 3)
	{
		ui8 dig = (i64)(_vecNeuronState[i] * 10000000000) % 10;
		if (dig < 8)
		{
			out = (out << 3) | (dig & 7);
			tmp_size += 3;
		}
		i++;
	}
	while (tmp_size != 0)
	{
		ui8 dig = (i64)(_vecNeuronState[i] * 10000000000) % 10;
		if (dig < 8)
		{
			out = (out << (size - tmp_size)) | (dig & int(pow(2, size - tmp_size) - 1));
			tmp_size = 0;
		}
		i++;
	}
	_isFirstIteration = true;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0.0, 0.1);
	for (int i = 0; i < 100; ++i)
		_vecNeuronState[i] = dis(gen);
	return out;
}


void GeneratorN::showState()
{
	for (int i = 0; i < 6; ++i)
		std::cout << rintf(_vecNeuronState[i] * 10000) / 10000 << " ";
	std::cout << "... ";
	std::cout << rintf(_vecNeuronState[99] * 10000) / 10000 << std::endl;
}


void GeneratorN::showMatrix()
{
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 6; ++j)
			if (_widthMatrix[i][j] < 0)
				std::cout << rintf(_widthMatrix[i][j] * 10000) / 10000 << "  ";
			else
				std::cout << rintf(_widthMatrix[i][j] * 10000) / 10000 << "   ";
		std::cout << ".....   ";
		std::cout << rintf(_widthMatrix[i][99] * 10000) / 10000 << std::endl;
	}
	std::cout << ".....    .....    .....    .....    .....    .....    .....    ....." << std::endl;
	for (int i = 0; i < 6; ++i)
		std::cout << rintf(_widthMatrix[99][i] * 10000) / 10000 << "  ";
	std::cout << ".....  ";
	std::cout << rintf(_widthMatrix[99][99] * 10000) / 10000 << std::endl;

}


GeneratorN::~GeneratorN()
{}