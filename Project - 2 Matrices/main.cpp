#include <iostream>
#include <fstream>

#include "calculations.h"
#include "file.h"

using namespace std;

int main()
{
    Matrix prices = Matrix(1, 4);
    prices.p[0][0] = 0.129;
    prices.p[0][1] = 1.461;
    prices.p[0][2] = 85.07;
    prices.p[0][3] = 0.132;

    Matrix values = Matrix(4, 4);
    Matrix total = Matrix(1, 4);

    File f = File("data.txt");
    f.readFromFile(values, total);

    cout << "Input: " << endl;
    cout << values;
    cout << total << endl;

    Calculations calc;
    Matrix m = calc.differencesInTotalPrices(values, prices, total);
    Matrix diff = calc.differencesInBilledNumberOfServices(values, prices, total);

    cout << "Output: " << endl;
    cout << m;
    cout << diff << endl;

    return 0;
}