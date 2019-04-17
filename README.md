**CustodyChain Project**

This project is an initial attempt at constructing the basic features of a blockchain application that could be used to keep track of artifacts in a &quot;chain of custody&quot;. Although a more realistic development would incorporate frameworks like Hyperledger, it was a good exercise to design and implement some of the features. Although there is no client/server distinction in this trivial scenario, implementations of blocks, merkle trees, artifact transactions, and transaction inputs/outputs have been created to service a brief simulation. Additionally, the openssl library was used for the cryptographic functionality. An explanation of the simulation (main function) is as follows:

1. An initial block is created. This could be interpreted as a forensics entity (person/organization) gathering evidence in the form of pictures, samples, etc. These items are digitally represented (through digital picture, bar-code, etc.) and placed in individual artifact transaction outputs. This is similar to a coin creation occurrence in Bitcoin. The output locking script contains the public key of identity that gathered the evidence.
  1. A merkle tree is formed from the transactions in the block and the root hash is provided
  2. The block header is also formed.
2. This identity chooses to transact some of the artifacts to another identity (e.g. send samples to a laboratory, different police station, etc.). This user signs the transactions that specify the originally created artifact outputs as inputs, and the new identity&#39;s public key as the output.
3. If the transaction is verified via the signature on the input and the referenced output&#39;s public key, it is added to a new vector of artifacts. This in turn forms a new block.

Principles Learned:

1. Implementing Bitcoin data structures: merkle tree, hash pointer, transactions, blocks.
2. Using cryptographic libraries to verify signatures, hashing, etc.
3. Better appreciating the complexity of cryptocurrencies and blockchain applications in general.
