#ifndef CALCULATIONS_H
#define CALCULATIONS_H

#include "matrix.h"

class Calculations
{
public:
    // The differences in total prices between those from the invoices for the four companies and our calculations
    Matrix differencesInTotalPrices(Matrix &values, Matrix &servicesPrices, Matrix &invoicePrices);

    // The difference between the actual billed number of services and the number of services measured by customers
    Matrix differencesInBilledNumberOfServices(Matrix &values, Matrix &servicesPrices, Matrix &invoicePrices);
};


#endif

