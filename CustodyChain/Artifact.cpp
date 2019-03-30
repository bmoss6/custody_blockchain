#include "Artifact.h"

Artifact::ArtifactTransaction::ArtifactTransaction()
{

}

bool Artifact::ArtifactTransaction::add_input(TXIO::Input input)
{
	this->inputs.push_back(input);
	this->hash_id = this->serialize();
	return true;
}

bool Artifact::ArtifactTransaction::add_output(TXIO::Output output)
{
	this->outputs.push_back(output);
	this->hash_id = this->serialize();
	return true;
}

string Artifact::ArtifactTransaction::serialize()
{
	stringstream ss;
	for (TXIO::Input input : this->inputs)
	{
		ss << input.get_hash();
	}
	for (TXIO::Output output : this->outputs)
	{
		ss << output.get_hash();
	}
	return crypto_helper::sha256_to_string(ss.str());
}

string Artifact::ArtifactTransaction::get_hash()
{
	return this->hash_id;
}