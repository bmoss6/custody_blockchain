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
		bool validate_tx(TXIO::Output output);
		TXIO::Input get_input();
		TXIO::Output get_output();

	private:
		std::vector<TXIO::Input> inputs;
		std::vector<TXIO::Output> outputs;
		std::string hash_id;



	};


}