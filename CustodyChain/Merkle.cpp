#include "Merkle.h"

using namespace Merkle;
using namespace std;




bool Merkle::MerkleTree::addTransaction(Artifact::ArtifactTransaction tx)
{
	this->transactions.push_back(tx);
}

string Merkle::MerkleTree::formTree()
{
	// Uses the tx vector to form a merkle tree from the base up. 

	// First check to make sure length of transactions is even 

	if (this->transactions.size % 2 != 0)
	{
		this->transactions.push_back(this->transactions[this->transactions.size - 1]);
	}

	// Take pairs of transactions and form hash pointer 

}