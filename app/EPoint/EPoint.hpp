//
// Created by clemente on 31/05/18.
//

#ifndef ECC_EPOINT_HPP
#define ECC_EPOINT_HPP

#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include <string>
#include "../Exception/Exception.hpp"

class ECurve;

class EPoint {
public:
	EPoint();
	EPoint(ECurve *curve);
	EPoint(NTL::ZZ_p x, NTL::ZZ_p y);
	EPoint(ECurve *curve, NTL::ZZ_p x, NTL::ZZ_p y);
	EPoint(ECurve *curve, unsigned char *binary);

	static std::string ZZpToHexString(NTL::ZZ_p &original_number);
	static unsigned char * ZZpToBinary(NTL::ZZ_p &original_number);

	std::string toString();
	unsigned char * toBinary();

	const NTL::ZZ_p &getX() const { return x; }
	const NTL::ZZ_p &getY() const { return y; }

	void setX(const NTL::ZZ_p &x) { EPoint::x = x; }
	void setY(const NTL::ZZ_p &y) { EPoint::y = y; }

	const bool identity() const { return is_identity; }

	ECurve *getCurve() const {
		if (curve == NULL)
			throw Exception("No curve setted for point!");
		return curve;
	}

	void setCurve(ECurve *curve) { EPoint::curve = curve; }

	//Operator Overload

	EPoint &operator=(const EPoint &a);
	bool operator==(const EPoint &a);
	EPoint operator+(const EPoint &Q);
	EPoint operator-(const EPoint &Q);
	EPoint operator*(const NTL::ZZ n);
	EPoint operator*(const int n);
	//This operator is being used as point doubling (P+P)
	EPoint operator++();

private:
	ECurve *curve;
	NTL::ZZ_p x;
	NTL::ZZ_p y;
	bool is_identity;

	static const std::string hex_digits;
};


#endif //ECC_EPOINT_HPP
