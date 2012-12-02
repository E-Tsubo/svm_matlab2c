#include "mex.h"

#include "liblinear/linear.h"
#include "liblinear/linear_model_matlab.h"

void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] )
{
  struct model *linearmodel = (struct model*)malloc( 1*sizeof(struct model) );
  //struct model *linearmodel;
  char *pFileName;
  const char *pErrorMsg;
  int status;

  if( nrhs != 2 ){
    mexPrintf("mat2liblinear(model, 'output_name');\n");
    plhs[0] = mxCreateDoubleMatrix(0, 0, mxREAL);
    return;
  }
  
  if( !mxIsStruct(prhs[0]) ){
    mexPrintf("model is not structure array\n");
    plhs[0] = mxCreateDoubleMatrix(0, 0, mxREAL);
    return;
  }

  if( !mxIsChar(prhs[1]) || mxGetM(prhs[1]) != 1 ){
    mexPrintf("FileName is not char\n");
    plhs[0] = mxCreateDoubleMatrix(0, 0, mxREAL);
    return;
  }
  
  //convert matlab structure to c structure
  pErrorMsg = matlab_matrix_to_model(linearmodel, prhs[0]);
  if( linearmodel == NULL ){
    mexPrintf("Can't read model: %s\n", pErrorMsg);
    plhs[0] = mxCreateDoubleMatrix(0, 0, mxREAL);
    return;
  }
  
  //save model
  pFileName = mxArrayToString(prhs[1]);
  status = save_model(pFileName, linearmodel);
  if( status != 0 ){
    mexWarnMsgTxt("While writing to file, error occured");
  }
  
  free_and_destroy_model(&linearmodel);
  mxFree(pFileName);
  
  //return 0 or 1. 0:success, 1:failure
  plhs[0] = mxCreateDoubleScalar(status);
  return;
}
