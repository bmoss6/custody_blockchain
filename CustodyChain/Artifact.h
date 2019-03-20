#pragma once
#include <stdlib.h>
#include "TXIO.h"
#include <vector>
#include <string>
namespace Artifact
{
	class ArtifactTransaction
	{
	public:
		ArtifactTransaction();
		bool add_input(TXIO::Input input);
		bool add_output(TXIO::Output output);

	private:
		std::vector<TXIO::Input> inputs;
		std::vector<TXIO::Output> outputs;
		std::string hash_id;



	};


}