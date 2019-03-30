#pragma once
#include <stdlib.h>
#include "TXIO.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "crypto_helper.h"
namespace Artifact
{
	class ArtifactTransaction
	{
	public:
		ArtifactTransaction();
		bool add_input(TXIO::Input input);
		bool add_output(TXIO::Output output);
		string get_hash();
		string serialize();

	private:
		std::vector<TXIO::Input> inputs;
		std::vector<TXIO::Output> outputs;
		std::string hash_id;



	};


}