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

 pair<EVP_PKEY*, EVP_PKEY*> crypto_helper::gen_keys()

 {

	 // Lots of help from https://wiki.openssl.org/index.php/EVP_Signing_and_Verifying
	 EVP_PKEY_CTX *ctx;
	 EVP_PKEY *pkey = NULL;

	 ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
	 if (!ctx)
	 {
		 string h = "hi";

	 }
	 /* Error occurred */
	 if (EVP_PKEY_keygen_init(ctx) <= 0)
	 {

	 }
	 /* Error */
	 if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, 2048) <= 0)
	 {

	 }
	 /* Error */

 /* Generate key */
	 if (EVP_PKEY_keygen(ctx, &pkey) <= 0)
	 {
		 cout << "ERROR" << endl;
	 }

	 BIO *bio_private = BIO_new(BIO_s_mem());
	 int fds = PEM_write_bio_PrivateKey(bio_private, pkey, NULL, NULL, 0, NULL, NULL);
	 EVP_PKEY *private_key = PEM_read_bio_PrivateKey(bio_private, NULL, NULL, NULL);
	 BIO *bio_public = BIO_new(BIO_s_mem());
	 int ret = PEM_write_bio_PUBKEY(bio_public, pkey);
	 EVP_PKEY *public_key = PEM_read_bio_PUBKEY(bio_public, NULL, NULL, NULL);

	 pair<EVP_PKEY*, EVP_PKEY*> key_pair = make_pair(private_key, public_key);
	 return key_pair;
 }

 bool crypto_helper::sign(string message, EVP_PKEY *private_key, unsigned char*& sig, size_t *slen)
 {
	 /* Error */
// https://stackoverflow.com/questions/27954979/openssl-fails-at-evp-verifyfinal
	 EVP_MD_CTX *mdctx = NULL;
	 int ret = 0;
	 const char* msg = message.c_str();
	 /* Create the Message Digest Context */
	 mdctx = EVP_MD_CTX_create();
	 /* Initialise the DigestSign operation - SHA-256 has been selected as the message digest function in this example */
	 int t = EVP_DigestSignInit(mdctx, NULL, EVP_sha256(), NULL, private_key);
	 /* Call update with the message */
	 int h = EVP_DigestSignUpdate(mdctx, msg, strlen(msg));

	 /* Finalise the DigestSign operation */
	 /* First call EVP_DigestSignFinal with a NULL sig parameter to obtain the length of the
	  * signature. Length is returned in slen */
	 int b = EVP_DigestSignFinal(mdctx, NULL, slen);
	 /* Allocate memory for the signature based on size in slen */
	 sig = (unsigned char*)OPENSSL_malloc(sizeof(unsigned char) * (*slen));
	 /* Obtain the signature */
	 int i = EVP_DigestSignFinal(mdctx, sig, slen);
	 if (i == 1)
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }

 }
 bool crypto_helper::verify(string message, unsigned char* sig, size_t slen, EVP_PKEY *pub_key)
 {
	 slen = 256;
	 const char* msg = message.c_str();
	 // VERIFY PART
	 EVP_MD_CTX *mdctx = EVP_MD_CTX_create();
	 /* Initialize `key` with a public key */
	 int j = EVP_DigestVerifyInit(mdctx, NULL, EVP_sha256(), NULL, pub_key);

	 /* Initialize `key` with a public key */
	 int e = EVP_DigestVerifyUpdate(mdctx, msg, strlen(msg));

	 int ret = EVP_DigestVerifyFinal(mdctx, sig, slen);

	 /* Clean up */
// if (*sig && !ret) OPENSSL_free(sig);
//	 if (mdctx) EVP_MD_CTX_destroy(mdctx);

	 if (ret == 1)
	 {
		 return true;
	 }
	 else
	 {
		 return false;
	 }
	 
 }

 string crypto_helper::pub_key_to_string(EVP_PKEY *pub_key)
 {
	 BIO *bio_pub;

	 //bio_pub = BIO_new_file("new_pem.pem", "w");
	 bio_pub = BIO_new(BIO_s_mem());
	 char* pp;



	 //	BIO *bio_out;
	 //	bio_out = BIO_new_fp(stdout, BIO_NOCLOSE);
	 int rc = PEM_write_bio_PUBKEY(bio_pub, pub_key);
	 BIO_flush(bio_pub);
	 BIO_get_mem_data(bio_pub, &pp);
	 char *test = &pp[0];
	 string pub_key_string = string(&pp[0], strlen(&pp[0]));
	 return pub_key_string;

 }

 bool crypto_helper::validate_tx()
 {
	 return true;
 }

 EVP_PKEY *crypto_helper::string_to_pub_key(string pub)
 {
	 BIO *bio_pub;
	 bio_pub = BIO_new(BIO_s_mem());
	 int rc =BIO_write(bio_pub, pub.c_str(), strlen(pub.c_str()));
	 EVP_PKEY *pub_key = PEM_read_bio_PUBKEY(bio_pub, NULL, NULL, NULL);
	 return pub_key;
	 
 }

 int maindf()
 {

	 pair<EVP_PKEY*, EVP_PKEY*> pair_1 = crypto_helper::gen_keys();
	 pair<EVP_PKEY*, EVP_PKEY*> pair_2 = crypto_helper::gen_keys();
	 string message = "HOW DO YOU DO";
	 unsigned char* sig = NULL;
	 size_t slen = 0;
	 crypto_helper::sign(message, pair_1.first, sig, &slen);
	 cout << "IS THIS MESSAGE VERIFIED?" << endl;
	 string message_2 = "HDASFADS";
	 bool result = crypto_helper::verify(message_2, sig, slen, pair_1.second);
	 if (result == true)
	 {
		 cout << "TRUE" << endl;
	 }
	 else
	 {
		 cout << "FALSE" << endl;
	 }
	 
	 return 0;
 }

