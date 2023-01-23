#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <fstream>
#include "matrix.h"

class File
{
private:
    string fileName;

public:
    File(string fileName);

    // reading the matrices from the file
    void readFromFile(Matrix &values, Matrix &prices);
};

#endif