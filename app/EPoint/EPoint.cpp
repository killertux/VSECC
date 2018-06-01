//
// Created by clemente on 31/05/18.
//

#include "EPoint.hpp"
#include "../ECurve/ECurve.hpp"

EPoint::EPoint() {
	this->curve = NULL;
	this->x = 0;
	this->y = 0;
	this->is_identity = true;
}

EPoint::EPoint(ECurve *curve) {
	this->curve = curve;
	this->x = 0;
	this->y = 0;
	this->is_identity = true;
}

EPoint::EPoint(NTL::ZZ_p x, NTL::ZZ_p y) {
	this->curve = NULL;
	this->x = x;
	this->y = y;
	this->is_identity = false;
}

EPoint::EPoint(ECurve *curve, NTL::ZZ_p x, NTL::ZZ_p y) {
	this->curve = curve;
	this->x = x;
	this->y = y;
	this->is_identity = false;
}

EPoint &EPoint::operator=(const EPoint &a) {
	this->x = a.x;
	this->y = a.y;
	this->curve = a.curve;
	this->is_identity = a.is_identity;
	return (*this);
}


bool EPoint::operator==(const EPoint &a) {
	if (this->x == a.x && this->y == a.y)
		return true;
	return false;
}

EPoint EPoint::operator+(const EPoint &Q) {
	EPoint point;
	NTL::ZZ_p lambda;
	point.curve = this->curve;
	if(this->curve != Q.curve)
		throw Exception("Can't add points from different curves");
	if (this->is_identity)
		return Q;
	if (Q.is_identity) {
		point = (*this);
		return point;
	}

	// P + P ?
	if((*this) == Q) {
		return ++(*this);
	} else {
		lambda = Q.x - this->x;
		if (lambda == 0)
			return point;
		lambda = (Q.y - this->y) / lambda;
		point.x = lambda * lambda - this->x - Q.x;
		point.y = -this->y + lambda * (this->x - point.x);
	}
	point.is_identity = false;
	return point;
}

EPoint &EPoint::operator++() {
	EPoint point;
	NTL::ZZ_p lambda;
	if (this->is_identity)
		return *this;
	if (this->y == 0)
		return *this;

	lambda = 3 * this->x * this->x + this->getCurve()->getC();
	lambda = lambda / (2 * this->y);
	point.x = lambda * lambda  - 2 * this->x;
	point.y = -this->y + lambda * (this->x - point.x);
	*this = point;
	return *this;
}

EPoint EPoint::operator*(const NTL::ZZ n) {
	EPoint point;
	point.curve = this->curve;
	if (n == 0)
		return point;
	if (n == 1) {
		point = (*this);
		return point;
	}

	point = (*this);
	for (NTL::ZZ i(0); i < n; i++)
		point = point + point;
	return point;
}

/*EPoint EPoint::operator*(const NTL::ZZ n) {
	EPoint R;
	EPoint Q = *this;
	NTL::ZZ m = n;

	while(m > 0) {
		if (NTL::AddMod(m, NTL::ZZ(0), NTL::ZZ(2)) == 1)
			R = R + Q;
		++Q;
		m /= 2;
	}
	return R;
}*/

EPoint EPoint::operator*(const int n) {
	NTL::ZZ m(n);
	return (*this) * m;
}



