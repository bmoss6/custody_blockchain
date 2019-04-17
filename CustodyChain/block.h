#pragma once
#include <string>
#include <stdlib.h>
#include "Merkle.h"
#include <chrono>


class Header
{
public:
	Header(chrono::milliseconds timestamp, string merkle_hash, string previous_block_hash);
	Header();
	string return_hash();
	~Header();
	

private:
	chrono::milliseconds timestamp;
	string merkle_hash;
	string previous_block_hash;
};


class Block
{
public:
	Block();
	void add_header(Header header);
	void add_artifacts(vector<Artifact::ArtifactTransaction> artifacts);
	void form_block(string prev_block);
	vector<Artifact::ArtifactTransaction> return_artifacts();
	string return_block_hash();
	
	

	~Block();

private:
	Header header;
	vector<Artifact::ArtifactTransaction> artifacts;
	string block_hash;
};



