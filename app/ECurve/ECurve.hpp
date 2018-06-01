//
// Created by clemente on 31/05/18.
//

#ifndef ECC_ELLIPTICCURVE_HPP
#define ECC_ELLIPTICCURVE_HPP

#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include "../EPoint/EPoint.hpp"

//Curve P-192 parameters
//https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.186-4.pdf , pg. 99

#define EC_P  "6277101735386680763835789423207666416083908700390324961279"
#define EC_N  "6277101735386680763835789423176059013767194773182842284081"
#define EC_C  "1191689908718309326471930603292001425137626342642504031845"
#define EC_B  "2455155546008943817740293915197451784769108058161191238065"
#define EC_GX "602046282375688656758213480587526111916698976636884684818"
#define EC_GY "174050332293622031404857552280219410364023488927386650641"

class ECurve {
public:
	ECurve();

	const EPoint &getG() const { return G; }
	const NTL::ZZ_p &getC() const { return c; }
	const NTL::ZZ_p &getN() const { return n; }

	void setG(const EPoint &G) { ECurve::G = G; }
	void setC(const NTL::ZZ_p &c) { ECurve::c = c; }
	void setN(const NTL::ZZ_p &n) { ECurve::n = n; }
	
private:
	NTL::ZZ_p p,n, c, b;
	EPoint G;
};


#endif //ECC_ELLIPTICCURVE_HPP
