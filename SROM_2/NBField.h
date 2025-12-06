#pragma once
#pragma once
#include "string"
#include "iostream"
#include <random>
#include <regex>

#include <chrono>

using namespace std;
using namespace std::chrono;

struct NBField
{
protected:
	uint64_t A[2] = { 0 };
	static const int L[225];
public:
	NBField() {};
	NBField(string s);
	NBField operator+(const NBField& B) const;
	NBField operator*(const NBField& B) const;
	NBField& operator=(const NBField& B);
	NBField(const NBField&);
	NBField(NBField&&);
	NBField pov2() const;
	NBField pov(const NBField& B) const;
	NBField pov2_i(int i) const;
	bool BinSyntax(string n);
	void ShowBin() const;
	int High() const;
	int Tr() const;
	bool mult_v(int i, const uint64_t u[2], const uint64_t v[2]) const;
	NBField rev() const;
};

