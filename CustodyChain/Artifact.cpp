#include "Artifact.h"

Artifact::ArtifactTransaction::ArtifactTransaction()
{

}

bool Artifact::ArtifactTransaction::add_input(TXIO::Input input)
{
	this->inputs.push_back(input);
}

bool Artifact::ArtifactTransaction::add_output(TXIO::Output output)
{
	this->outputs.push_back(output);
}