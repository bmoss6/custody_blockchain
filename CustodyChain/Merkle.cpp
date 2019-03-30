#include "Merkle.h"

using namespace Merkle;
using namespace std;


HashPointer::HashPointer()
{
	this->hash = "";
	this->parent = NULL;
	
}
Merkle::MerkleTree::MerkleTree()
{
	HashPointer root = HashPointer::HashPointer();
	this->root = &root;
}

bool Merkle::MerkleTree::addTransaction(Artifact::ArtifactTransaction tx)
{
	this->transactions.push_back(tx);
	return true;
}

string Merkle::MerkleTree::formTree()
{
	// Uses the tx vector to form a merkle tree from the base up. 

	// First check to make sure length of transactions is even 

	int transx_size = this->transactions.size();
	if (transx_size % 2 != 0)
	{
		Artifact::ArtifactTransaction to_add = this->transactions[0];
		this->transactions.push_back(to_add);
	}

	// Create bottom level of hash pointers for all transactions
	vector<HashPointer> base_level;

	for (Artifact::ArtifactTransaction artifact : this->transactions)
	{
		HashPointer new_hash = HashPointer();
		new_hash.set_hash(artifact.get_hash());
		base_level.push_back(new_hash);
	}

	string root_hash = this->r_formTree(base_level);

	// Now start from bottom up by creating leaf nodes, hashing, and working up to form tree
	
	return root_hash;
	// Take pairs of transactions and form hash pointer 

}

bool Merkle::MerkleTree::verify()
{
	return false;
}

string Merkle::MerkleTree::r_formTree(std::vector<HashPointer> hash_level )
{
	//For each pair of pointers in the list, make a new hash pointer and add to level vector
	// Base case is if the hash level list is length 1, then we've reached the top of the tree.
	if (hash_level.size() == 1)
	{
		return hash_level[0].get_hash();
	}
	



		vector<HashPointer> new_level;
		for (int x = 0; x < hash_level.size()-1; x += 2)
		{
			// Get a pair of hash pointers
			stringstream ss;
			ss << hash_level[x].get_hash();
			ss << hash_level[x + 1].get_hash();
			// Create new hash pointer
			HashPointer new_hash =  HashPointer();
			new_hash.set_hash(ss.str());
			new_level.push_back(new_hash);
		}

		return r_formTree(new_level);
		

}



string Merkle::HashPointer::get_hash()
{
	return this->hash;
}

string Merkle::HashPointer::set_hash(string hash)
{
	this->hash = hash;
	return this->hash;
}

void addInitialEvidence(MerkleTree &tree)
{
	// Should add 20 transactions to the merkle tree's tx vector. This represents initial evidence being gathered at
	// a collection site. 
	for (int i = 0; i < 4; i++)
	{
		Artifact::ArtifactTransaction artifact = Artifact::ArtifactTransaction::ArtifactTransaction();
		TXIO::Output output = TXIO::Output::Output("Test"+to_string(i));
		artifact.add_output(output);
		tree.addTransaction(artifact);
	}
}

int main() 
{
	MerkleTree test_tree;
	addInitialEvidence(test_tree);
	string root_hash = test_tree.formTree();
	return 0;
}