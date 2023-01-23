#include "file.h"

File::File(string fileName)
{
    this->fileName = fileName;
}

void File::readFromFile(Matrix &values, Matrix &prices)
{
    // opening the file in reading mode
    ifstream file(fileName, ios::in);

    // checking if the file opened properly
    if (!file.is_open())
    {
        cout << "Could not open input file!" << endl;
        exit(1);
    }

    // making a variable to store the readen number
    double num = 0;

    // filling the matrix with the number of services
    for (int i = 0; i < values.rows; i++)
    {
        for (int j = 0; j < values.cols; j++)
        {
            if (file >> num)
                values.p[i][j] = num;
            else
            {
                cout << "There was a problem while reading from the input file!" << endl;
                exit(2);
            }
        }
    }

    // filling the matrix with the total prices
    for (int j = 0; j < prices.cols; j++)
    {
        {
            if (file >> num)
                prices.p[0][j] = num;
            else
            {
                cout << "There was a problem while reading from the input file!" << endl;
                exit(2);
            }
        }
    }
}
