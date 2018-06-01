//
// Created by clemente on 31/05/18.
//

#ifndef ECC_EXCEPTION_HPP
#define ECC_EXCEPTION_HPP

#include <string>

class Exception {
public:
	Exception(std::string exception_message);

private:
	std::string exception_message;
};


#endif //ECC_EXCEPTION_HPP
