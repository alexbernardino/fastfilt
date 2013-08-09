/// Usage: [real_out, imag_out] = gaborfilt(handle, input_img)
/// Arguments:input:  handle - pointer to the gabor filter (previously created with opengabor)
///           		  input_img - image to filter. Should be 1 channel (grayscale) and floating point single precision.
///
///           output: real_out - the real part of the filtered image
///                   imag_out - the imaginary part of the filtered image

#include "mex.h"
#include "mgabor.h"


void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    // check correct number of arguments
    if( (nlhs!=2) || (nrhs!=2) )
		mexErrMsgTxt("Please use as: [<real_out>, <imag_out>] = gaborfilt(<filter_handle>, <input_img>\n");
	
	// check correct handle type
	if(!mxIsUint64(prhs[0]))
		mexErrMsgTxt("Invalid handle\n");
	if(mxIsEmpty(prhs[0]))
		mexErrMsgTxt("Invalid handle\n");
	
	//get handle
	unsigned long long *pointer = (unsigned long long *)mxGetData(prhs[0]);
	MatlabFastGabor *fg = (MatlabFastGabor *)pointer[0];
	if( fg->id != FASTGABORHANDLEID )
		mexErrMsgTxt("Invalid object\n");
	
	//get filter parameters
	long lines, cols;
	lines = fg->GetLines();
	cols = fg->GetCols();
	
	// check input data
    if( mxGetNumberOfDimensions(prhs[1]) != 2)
		mexErrMsgTxt("Invalid input image.\n");
		
	// check if data type is single
	if(!mxIsSingle(prhs[1]))
		mexErrMsgTxt("Input data must be of type single\n");
		
	// check coherent sizes
	const mwSize* psz_in1 =  mxGetDimensions(prhs[1]);
	int m, n;
    //because matlab stores data in row order we must make m = cols, n = lines
	m = psz_in1[0];
	n = psz_in1[1];
	if( ( n != lines) || ( m !=  cols) )
		mexErrMsgTxt("Input image must have dimensions coherent with filter specification\n");
	
	
	plhs[0] = mxCreateNumericMatrix(m, n, mxSINGLE_CLASS, mxREAL);
    plhs[1] = mxCreateNumericMatrix(m, n, mxSINGLE_CLASS, mxREAL);
    
	
	float *re, *im, *in;
	
	in = (float*)mxGetPr(prhs[1]);
	re = (float*)mxGetPr(plhs[0]);
	im = (float*)mxGetPr(plhs[1]);
		
	fg->GaborFiltZeroMean(in, re, im);
	
    return;
}