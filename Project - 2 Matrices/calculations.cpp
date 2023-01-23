#include "calculations.h"

Matrix Calculations::differencesInTotalPrices(Matrix &values, Matrix &servicesPrices, Matrix &invoicePrices)
{
    Matrix result = Matrix(values);

    // multiplying the number of services by each of their prices
    result.dotProductOfRowns(servicesPrices);

    // taking the totals for each firm
    Matrix sum = result.sumOfRows();

    // subtract our totals from the invoice totals, getting the actual prices
    Matrix realPrices = invoicePrices - sum;

    return realPrices;
}

// The difference between the actual billed number of services and the number of services measured by customers
Matrix Calculations::differencesInBilledNumberOfServices(Matrix &values, Matrix &servicesPrices, Matrix &invoicePrices)
{
    // allocating temporary matrix (copy of the original one) for the calculations
    Matrix temp = Matrix(values);

    // flipping the matrix for the invoice prices so that we can 'stick' it to the matrix value
    invoicePrices = invoicePrices.transpose();

    // adding (sticking) the invoice prices matrix to the temporary matrix
    temp = temp.addColumn(invoicePrices);

    // applying the Gaussian method to the [temporary matrix|invoice prices matrix]
    //                                     [ax1 + bx2 + cx3 + dx4  = m]
    //                                          [a  b  c  d | m]
    // by doing so we find the real preices of every service
    Matrix actualServicesPrices = temp.GaussianMethod();

    // allocating matrix (copy of the original one) for the answer
    Matrix actualBilledNumberOfServices = Matrix(values);

    // multiplying the number of services by their corresponding actual prices (the ones we found using the Gaussian method)
    actualBilledNumberOfServices.dotProductOfRowns(actualServicesPrices);

    // deviding the calculated above totals by the the prices of the services from the sites
    actualBilledNumberOfServices.divisionOfRowns(servicesPrices);

    // the number of services actually billed 
    //               - 
    // our customer-measured number of services used (i.e. those from the file)
    actualBilledNumberOfServices -= values;

    return actualBilledNumberOfServices;
}
