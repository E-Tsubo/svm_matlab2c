#include "mex.h"

#include "liblinear/linear.h"
#include "liblinear/linear_model_matlab.h"

void mexFunction( int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[] )
{
  char *loadName = NULL;
  int buflen;
  
  int status;
  const char *error_msg;

  struct model *c_model = NULL;
  
  buflen = mxGetN(prhs[0])*sizeof(mxChar)+1;
  loadName = mxMalloc(buflen);
  status = mxGetString(prhs[0], loadName, buflen);
  
  mexPrintf("Convert [%s] from C Structure to Matlab Structure\n", loadName);
  
  c_model = load_model( loadName );
  if( c_model == NULL )
    mexPrintf("ERROR: Can't load liblinear model\n");
  error_msg = model_to_matlab_structure(plhs, c_model);
  if( error_msg )
    mexPrintf("ERROR: Can't convert liblinear model to matlab structure\n");
  free_and_destroy_model(&c_model);
  
  return;
}
