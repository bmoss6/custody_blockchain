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

bool Artifact::ArtifactTransaction::validate_tx(TXIO::Output output)
{
	stringstream tokens(output.return_scriptpubkey());
	string test;
	vector<string> toks;
	while (getline(tokens, test, '|'))
	{
		toks.push_back(test);
	}
	// Form Message
	string message = crypto_helper::sha256_to_string(to_string(0));
	EVP_PKEY *pkey = crypto_helper::string_to_pub_key(toks[1]);
	crypto_helper::verify(message, (unsigned char*)this->get_input().return_scriptsig().c_str(), size(this->get_input().return_scriptsig()), pkey);
	return true;
}

TXIO::Input Artifact::ArtifactTransaction::get_input()
{
	return this->inputs[0];
}


TXIO::Output Artifact::ArtifactTransaction::get_output()
{
	return this->outputs[0];
}