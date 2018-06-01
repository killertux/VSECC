//
// Created by clemente on 31/05/18.
//

#include "ECurve.hpp"

ECurve::ECurve() {
	NTL::ZZ prime = NTL::conv<NTL::ZZ>(EC_P);
	NTL::ZZ_p::init(prime);
	this->n = NTL::conv<NTL::ZZ_p>(EC_N);
	this->c = NTL::conv<NTL::ZZ_p>(EC_C);
	this->b = NTL::conv<NTL::ZZ_p>(EC_B);
	this->G = EPoint(this, NTL::conv<NTL::ZZ_p>(EC_GX), NTL::conv<NTL::ZZ_p>(EC_GY));
}
