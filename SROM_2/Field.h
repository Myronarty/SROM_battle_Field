#pragma once
#include "string"
#include "iostream"
#include <random>
#include <regex>

#include <chrono>

using namespace std;
using namespace std::chrono;

struct Field
{
	friend struct D_Field;
protected:
	uint64_t A[3] = { 0 };
	//uint64_t Pol[3] = {201, 0, 34359738368};
public:
	Field() {};
	Field(string s);
	Field operator+(const Field& B) const;
	Field operator*(const Field& B) const;
	Field& operator=(const Field& B);
	Field(const Field&);
	Field(Field&&);
	void Shift1();
	bool BinSyntax(string n);
	int High() const;
	void ShowBin() const;
	//void Mod();
	int ord();
	Field pov(const Field& B) const;
	Field pov2() const;
	int Tr() const;
	Field rev() const;
};

/*struct D_Field
{
	friend struct Field;
protected:
	uint64_t A[6] = { 0 };
public:
	D_Field() {};
	D_Field operator+(const Field& B) const;
	D_Field operator+(const D_Field& B) const;
	D_Field& operator=(const D_Field& B);
	D_Field(const D_Field&);
	D_Field(D_Field&&);
	Field Mod();
	int ord();
};
*/