//
// Created by clemente on 31/05/18.
//

#ifndef ECC_ECC_HPP
#define ECC_ECC_HPP

#include <string>
#include "ECurve/ECurve.hpp"

class ECC {
public:
	std::string generatePrivateKey();
	std::string generatePublicKey(std::string private_key);
private:
	ECurve curve;
};


#endif //ECC_ECC_HPP
