#include "NBField.h"
#include "Field.h"

int pos_mod(int a, int n) 
{
    return (a % n + n) % n;
}

int main()
{
    NBField A("10110010100111010100010110101001011100100101101010100011101001011001010101110010010101001011000110101001011101010");
    NBField B("10011010110001010101110010010110101010001101001001110101010010110010101000110101010011100100101011010100010110100");
    NBField C("10011010110001010101110010010110101010001101001001110101010010110010101000110101010011100100101011010100010110100");
    NBField D = A + B;
    NBField E = A * B;
    NBField F = A.pov2();
    NBField G = A.pov(C);
    int T = A.Tr();
    NBField I = A.rev();
    cout << "A+B : ";
    D.ShowBin();
    cout << "A*A : ";
    E.ShowBin();
    cout << "A^2 : ";
    F.ShowBin();
    cout << "A^C : ";
    G.ShowBin();
    cout << "Tr(A) : ";
    cout << endl << T << endl;
    cout << "A^(-1) : ";
    I.ShowBin();

    return 0;
}