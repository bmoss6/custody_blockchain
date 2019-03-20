#include "TXIO.h"
#include <string>

using namespace TXIO; 


TXIO::Input::Input(std::string previous_tx, int index, std::string scriptsig)
{
	this->previous_tx = previous_tx;
	this->index = index;
	this->scriptsig = scriptsig;
}

TXIO::Output::Output(std::string scriptpubkey)
{
	this->scriptpubkey = scriptpubkey;
}