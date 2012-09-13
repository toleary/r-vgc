#include <cmath>
#include <vector>
#include "mex.h"
#include "compartment.h"
#include "leak.h"
#include "NaV.h"
#include "Kdr.h"
#include "Ka.h"
#include "CaS.h"
#include "Ih.h"
#include "liusensor.h"

using namespace std;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double *output;
    double *input;
    int nits = 10, n_g = 1;
    double dt, tstop;
    int state_dim = 0;
    double* state;
    double E_Na = 50.0;
    double E_K = -80.0;
    double E_h = -20.0;
    double E_leak = -60.0;
    double E_Ca = 132.0;
    
    //input + params
    input = mxGetPr(prhs[0]);
    dt = input[0];
    tstop = input[1];
    
    //make conductances
    leak gleak(0.002, E_leak);
    NaV gna(140.0, E_Na);
    Kdr gkdr(40.0, E_K);
    Ka gka(1.0, E_K);
    //CaS gcas(1.0, E_Ca);
    Ih gh(1.0, E_h);
    
    //make sensor
    //liusensor liu;
    
    //make compartment
    compartment cell(-70);
    cell.add_conductance(&gleak);
    cell.add_conductance(&gna);
    cell.add_conductance(&gkdr);
    cell.add_conductance(&gka);
    //cell.add_conductance(&gcas);
    cell.add_conductance(&gh);
    
    //mexPrintf("g leak = %e\n", g_leak.get_gbar());
    //mexPrintf("i leak = %f\n", gleak2.i());
    
    state_dim = cell.get_state_dim();
    
    mexPrintf("test = %d\n", state_dim);
    
    state = new double[state_dim];
    state = cell.get_state();
    
    for(int i=0; i<state_dim; i++)
    {
        mexPrintf("test = %f\n", state[i]);
    }
    
    nits = (int) floor(tstop/dt);
    
    //output
    plhs[0] = mxCreateDoubleMatrix(nits, n_g, mxREAL);
    output = mxGetPr(plhs[0]);
    
    //integration loop
    for(int i=0; i<nits; i++)
    {
        output[i] = cell.integrate(dt);
    }
    
}
