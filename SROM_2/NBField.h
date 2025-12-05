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
	int* zsuvL(int i);
	int* zsuvR(int i);
	NBField(const NBField&);
	NBField(NBField&&);
	NBField pov2() const;
	bool BinSyntax(string n);
	void ShowBin() const;
	int High() const;
	int Tr() const;
};

