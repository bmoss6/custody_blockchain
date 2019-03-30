#include "crypto_helper.h"



crypto_helper::crypto_helper()
{
}


crypto_helper::~crypto_helper()
{
}


 string crypto_helper::sha256_to_string(string input)
{
	unsigned char digest[SHA256_DIGEST_LENGTH];
	stringstream s;
	SHA256((unsigned char*)input.c_str(), input.length(), (unsigned char*)&digest);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
	{
		s << hex << int(digest[i]);
	}
	return s.str();
}


 int crypto_helper::sha256(string input)
{
	unsigned char digest[SHA256_DIGEST_LENGTH];
	stringstream s;
	SHA256((unsigned char*)input.c_str(), input.length(), (unsigned char*)&digest);
	for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
	{
		s << int(digest[i]);
	}
	int result;
	s >> result;
	return result;
}