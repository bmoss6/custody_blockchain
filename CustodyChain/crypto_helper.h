#pragma once
#include <string>
#include <cstdio>
#include "openssl/sha.h"
#include <iostream>
#include <sstream>
#include "openssl/rsa.h"
#include "openssl/pem.h"
#include "openssl/err.h"

#include "openssl/evp.h"
using namespace std;

class crypto_helper
{
public:
	crypto_helper();
	~crypto_helper();
	static int sha256(string input);
	static string sha256_to_string(string input);
	static pair<EVP_PKEY*, EVP_PKEY*> gen_keys();
	static bool sign(string message, EVP_PKEY *private_key, unsigned char*& sig, size_t *slen);
	static bool verify(string message, unsigned char* sig, size_t siglen, EVP_PKEY *pub_key);
	static string pub_key_to_string(EVP_PKEY *pub_key);
	static bool validate_tx();
	static EVP_PKEY *string_to_pub_key(string pub);
	
};

