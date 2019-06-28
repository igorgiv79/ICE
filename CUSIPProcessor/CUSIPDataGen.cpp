
#include "pch.h"
#include <fstream>

class CUSIPDataGen
{
public:
	CUSIPDataGen ();
	~CUSIPDataGen ();

private:

};

CUSIPDataGen::CUSIPDataGen ()
{
}

CUSIPDataGen::~CUSIPDataGen ()
{
}

void GenCUSIPData (unsigned int numCUSIPs, std::string const &name)
{
	std::ofstream of;
	of.exceptions (std::ios::failbit | std::ios::badbit);
	of.open (name.c_str (), std::ios::out | std::ios::trunc);

	for (int i = 0; i < numCUSIPs; ++i) {

	}
}