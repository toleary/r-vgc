// CALCIUM CONDUCTANCE
#ifndef CAS
#define CAS
#include "conductance.h"

//inherit conductance class spec
class CaS: public conductance {
protected:
    double m;
    double h;
    double i_ca;
    double v;
public:
    //constructors - must set gbar!    
    // gbar only
    CaS(double g_in)//: conductance(g_in)
    {
        gbar = g_in;
        state_dim = 2;
        // default if unspecified
        e_rev = 120.0;
    }
    
    //specify both gbar and erev
    CaS(double g_in, double e_in)//: conductance(g_in)
    {
        gbar = g_in;
        state_dim = 2;
        e_rev = e_in;
    }
    
    //return current
    double i(void);
    void integrate(double dt);
    //let conductance access cell/compartment state
    void connect(cellstate *s_in);
    double m_inf(void);
    double h_inf(void);
    double tau_m(void);
    double tau_h(void);
    void set_state(condstate*);
    condstate get_state(void);
    double* state2double(void);
    void double2state(double*);    
};

double CaS::i(void)
{
    return gbar*m*m*m*h*(e_rev - v_m());
}

// can maybe speed things up by overwriting get_g to return gbar & making integrate empty.
void CaS::integrate(double dt)
{
    i_ca = compartment_state->get_i_Ca();
    e_rev = compartment_state->get_e_Ca();
    //mexPrintf("integrating, dt = %e\n", dt);
    m = m_inf() + (m - m_inf())*exp(-dt/tau_m());
    h = h_inf() + (h - h_inf())*exp(-dt/tau_h());
    g = gbar*m*m*m*h;
    compartment_state->set_i_Ca(g*(e_rev - v_m()));
}

void CaS::connect(cellstate *s_in)
{
    compartment_state = s_in;
    m = m_inf();
    h = h_inf();
    //mexPrintf("state ptr val: %f\n",compartment_state->get_v());
    //mexPrintf("state ptr: %d\n",compartment_state);
}

double CaS::m_inf(void) {return 1.0/(1.0+exp((v_m()+33.0)/-8.1));}
double CaS::h_inf(void) {return 1.0/(1.0+exp((v_m()+60.0)/6.2));}
double CaS::tau_m(void) {return 1.4 + 7.0/(exp((v_m()+27.0)/10.0) + exp((v_m()+70.0)/-13.0));}
double CaS::tau_h(void) {return 60.0 + 150.0/(exp((v_m()+55.0)/9.0) + exp((v_m()+65.0)/-16.0));}

void CaS::set_state(condstate* cs)
{
    m = cs->get_m();
    h = cs->get_h();
}

condstate CaS::get_state(void)
{
    state.set_m(m);
    state.set_h(h);
    return state;
}

double* CaS::state2double(void)
{
    double st[2] = {m, h};
    return st;
}

void CaS::double2state(double* st)
{
    m = st[0];
    h = st[1];
}

#endif
