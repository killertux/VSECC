//
// Created by clemente on 31/05/18.
//

#include "ECC.hpp"
#include <NTL/ZZ_p.h>
#include <sstream>

std::string ECC::generatePrivateKey() {
	std::stringstream returner;
	returner << NTL::random_ZZ_p();
	return returner.str();
}

std::string ECC::generatePublicKey(std::string private_key) {
	std::stringstream returner;
	EPoint G = this->curve.getG();
	EPoint public_key = G * NTL::conv<NTL::ZZ>(private_key.c_str());
	returner << public_key.getX() << "," << public_key.getY() << std::endl;
	return returner.str();
}
