#ifndef MGABOR_H
#define MGABOR_H

//Define a gabor object for use with matlab

#include "FastGabor.h" 

//Arbitrary code for checking handle validity
#define FASTGABORHANDLEID 9267303

class MatlabFastGabor : public FastGabor
{
public: int id;
};

#endif // MLPS_H