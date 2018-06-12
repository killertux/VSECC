//
// Created by clemente on 31/05/18.
//

#ifndef ECC_ECC_HPP
#define ECC_ECC_HPP

#include <string>
#include <map>
#include "ECurve/ECurve.hpp"

class ECC {
public:
	unsigned char * generatePrivateKey();
	unsigned char * generatePublicKey(unsigned char *private_key);
	void encrypt(std::ifstream *file,
	             unsigned char *my_public_key,
	             unsigned char *my_private_key,
	             unsigned char *their_public_key);

	void decrypt(std::ifstream *file, unsigned char *my_private_key);

private:
	ECurve curve;
	EPoint ascii_map[256];

	void generateASCIIMap();
	char getASCIIFromPoint(EPoint &point);
};


#endif //ECC_ECC_HPP
