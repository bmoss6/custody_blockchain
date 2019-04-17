#include "client.h"
#include <chrono>


client::client(string name, string department)
{
	this->name = name;
	this->department = department;
	pair<EVP_PKEY*, EVP_PKEY*> key_pair = crypto_helper::gen_keys();
	this->private_key = key_pair.first;
	this->public_key = key_pair.second;
}
string client::get_department()
{
	return this->department;
}
string client::get_name()
{
	return this->name;
}

Artifact::ArtifactTransaction client::create_transx(string previous_tx, int index, string to_pubkey)
{
	Artifact::ArtifactTransaction *new_tx = new Artifact::ArtifactTransaction();
	
	TXIO::Output *new_output = new TXIO::Output(to_pubkey);
	unsigned char* sig = NULL;
	size_t slen = 0;
	string message = crypto_helper::sha256_to_string(to_string(index));
	
	crypto_helper::sign(message, this->private_key, sig, &slen);
	string sig_string = string((char *)sig, slen);
	string test_pub = crypto_helper::pub_key_to_string(this->public_key);
	TXIO::Input *new_input = new TXIO::Input(previous_tx, index, sig_string);
	new_tx->add_input(*new_input);
	new_tx->add_output(*new_output);
	return *new_tx;
}

EVP_PKEY* client::get_pub_key()
{
	return this->public_key;

}
Block client::collect_evidence()
{
	
	
	Merkle::MerkleTree *test_tree = new Merkle::MerkleTree();
	test_tree->addInitialEvidence(*test_tree, this->public_key);
	string root_hash = test_tree->formTree();
	chrono::milliseconds ms = chrono::duration_cast<chrono::milliseconds> (chrono::system_clock::now().time_since_epoch());
	Header *new_header = new Header(ms, root_hash, "");
	Block *new_block = new Block();
	new_block->add_artifacts(test_tree->return_transactions());
	new_block->add_header(*new_header);
	this->UTXO = test_tree->return_transactions();
	return *new_block;
}





client::~client()
{
	
}
