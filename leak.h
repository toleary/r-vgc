// LEAK CONDUCTANCE
#ifndef LEAK
#define LEAK
#include "conductance.h"

//inherit conductance class spec
class leak: public conductance {
public:
    //constructors - must set gbar!    
    // gbar only
    leak(double g_in)//: conductance(g_in)
    {
        gbar = g_in;
        state_dim = 0;
        // default if unspecified
        e_rev = -60.0;
    }
    
    //specify both gbar and erev
    leak(double g_in, double e_in)//: conductance(g_in)
    {
        gbar = g_in;
        state_dim = 0;
        e_rev = e_in;
    }
    
    double i(void);
    void integrate(double dt); //integrate = do nothing
    void connect(cellstate *s_in);
    void set_state(condstate*);
    condstate get_state(void);
    double* state2double(void);
    void double2state(double*);    
};

double leak::i(void)
{
    return gbar*(e_rev - compartment_state->get_v());
}

// can maybe speed things up by overwriting get_g to return gbar & making integrate empty.
void leak::integrate(double dt)
{
    g = gbar;
}

void leak::connect(cellstate *s_in)
{
    compartment_state = s_in;
}

void leak::set_state(condstate* cs)
{
    //no state to set in leak!
}

condstate leak::get_state(void)
{
    return state;
}

double* leak::state2double(void)
{
    double* st = 0;
    return st;
}

void leak::double2state(double*) {    }

#endif
