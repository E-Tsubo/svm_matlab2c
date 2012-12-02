#include "mex.h"
#include "libsvm/svm.h"
#include "libsvm/svm_model_matlab.h"

void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] )
{
  struct svm_model *model;
  char *pFileName;
  const char *pErrorMsg;
  int status;

  if( nrhs != 2 ){
    mexPrintf("mat2libsvm(model, 'output_name');\n");
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
  model = matlab_matrix_to_model(prhs[0], &pErrorMsg);
  if( model == NULL ){
    mexPrintf("Can't read model: %s\n", pErrorMsg);
    plhs[0] = mxCreateDoubleMatrix(0, 0, mxREAL);
    return;
  }

  //save model
  pFileName = mxArrayToString(prhs[1]);
  status = svm_save_model(pFileName, model);
  if( status != 0 ){
    mexWarnMsgTxt("While writing to file, error occured");
  }
  
  svm_free_and_destroy_model(&model);
  mxFree(pFileName);
  
  //return 0 or 1. 0:success, 1:failure
  plhs[0] = mxCreateDoubleScalar(status);
  return;
}
