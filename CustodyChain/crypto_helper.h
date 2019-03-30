#pragma once
#include <string>
#include <cstdio>
#include "openssl/sha.h"
#include <iostream>
#include <sstream>
using namespace std;
class crypto_helper
{
public:
	crypto_helper();
	~crypto_helper();
	static int sha256(string input);
	static string sha256_to_string(string input);
};

