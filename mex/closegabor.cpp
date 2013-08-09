/// Usage: closegabor(<handle>)
/// Arguments: handle - pointer to the gabor filter (previously created with opengabor)

#include "mex.h"
#include "mgabor.h" 

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // check correct number of arguments
    if( (nlhs!=0) || (nrhs!=1) )
		mexErrMsgTxt("Please use as: closegabor(<handle>)\n");
		
	// check correct handle type
	if(!mxIsUint64(prhs[0]))
		mexErrMsgTxt("Invalid handle\n");
	if(mxIsEmpty(prhs[0]))
		mexErrMsgTxt("Invalid handle\n");
	
	//get handle
	unsigned long long *pointer = (unsigned long long*)mxGetData(prhs[0]);
	MatlabFastGabor *fg = (MatlabFastGabor *)pointer[0];
	if( fg->id != FASTGABORHANDLEID )
		mexErrMsgTxt("Invalid object\n");
		
	//deallocate memory
	fg->id = NULL;
	fg->FreeResources();
	delete fg;
	
    return;
}