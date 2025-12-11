#include "NBField.h"

const int NBField::L[225] = { 1, 0, 46, 11, 46, 41, 92, 57, 99, 74, 84, 20, 72, 24, 83, 43, 58, 90, 111, 40, 45, 2, 47, 28, 92, 65, 87, 18, 107, 71, 79, 75, 101, 36, 106, 14, 88, 71, 96, 6, 85, 24, 33, 49, 62, 32, 82, 7, 21, 43, 62, 39, 55, 60, 91, 12, 48, 34, 87, 37, 103, 54, 81, 23, 63, 21, 86, 29, 49, 103, 105, 17, 102, 30, 88, 54, 110, 26, 44, 10, 91, 3, 47, 57, 61, 8, 25, 39, 111, 10, 112, 1, 2, 11, 41, 28, 61, 22, 34, 82, 105, 73, 76, 94, 100, 80, 109, 31, 38, 26, 63, 60, 98, 4, 42, 8, 84, 90, 97, 27, 56, 42, 48, 22, 25, 32, 55, 86, 98, 13, 93, 77, 107, 68, 69, 67, 78, 67, 108, 78, 95, 15, 19, 6, 75, 51, 83, 5, 100, 16, 72, 51, 106, 66, 94, 68, 70, 15, 108, 53, 101, 31, 104, 23, 50, 7, 73, 5, 58, 20, 97, 33, 64, 13, 29, 18, 37, 96, 110, 9, 59, 27, 40, 3, 12, 65, 99, 52, 77, 70, 109, 19, 89, 59, 85, 56, 64, 4, 93, 52, 74, 16, 80, 36, 104, 30, 35, 81, 102, 35, 50, 17, 76, 14, 66, 69, 79, 53, 95, 38, 89, 9, 44, 45, 112 };

bool NBField::BinSyntax(string n)
{
    regex bin("^[01]+$");
    return regex_match(n, bin);
}
//good
NBField::NBField(string s)
{
    A[0] = A[1] = 0;

    int n = s.size();

    if (n > 113)
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
NBField NBField::operator+(const NBField& B) const
{
    NBField C;
    for (int i = 0; i < 2; i++)
    {
        C.A[i] = this->A[i] ^ B.A[i];
    }
    return C;
}

NBField::NBField(const NBField&) = default;

NBField::NBField(NBField&&) = default;

NBField& NBField:: operator=(const NBField& B) = default;

bool NBField::mult_v(int i, const uint64_t u[2], const uint64_t v[2]) const //???
{
    //mult L * v^T
    if (i >= 113) i %= 113;
    int j_0 = i + 1;
    if (j_0 >= 113) j_0 -= 113;

    uint64_t v_[2] = { 0 };

    v_[0] |= (v[j_0 >> 6] >> (j_0 & 63)) & 1;

    int i_ = 1;

    for (int k = 1; k < 225;)
    {
        int j_1 = L[k] + i;
        int j_2 = L[k+1] + i;

        if (j_1 >= 113) j_1 -= 113;
        if (j_2 >= 113) j_2 -= 113;

        uint64_t b_1 = (v[j_1 >> 6] >> (j_1 & 63)) & 1;
        uint64_t b_2 = (v[j_2 >> 6] >> (j_2 & 63)) & 1;

        v_[i_ >> 6] |= ((b_1 ^ b_2) << (i_ & 63));
        k += 2;
        i_++;
    }

    bool t = 0;

    //mult u*(L*v^T)
    for (int j = 0; j < 113; j++)
    {
        int j_ = i + j;
        if (j_ >= 113) j_ -= 113;
        t ^= ((u[j_ >> 6] >> (j_ & 63)) & 1) & (v_[j >> 6] >> (j & 63)) & 1;
    }
    return t;
}

NBField NBField::operator*(const NBField& B) const
{
    NBField C;

    for (int i = 0; i < 113; i++)
    {
        if (mult_v(i, this->A, B.A))
        {
            C.A[i >> 6] |= uint64_t(1) << (i % 113);
        }
    }

    return C;
}

NBField NBField::pov2() const
{
    NBField C;
    C.A[0] = (this->A[0] >> 1) | (this->A[1] << 63);
    C.A[1] = ((this->A[0] << 48) | (this->A[1] >> 1)) & 0x1FFFFFFFFFFFFULL;
    return C;
}
//good
void NBField::ShowBin() const
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
int NBField::High() const
{
    for (int i = 1; i >= 0; i--)
    {
        if (A[i] != 0) return i;
    }
    return -1;
}

int NBField::Tr() const
{
    int t=0;
    for (int i = 0; i < 113; i++)
    {
        if ((A[i / 64] & (uint64_t(1) << (i % 64))) != 0)
        {
            t++;
        }
    }
    return t & 1;
}

NBField NBField::pov2_i(int i) const
{
    NBField C = *this;

    for (int j = 0; j < i; j++)
    {
        C = C.pov2();
    }

    return C;
}

NBField NBField::rev() const
{
    NBField B = *this;
    int k = 1;
    for (int i = 5; i > -1; i--)
    {
        B = B.pov2_i(k) * B;
        k = 2 * k;
        if ((i == 5) || (i == 4))
        {
            B = B.pov2() * *this;
            k++;
        }
    }
    B = B.pov2();

    return B;
}

NBField NBField::pov(const NBField& B) const
{
    NBField C;
    C.A[0] = ~uint64_t(0);
    C.A[1] = (uint64_t(1) << 49) - 1;

    for (int i = 112; i > -1; i--)
    {
        C = C.pov2();
        if ((B.A[i / 64] & (uint64_t(1) << (i % 64))) != 0)
        {
            C = C * *this;
        }
    }

    return C;
}