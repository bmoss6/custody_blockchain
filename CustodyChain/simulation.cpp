#include "simulation.h"



simulation::simulation()
{
	
	// Create users 
	for (int i = 0; i < 3; i++)
	{
		client *user = new client(to_string(i), to_string(i));
		this->users.push_back(*user);
	}

}


simulation::~simulation()
{
}

TXIO::Output find_output(string hash, int index, vector<Block> blockchain)
{
	for (Block block : blockchain)
	{
		for (Artifact::ArtifactTransaction tx : block.return_artifacts())
		{
			if (tx.get_output().get_hash() == hash)
			{
				return tx.get_output();
			}
		}
	}
	TXIO::Output *null = new TXIO::Output("NULL");
	return *null;
}

int main()
{
	vector<Block> blockchain;
	simulation *new_sim = new simulation();
	// Create the genesis block 
	Block genesis = new_sim->users[0].collect_evidence();
	blockchain.push_back(genesis);
	// Now a user wants to transfer chain of custody to another employee
	vector<Artifact::ArtifactTransaction> new_txs;
	for (int i = 0; i < 5; ++i)
	{
		Artifact::ArtifactTransaction new_tx = new_sim->users[0].create_transx(new_sim->users[0].UTXO[i].get_output().get_hash() , 0, crypto_helper::pub_key_to_string(new_sim->users[2].get_pub_key()));
		TXIO::Output output = find_output(new_tx.get_input().return_prevtx(), new_tx.get_input().return_index(), blockchain);
		if (new_tx.validate_tx(output) == true)
		{
			new_txs.push_back(new_tx);
		}
		
	}
	Block *next_block = new Block();
	next_block->add_artifacts(new_txs);
	next_block->form_block(genesis.return_block_hash());
	blockchain.push_back(*next_block);
	return 0;
}
