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
protected:
	uint64_t A[3] = { 0 };
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
