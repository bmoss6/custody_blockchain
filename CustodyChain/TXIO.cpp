#include "TXIO.h"
#include <string>

using namespace TXIO; 


TXIO::Input::Input(std::string previous_tx, int index, std::string scriptsig)
{
	this->previous_tx = previous_tx;
	this->index = index;
	this->scriptsig = scriptsig;
	this->hash = this->return_hash();
}

TXIO::Output::Output(std::string scriptpubkey)
{
	this->scriptpubkey = scriptpubkey;
	this->hash = this->return_hash();
}


string TXIO::Input::return_hash()
{
	return crypto_helper::crypto_helper::sha256_to_string(this->previous_tx + to_string(this->index) + this->scriptsig);
}

string TXIO::Output::return_hash()
{
	return crypto_helper::crypto_helper::sha256_to_string(this->scriptpubkey);
}

string TXIO::Input::get_hash()
{
	return this->hash;
}

string TXIO::Output::get_hash()
{
	return this->hash;
}