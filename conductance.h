//Abstract class for defining conductances
#ifndef CONDUCTANCE
#define CONDUCTANCE
#include "cellstate.h"
#include "condstate.h"
#include <cmath>
//#include <vector>
//#include "mex.h"

class conductance {
protected:
    //PUT REGULATOR HERE??
    double gbar;
    double g;
    double e_rev;
    int state_dim;
    cellstate *compartment_state;
    condstate state;
public:
    conductance()
    {
        //null pointer for safety
        compartment_state = 0;
        state_dim = 0;
    }
    
    double v_m(void); //return compartment voltage
    double get_gbar(void);
    double get_g(void);
    double get_ge(void); // for Dayan-Abbot integration
    int get_state_dim(void);
    
    // all of these must be defined and will be unique
    // for each conductance in general
    virtual void integrate(double) =0;
    virtual double i(void) =0; //consider removing this
    virtual void connect(cellstate*) =0;
    virtual void set_state(condstate*) =0;
    virtual double* state2double(void) =0;
    virtual void double2state(double*) =0;
    virtual condstate get_state(void) =0;
};

double conductance::v_m()
{
    return compartment_state->get_v();
}

double conductance::get_gbar()
{
    return gbar;
}

double conductance::get_g()
{
    return g;
}

double conductance::get_ge()
{
    return g*e_rev;
}

int conductance::get_state_dim(void)
{
    return state_dim;
}

#endif
