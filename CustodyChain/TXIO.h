#pragma once
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include "crypto_helper.h"
using namespace std;
namespace TXIO
{
	class Input
	{
	public:
		Input(std::string previous_tx, int index, std::string scriptsig);
		string return_hash();
		string get_hash();
		int return_index();
		string return_prevtx();
		string return_scriptsig();
	private:
		std::string previous_tx;
		int index;
		std::string scriptsig;
		string hash;
	};

	class Output
	{
	public:
		Output(std::string scriptpubkey);
		string return_hash();
		string get_hash();
		string return_scriptpubkey();
	private:
		std::string scriptpubkey;
		string hash;
		

	};

}