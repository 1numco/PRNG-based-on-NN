#pragma once
#include "own.hpp"
#include "NNH.hpp"

class Generator
{
protected:
	int _keySize;
	std::string _name;
public:
	virtual ui64 getKey() = 0;
	virtual int getKeySize() {return _keySize;}
	virtual std::string getName() { return _name;} 
	virtual void writeSamplesToTextFile(ui64 size, std::string path)
	{
		std::ofstream myfile;
		myfile.open(path);
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
				myfile << "\n" << getKey();
			}
		}
		myfile.close();
	}
	virtual void writeSamplesToBinFile(ui64 size, std::string path)
	{
		std::ofstream myfile(path, std::ios_base::binary|std::ios::out);
		if (myfile.is_open())
		{
			for (int i = 0; i < size; ++i) {
				ui64 value = getKey();
				myfile.write((char*)&value, sizeof(ui32));
			}
		}
		myfile.close();
	}
	virtual ~Generator(){}
};