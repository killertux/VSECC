//
// Created by clemente on 31/05/18.
//

#include <algorithm>
#include <sstream>
#include <string.h>
#include "EPoint.hpp"
#include "../ECurve/ECurve.hpp"

std::string const EPoint::hex_digits = "0123456789ABCDEF";

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

EPoint::EPoint(ECurve *curve, unsigned char *binary) {
	unsigned char buffer[N_BYTES];
	this->curve = curve;
	this->is_identity = false;
	memcpy(buffer, binary, N_BYTES);
	this->x = NTL::conv<NTL::ZZ_p>(NTL::ZZFromBytes(buffer, N_BYTES));
	memcpy(buffer, binary + N_BYTES, N_BYTES);
	this->y = NTL::conv<NTL::ZZ_p>(NTL::ZZFromBytes(buffer, N_BYTES));
}

std::string EPoint::toString() {
	return EPoint::ZZpToHexString(this->x) + EPoint::ZZpToHexString(this->y);
}

EPoint &EPoint::operator=(const EPoint &a) {
	this->x = a.x;
	this->y = a.y;
	this->curve = a.curve;
	this->is_identity = a.is_identity;
	return (*this);
}


bool EPoint::operator==(const EPoint &a) {
	if ((this->x == a.x && this->y == a.y) ||
			(this->is_identity == true and a.is_identity == true))
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
	if (Q.is_identity)
		return *this;

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

EPoint EPoint::operator-(const EPoint &Q) {
	EPoint minusQ = Q;
	minusQ.y = -Q.y;
	return (*this) + minusQ;
}


EPoint EPoint::operator++() {
	EPoint point;
	point.curve = this->curve;
	NTL::ZZ_p lambda;
	if (this->is_identity)
		return point;
	if (this->y == 0)
		return point;
	point.is_identity = false;
	lambda = 3 * this->x * this->x + this->getCurve()->getA();
	lambda = lambda / (2 * this->y);
	point.x = lambda * lambda  - 2 * this->x;
	point.y = -this->y + lambda * (this->x - point.x);
	return point;
}

EPoint EPoint::operator*(const NTL::ZZ n) {
	EPoint Q;
	Q.curve = this->curve;
	NTL::ZZ m = n;

	for(long i = NTL::NumBits(m) -1; i >= 0; i--) {
		Q = ++Q;
		if(NTL::bit(m, i) == 1) {
			Q = Q + *this;
		}
	}

	return Q;
}

EPoint EPoint::operator*(const int n) {
	NTL::ZZ m(n);
	return (*this) * m;
}

std::string EPoint::ZZpToHexString(NTL::ZZ_p &original_number) {
	std::string hex;
	NTL::ZZ number = NTL::conv<NTL::ZZ>(original_number);

	while (number != 0) {
		auto number_mod_16 = number % 16;
		hex += hex_digits[number_mod_16];
		number /= 16;
	}

	unsigned long i;
	while ((i = hex.size() / 2) < N_BYTES) {
		hex += "0";
	}

	std::reverse(hex.begin(), hex.end());

	return hex;
}

unsigned char * EPoint::toBinary() {
	auto *returner = new unsigned char[N_BYTES * 2];
	unsigned char *x_coordinate = EPoint::ZZpToBinary(this->x);
	unsigned char *y_coordinate = EPoint::ZZpToBinary(this->y);

	memcpy(returner, x_coordinate, N_BYTES);
	memcpy(returner + N_BYTES, y_coordinate, N_BYTES);

	delete [] x_coordinate;
	delete [] y_coordinate;

	return returner;
}

unsigned char * EPoint::ZZpToBinary(NTL::ZZ_p &original_number) {
	auto *returner = new unsigned char[N_BYTES];
	std::string point_string = EPoint::ZZpToHexString(original_number);

	//Little Endian
	for (int i = N_BYTES - 1, j = 0; i >= 0; i--, j += 2) {
		auto upper_nibble = (unsigned char)((point_string[j] - '0' < 10) ? point_string[j] - '0' : (point_string[j] - 'A') + 10);
		auto lower_nibble = (unsigned char)((point_string[j + 1] - '0' < 10) ? point_string[j + 1] - '0' : (point_string[j + 1] - 'A') + 10);
		returner[i] = upper_nibble << 4 | lower_nibble;
	}

	return returner;
}

