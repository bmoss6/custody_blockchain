#pragma once
#include "crypto_helper.h"
#include "block.h"
#include "Merkle.h"
#include "Artifact.h"
class client
{
public:
	client(string name, string department);
	~client();
	string get_name();
	string get_department();
	Block collect_evidence();
	vector<Artifact::ArtifactTransaction> UTXO;
	Artifact::ArtifactTransaction create_transx(string previous_tx, int index, string to_pubkey);
	EVP_PKEY *get_pub_key();

private:
	EVP_PKEY *private_key;
	EVP_PKEY *public_key;
	string name;
	string department;
};

