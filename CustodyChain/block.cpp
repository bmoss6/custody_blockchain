#include "block.h"



Block::Block()
{

}
void Block::add_header(Header header)
{
	this->header = header;
}

Block::~Block()
{

}
string Block::return_block_hash()
{
	return this->header.return_hash();
}
void Block:: add_artifacts(vector<Artifact::ArtifactTransaction> artifacts)
{
	this->artifacts = artifacts;
}
void Block::form_block(string prev_block)
{
	Merkle::MerkleTree *test_tree = new Merkle::MerkleTree();
	for (Artifact::ArtifactTransaction i : this->artifacts)
	{
		test_tree->addTransaction(i);
	}
	string root_hash = test_tree->formTree();
	chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds> (chrono::system_clock::now().time_since_epoch());
	Header *new_header = new Header(ms, root_hash, prev_block);
	this->add_header(*new_header);
	
}

vector <Artifact::ArtifactTransaction>  Block::return_artifacts()
{
	return this->artifacts;
}
Header::Header()
{

}
Header::Header(chrono::milliseconds timestamp, string merkle_hash, string previous_block_hash)
{
	this->merkle_hash = merkle_hash;
	this->previous_block_hash = previous_block_hash;
	this->timestamp = timestamp;
}

string Header::return_hash()
{
	return crypto_helper::sha256_to_string(this->merkle_hash + this->previous_block_hash + to_string(this->timestamp.count()));
}

Header::~Header()
{

}
