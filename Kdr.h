// LEAK CONDUCTANCE
#ifndef KDR
#define KDR
#include "conductance.h"

//inherit conductance class spec
class Kdr: public conductance {
protected:
    double m;
public:
    //constructors - must set gbar!    
    // gbar only
    Kdr(double g_in)//: conductance(g_in)
    {
        gbar = g_in;
        state_dim = 1;
        // default if unspecified
        e_rev = -80.0;
    }
    
    //specify both gbar and erev
    Kdr(double g_in, double e_in)//: conductance(g_in)
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
double Kdr::i(void)
{
    return gbar*m*m*m*m*(e_rev - v_m());
}

// can maybe speed things up by overwriting get_g to return gbar & making integrate empty.
void Kdr::integrate(double dt)
{
    //mexPrintf("integrating, dt = %e\n", dt);
    m = m_inf() + (m - m_inf())*exp(-dt/tau_m());
    g = gbar*m*m*m*m;
    //default: g is fixed
}

void Kdr::connect(cellstate *s_in)
{
    compartment_state = s_in;
    m = m_inf();
    //mexPrintf("state ptr val: %f\n",compartment_state->get_v());
    //mexPrintf("state ptr: %d\n",compartment_state);
}

double Kdr::m_inf(void) {return 1.0/(1.0+exp((v_m()+12.3)/-11.8));}
double Kdr::tau_m(void) {return 7.2 - 6.4/(1.0+exp((v_m()+28.3)/-19.2));}

void Kdr::set_state(condstate* cs)
{
    m = cs->get_m();
}

condstate Kdr::get_state(void)
{
    state.set_m(m);
    return state;
}

double* Kdr::state2double(void)
{
    double st[1] = {m};
    return st;
}

void Kdr::double2state(double* st)
{
    m = st[0];
}

#endif
