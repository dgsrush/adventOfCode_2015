#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include<string>
#include<iostream>
#include"cryptopp850/md5.h"
#include"cryptopp850/hex.h"
#include"cryptopp850/files.h"
#include"cryptopp850/aes.h"

using std::string;
using std::cout;
using std::endl;
using namespace CryptoPP;

int main()
{
	string input = "ckczppom";
	//string fnd = "00000";

	HexEncoder encoder(new FileSink(std::cout));

	for(int i = 0; i < 10000000; i++)
	{
		string inp = input + std::to_string(i);
		string digest;

		Weak::MD5 hash;
		hash.Update((const byte*)&inp[0], inp.size());
		digest.resize(hash.DigestSize());
		hash.Final((byte*)&digest[0]);

		cout << inp << " = ";
		StringSource(digest, true, new Redirector(encoder));
		cout << endl;
	}

	//part 1 answer = 117946
	//part 2 answer = 3938038

	return 0;
}
