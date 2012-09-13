// LEAK CONDUCTANCE
#ifndef IH
#define IH
#include "conductance.h"

//inherit conductance class spec
class Ih: public conductance {
protected:
    double m;
public:
    //constructors - must set gbar!    
    // gbar only
    Ih(double g_in)//: conductance(g_in)
    {
        gbar = g_in;
        state_dim = 1;
        // default if unspecified
        e_rev = -20.0;
    }
    
    //specify both gbar and erev
    Ih(double g_in, double e_in)//: conductance(g_in)
    {
        gbar = g_in;
        state_dim = 1;
        e_rev = e_in;
    }
    
    //return current
    double i(void);
    void integrate(double dt);
    //let conductance access cell/compartment state
    void connect(cellstate *s_in);
    double m_inf(void);
    double tau_m(void);
    void set_state(condstate*);
    condstate get_state(void);
    double* state2double(void);
    void double2state(double*);
};

//membrane current
double Ih::i(void)
{
    return gbar*m*(e_rev - v_m());
}

// can maybe speed things up by overwriting get_g to return gbar & making integrate empty.
void Ih::integrate(double dt)
{
    //mexPrintf("integrating, dt = %e\n", dt);
    m = m_inf() + (m - m_inf())*exp(-dt/tau_m());
    g = gbar*m;
    //default: g is fixed
}

void Ih::connect(cellstate *s_in)
{
    compartment_state = s_in;
    m = m_inf();
    //mexPrintf("state ptr val: %f\n",compartment_state->get_v());
    //mexPrintf("state ptr: %d\n",compartment_state);
}

double Ih::m_inf(void) {return 1.0/(1.0+exp((v_m()+70.0)/6.0));}
double Ih::tau_m(void) {return (272.0 + 1499.0/(1.0+exp((v_m()+42.2)/-8.73)));}

void Ih::set_state(condstate* cs)
{
    m = cs->get_m();
}

condstate Ih::get_state(void)
{
    state.set_m(m);
    return state;
}

double* Ih::state2double(void)
{
    double st[1] = {m};
    return st;
}

void Ih::double2state(double* st)
{
    m = st[0];
}

#endif
