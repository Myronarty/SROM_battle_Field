#include "NBField.h"

int pos_mod(int a, int n) 
{
    return (a % n + n) % n;
}

int main()
{
    NBField A("10100010010011011110110100111100101011101001000100110011100100100110010101110111100001110010010");
    A.pov2().ShowBin();
    (A * A).ShowBin();
    return 0;
}