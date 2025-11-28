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

/*void Field::Mod()
{
    while ((this->A[2] & 18446744039349813248) != 0)
    {
        int i = this->ord() - 163;
        this->A[0] ^= uint64_t(201) << (64-i);
        this->A[2] ^= (uint64_t(1) << 35) << (64-i);
    }
}*/
//good
Field Field::operator*(const Field& B) const
{
    Field C;
    Field A = *this;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if ((B.A[i] & (uint64_t(1) << j)) != 0)
            {
                C = C + A;
            }
            A.Shift1();
        }
    }
    for (int j = 0; j < 35; j++)
    {
        if ((B.A[2] & (uint64_t(1) << j)) != 0)
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
    Field C;
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
//doesnt need
int Field::ord()
{
    uint64_t n = 0;
    int k;
    if(this->A[2] != 0)
    {
        n = this->A[2];
        k = 2;
    }
    else if (this->A[1] != 0)
    {
        n = this->A[1];
        k = 1;
    }
    else if (this->A[0] != 0)
    {
        n = this->A[0];
        k = 0;
    }
    if (n == 0) return -1;

    int pos = 0;

    if (n > 0xFFFFFFFFULL)
    {
        n >>= 32; pos += 32;
    }

    if (n > 0xFFFFULL)
    {
        n >>= 16; pos += 16;
    }

    if (n > 0xFFULL)
    {
        n >>= 8; pos += 8;
    }

    if (n > 0xFULL)
    {
        n >>= 4; pos += 4;
    }

    if (n > 0x3ULL)
    {
        n >>= 2; pos += 2;
    }

    if (n > 0x1ULL)
    {
        pos += 1;
    }

    return pos;
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
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 64; j++)
        {
            if ((this->A[i] & (uint64_t(1) << j)) != 0)
            {
                C = C + A;
            }
            A.Shift1();
            A.Shift1();
        }
    }
    for (int j = 0; j < 35; j++)
    {
        if ((this->A[2] & (uint64_t(1) << j)) != 0)
        {
            C = C + A;
        }
        A.Shift1();
        A.Shift1();
    }
    return C;
}

Field Field::pov(const Field& B) const
{
    Field C;

    return C;
}
