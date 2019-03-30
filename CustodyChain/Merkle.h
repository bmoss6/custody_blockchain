#pragma once
#include <string>
#include "Artifact.h"
#include <vector>
#include <iostream>
#include <sstream>
#include "crypto_helper.h"


namespace Merkle
{
	class HashPointer
	{
	public:
		HashPointer();
		string get_hash();
		string set_hash(string hash);
		
	private:
		string hash;
		HashPointer* parent;

	};

	class MerkleTree
	{
	public:
		MerkleTree();
		bool addTransaction(Artifact::ArtifactTransaction tx);
		string formTree();
		string r_formTree(std::vector<HashPointer> hash_level);
		bool verify();

	private:
		HashPointer* root;
		std::vector<Artifact::ArtifactTransaction> transactions; 
	};


}