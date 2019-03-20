#pragma once
#include <string>
#include "Artifact.h"
#include <vector>
#include <openssl>
namespace Merkle
{
	class HashPointer
	{
	private:
		string hash;
		HashPointer& parent;

	};

	class MerkleTree
	{
	public:
		MerkleTree();
		bool addTransaction(Artifact::ArtifactTransaction tx);
		string formTree();
		bool verify();

	private:
		HashPointer& root;
		std::vector<Artifact::ArtifactTransaction> transactions; 
	};


}