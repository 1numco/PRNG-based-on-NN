#pragma once
#include "own.hpp"
#include "NNH.hpp"

class Generator
{
public:
	NNH * net;
	virtual ui64 getKey(int size) = 0;
	virtual void writeToFile(ui64 size)
	{
		std::ofstream myfile;
		myfile.open("../generated_samples.txt");
		if (myfile.is_open())
		{
			myfile << "#==================================================================\n";
			myfile << "## generator my_prng  seed = 1\n";
			myfile << "#==================================================================\n";
			myfile << "type: d\n";
			myfile << "count: " << size << "\n";
			myfile << "numbit: 32";
			for (ui64 i = 0; i < size; ++i)
			{
				myfile << "\n" << getKey(32);
			}
		}
		myfile.close();
	}
	virtual ~Generator(){}
};