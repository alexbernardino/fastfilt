/// Usage: handle = opengabor( lines, cols, scale, orientation, wavelength )
/// Arguments: input - lines: number of lines of the images
///                    cols: number of columns of images
///                    scale: std dev of the gaussian envelope
///                    orientation: angle (degrees) of the carrier
///                    wavelength: spatial period (pixels) of the carrier
///            output - handle with the object pointer

#include "mex.h"
#include "mgabor.h" 

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // check correct number of arguments
    if( (nlhs!=1) || (nrhs!=5) )
		mexErrMsgTxt("Please use as: <handle> = opengabor( <lines>, <cols>, <scale (pixel)>, <orientation (degree)>, <wavelength (pixel)> )\n");
		
	// check correct number of dimensions
    if( mxIsEmpty(prhs[0]) || mxIsEmpty(prhs[1]) || mxIsEmpty(prhs[2]) || mxIsEmpty(prhs[3]) || mxIsEmpty(prhs[4]) )
		mexErrMsgTxt("Invalid argument: empty array");
		
	
	double lines = mxGetScalar(prhs[0]);
	double cols = mxGetScalar(prhs[1]);
	double scale = mxGetScalar(prhs[2]);
	double orientation = mxGetScalar(prhs[3]);
	double wavelength =  mxGetScalar(prhs[4]);
		
	// check valid range
	if( ((int)lines < 1) || ((int)cols < 1) )
        mexErrMsgTxt("Error: Image size must be positive \n");
	
    if( (scale < 0.5) || (wavelength < 0.5))
		mexErrMsgTxt("Error: Scale/wavelength must be positive > 0.5 \n");
	
	MatlabFastGabor *fg = new MatlabFastGabor();
	if( fg == NULL)
		mexErrMsgTxt("Error: Cannot create object\n");
		
    
	fg->id = FASTGABORHANDLEID;
	fg->AllocateResources(lines, cols, scale, orientation, wavelength);
	plhs[0] = mxCreateNumericMatrix(1,1, mxUINT64_CLASS, mxREAL);
	unsigned long long *pointer = (unsigned long long*)mxGetData(plhs[0]);
	pointer[0] = (unsigned long long)fg;
	
    return;
}