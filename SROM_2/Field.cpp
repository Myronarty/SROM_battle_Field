#include "Field.h"
//good
bool Field::BinSyntax(string n)
{
    regex bin("^[01]+$");
    return regex_match(n, bin);
}
//good
Field::Field(string s)
{
    A[0] = A[1] = A[2] = 0;

    int n = s.size();

    if (n > 163)
    {
        cout << "Too big number" << endl;
        return;
    }

    if (BinSyntax(s) == 0)
    {
        cout << "Strange number" << endl;
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (s[n - 1 - i] == '1')
        {
            A[i / 64] |= (uint64_t(1) << (i % 64));
        }
    }
}
//good
Field Field::operator+(const Field& B) const
{
    Field C;
    for (int i = 0; i < 3; i++)
    {
        C.A[i] = this->A[i] ^ B.A[i];
    }
    return C;
}

Field::Field(const Field&) = default;

Field::Field(Field&&) = default;

Field& Field:: operator=(const Field& B) = default;
//good
Field Field::operator*(const Field& B) const
{
    Field C;
    Field A = *this;
    for (int i = 0; i < 163; i++)
    {
        if ((B.A[i/64] & (uint64_t(1) << (i%64))) != 0)
        {
            C = C + A;
        }
        A.Shift1();
    }
    return C;
}
//good
void Field::Shift1()
{
    this->A[2] = (this->A[2] << 1) | (this->A[1] >> 63);
    this->A[1] = (this->A[1] << 1) | (this->A[0] >> 63);
    this->A[0] = this->A[0] << 1;

    if ((this->A[2] & (uint64_t(1) << 35)) != 0)
    {
        this->A[0] ^= uint64_t(201);
        this->A[2] ^= (uint64_t(1) << 35);
    }
}
//good
void Field::ShowBin() const
{
    cout << endl;

    int k = High();

    if (k < 0)
    {
        cout << "0" << endl;
        return;
    }

    bool firstOneFound = false;

    for (int i = k; i >= 0; i--)
    {
        uint64_t val = A[i];

        for (int j = 63; j >= 0; j--)
        {
            bool bit = (val >> j) & 1;

            if (i == k)
            {
                if (bit)
                {
                    firstOneFound = true;
                    cout << "1";
                }
                else if (firstOneFound)
                {
                    cout << "0";
                }
            }
            else
            {
                cout << bit;
            }
        }
    }
    cout << endl;
}
//for showbit
int Field::High() const
{
    for (int i = 2; i >= 0; i--)
    {
        if (A[i] != 0) return i;
    }
    return -1;
}

Field Field::pov2() const
{
    Field C;
    Field A;
    A.A[0] = 1;
    for (int i = 0; i < 163; i++)
    {
        if ((this->A[i/64] & (uint64_t(1) << (i%64))) != 0)
        {
            C = C + A;
        }
        A.Shift1();
        A.Shift1();
        A.ShowBin();
    }
    return C;
}

Field Field::pov(const Field& B) const
{
    Field C;
    C.A[0] = 1;

    for (int i = 162; i > -1; i--)
    {
        C = C.pov2();
        if ((B.A[i/64] & (uint64_t(1) << (i%64))) != 0)
        {
            C = C * *this;
        }
    }

    return C;
}

int Field::Tr() const
{
    Field A = *this;
    Field C = *this;
    Field Q;
    Q.A[0] = 163;
    for (int i = 1; i < 163; i++)
    {
        A = A.pov2();
        C = C + A;
    }
    return C.A[0];
}

Field Field::rev() const
{
    return this->pov(Field("1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111110"));
}
