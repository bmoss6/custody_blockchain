#pragma once
#include <string>
#include <cstdlib>
#include <stdlib.h>
using namespace std;
namespace TXIO
{
	class Input
	{
	public:
		Input(std::string previous_tx, int index, std::string scriptsig);
	private:
		std::string previous_tx;
		int index;
		std::string scriptsig;
	};

	class Output
	{
	public:
		Output(std::string scriptpubkey);
	private:
		std::string scriptpubkey;

	};

}