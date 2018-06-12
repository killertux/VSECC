//
// Created by clemente on 31/05/18.
//

#ifndef ECC_ELLIPTICCURVE_HPP
#define ECC_ELLIPTICCURVE_HPP

#include <iostream>
#include <NTL/ZZ.h>
#include <NTL/ZZ_p.h>
#include "../EPoint/EPoint.hpp"

//Curve secp192k1 parameters
//http://www.secg.org/sec2-v2.pdf , pg. 10

#define EC_P  "6277101735386680763835789423207666416102355444459739541047"
#define EC_N  "6277101735386680763835789423061264271957123915200845512077"
#define EC_A  "0"
#define EC_B  "3"
#define EC_GX "5377521262291226325198505011805525673063229037935769709693"
#define EC_GY "3805108391982600717572440947423858335415441070543209377693"
#define N_BYTES 24

class ECurve {
public:
	ECurve();

	const EPoint &getG() const { return G; }
	const NTL::ZZ_p &getA() const { return a; }
	const NTL::ZZ_p &getN() const { return n; }

	void setG(const EPoint &G) { ECurve::G = G; }
	void setA(const NTL::ZZ_p &c) { ECurve::a = c; }
	void setN(const NTL::ZZ_p &n) { ECurve::n = n; }
	
private:
	NTL::ZZ_p p,n, a, b;
	EPoint G;
};


#endif //ECC_ELLIPTICCURVE_HPP
