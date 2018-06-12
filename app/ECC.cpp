//
// Created by clemente on 31/05/18.
//

#include "ECC.hpp"
#include <NTL/ZZ_p.h>
#include <fstream>
#include <sstream>


unsigned char * ECC::generatePrivateKey() {
	NTL::ZZ_p key = NTL::random_ZZ_p();
	return EPoint::ZZpToBinary(key);
}

unsigned char * ECC::generatePublicKey(unsigned char *private_key) {
	EPoint G = this->curve.getG();
	EPoint public_key = G * NTL::ZZFromBytes(private_key, N_BYTES);
	return public_key.toBinary();
}


void ECC::encrypt(std::ifstream *file, unsigned char *my_public_key,
                  unsigned char *my_private_key,
                  unsigned char *their_public_key) {
	unsigned char buffer;
	NTL::ZZ private_key = NTL::ZZFromBytes(my_private_key, N_BYTES);
	EPoint their_public_key_point(&this->curve, their_public_key);
	EPoint M = their_public_key_point * private_key;

	this->generateASCIIMap();
	std::cout.write((const char *) my_public_key, N_BYTES * 2);
	while (file->read((char*)&buffer, 1)) {
		EPoint byte_point = this->ascii_map[buffer];
		EPoint encrypt = byte_point + M;
		if(encrypt.toString() == "67C1F7D243000B6B3001CA1E73BE9A1E98546561D23392F905DCEB27744482144CC1BCFAB38CF1098F03D2582D496BF0")
			std::cerr << buffer << std::endl;
		unsigned char *result = encrypt.toBinary();
		std::cout.write((const char *) result, N_BYTES * 2);
		delete [] result;
	}
}

void ECC::decrypt(std::ifstream *file, unsigned char *my_private_key) {
	unsigned char buffer[N_BYTES * 2];
	NTL::ZZ private_key = NTL::ZZFromBytes(my_private_key, N_BYTES);
	file->read((char *)buffer, N_BYTES * 2);
	EPoint their_public_key_point(&this->curve, buffer);
	EPoint M = their_public_key_point * private_key;

	this->generateASCIIMap();
	while (file->read((char *)buffer, N_BYTES * 2)) {
		EPoint encrypted_point(&this->curve, buffer);
		EPoint decrypted_point = encrypted_point - M;
		char byte = this->getASCIIFromPoint(decrypted_point);
		std::cout.write(&byte, 1);
	}
}

void ECC::generateASCIIMap() {
	EPoint point(&this->curve), G;
	G = this->curve.getG();
	for(int i = 1; i <= 256; i++) {
		point = G * i;
		this->ascii_map[i - 1] = point;
	}
}

char ECC::getASCIIFromPoint(EPoint &point) {
	for(int i = 0; i < 256; i++) {
		if (this->ascii_map[i] == point)
			return (char)i;
	}
	std::cerr << "A byte was not found!\n";
	return 0;
}

