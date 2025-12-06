#include "NBField.h"

int pos_mod(int a, int n) 
{
    return (a % n + n) % n;
}

int main()
{
    NBField A("1010001001001101111011010011110010101110101000011001000100110011100100100110010101110111100001110010010");
    NBField B =  A.pov2();
    B.ShowBin();
    NBField C = A.pov(NBField("10"));
    C.ShowBin();

    return 0;
}