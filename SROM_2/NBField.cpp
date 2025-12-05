#include "NBField.h"

const int NBField::L[225] = { 1, 113, 159, 237, 272, 380, 431, 509, 551, 639, 649, 698, 750, 815, 874, 947, 962, 1107, 1128, 1170, 1175, 1245, 1290, 1384, 1448, 1534, 1556, 1600, 1689, 1766, 1774, 1883, 1909, 1957, 2027, 2048, 2122, 2218, 2243, 2266, 2345, 2397, 2406, 2535, 2548, 2631, 2681, 2719, 2733, 2868, 2887, 2977, 2993, 3111, 3142, 3176, 3212, 3311, 3364, 3427, 3493, 3557, 3584, 3639, 3679, 3750, 3815, 3871, 3891, 4058, 4060, 4085, 4170, 4211, 4269, 4348, 4404, 4433, 4451, 4530, 4611, 4636, 4680, 4803, 4807, 4867, 4884, 5011, 5083, 5095, 5197, 5199, 5200, 5322, 5352, 5452, 5485, 5559, 5571, 5732, 5755, 5836, 5839, 5970, 5976, 6069, 6098, 6133, 6140, 6241, 6278, 6388, 6426, 6445, 6483, 6562, 6638, 6757, 6764, 6807, 6836, 6935, 6941, 7028, 7031, 7151, 7174, 7318, 7330, 7358, 7438, 7535, 7565, 7639, 7640, 7751, 7762, 7864, 7905, 7988, 8005, 8038, 8042, 8142, 8211, 8300, 8332, 8367, 8462, 8491, 8547, 8639, 8694, 8767, 8795, 8882, 8884, 8942, 9035, 9093, 9141, 9184, 9257, 9289, 9316, 9386, 9452, 9497, 9550, 9625, 9702, 9751, 9782, 9844, 9860, 9962, 9981, 10153, 10167, 10179, 10229, 10310, 10323, 10399, 10408, 10574, 10608, 10674, 10699, 10805, 10844, 10867, 10937, 11020, 11046, 11130, 11138, 11191, 11280, 11352, 11374, 11429, 11493, 11562, 11630, 11669, 11674, 11833, 11854, 11900, 11915, 11995, 12054, 12105, 12157, 12273, 12283, 12370, 12412, 12468, 12519, 12552, 12587, 12701, 12768 };


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

int* NBField::zsuvL(int i)
{
    int rez[113] = { 0 };

    if (i < 64)
    {
        this->A[0] = (this->A[0] << i) | (this->A[1] >> (49-i));
        this->A[1] = (this->A[1] << i) | (this->A[0] >> (35 - i));
    }
    else if (i < 113)
    {

    }

    return rez;
}

int* NBField::zsuvR(int i)
{
    int rez[113] = { 0 };

    return rez;
}

NBField NBField::operator*(const NBField& B) const
{
    NBField C;

    return C;
}

NBField NBField::pov2() const
{
    NBField C;
    C.A[0] = (this->A[0] << 1) | ((this->A[1] >> 48) & 1);
    C.A[1] = ((this->A[0] >> 63) | (this->A[1] << 1)) & 0x1FFFFFFFFFFFFULL;
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