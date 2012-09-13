#include <cmath>
#include <vector>
#include "mex.h"
#include "compartment.h"
#include "leak.h"
#include "NaV.h"
#include "Kdr.h"
#include "Ka.h"
#include "CaS.h"
#include "liusensor.h"

using namespace std;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double *output;
    double *simparams, *gmax;
    int nits = 10, n_g = 1;
    double dt, tstop;
    double gbar_leak, gbar_na, gbar_kd, gbar_ka, gbar_kca, gbar_cas, gbar_cat, gbar_h;
    int state_dim = 0;
    double* state;
    
    //input + params
    simparams = mxGetPr(prhs[0]);
    dt = simparams[0];
    tstop = simparams[1];

    gmax = mxGetPr(prhs[1]);
    gbar_leak = gmax[0];
    gbar_na = gmax[1];
    gbar_kd = gmax[2];
    gbar_ka = gmax[3];
    gbar_kca = gmax[4];
    gbar_cas = gmax[5];
    gbar_cat = gmax[6];
    gbar_h = gmax[7];
    
    //make conductances
    leak gleak(gbar_leak, -80.0);
    NaV gna(gbar_na,50);
    Kdr gkdr(gbar_kd,-80.0);
    Ka gka(gbar_ka,-80.0);
    CaS gcas(gbar_cas,120.0);
    
    //make sensor
    //liusensor liu;
    
    //make compartment
    compartment cell(-70);
    cell.add_conductance(&gleak);
    cell.add_conductance(&gna);
    cell.add_conductance(&gkdr);
    cell.add_conductance(&gka);
    cell.add_conductance(&gcas);
    
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
