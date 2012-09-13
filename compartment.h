//single compartment class
#ifndef COMPARTMENT
#define COMPARTMENT
#include <cmath>
#include <vector>
#include "conductance.h"
#include "cellstate.h"

using namespace std;

/* single compartment class
 * contains vector of conductances
 * integrates membrane equation after
 * integrating each conductance state equation */
class compartment
{
protected:
    // capacitance (not used)
    double cm;
    // all conductances in compartment
    vector<conductance*> gs;
    // voltage and other state variables (calcium, ..
    cellstate state;
    double sum_g;
    double sum_ge;
    //double tau_v = 0.0;
    double v_inf;    
public:    
    // constructor
    compartment(double v_init)
    {
        state = cellstate(v_init,0.0);
    }
    
    // constructor
    compartment(double v_init, double c_init)
    {
        state = cellstate(v_init,0.0);
    }
    
    // return v_mem
    double get_v(void);
    // integrate one timestep and return v_mem
    double integrate(double dt);
    // insert conductance
    void add_conductance(conductance *cond_in);
    double* get_state(void);
    int get_cond_state_dim(void);
    void set_state(double*);
    int get_state_dim(void);
};

double compartment::get_v(void)
{
    return state.get_v();
}

double compartment::integrate(double dt)
{
    int n_cond = gs.size();
    double v = state.get_v();
    
    //set ica to zero before summing contributions
    state.set_i_Ca(0.0);
    
    // TODO use an iterator for this
    // integrate all conductances
    for (int i=0; i<n_cond; i++)
    {
        gs[i]->integrate(dt);
        sum_g += gs[i]->get_g();
        sum_ge += gs[i]->get_ge();
    }
    
    v_inf = sum_ge/sum_g;
    
    //mexPrintf("integrating, tau = %e\n", tau_v);
    
    // now integrate membrane equation
    state.set_v(v_inf + (v - v_inf)*exp(-dt*sum_g));
    //for non-unit conductance model
    //tau = cm/sum_g;
    //state.set_v(v_inf + (v - v_inf)*exp(-dt/tau_v));
    
    // ADCR step here
    return state.get_v();
}

// add conductance and provide pointer to compartment state
// for state-dependent conductances
void compartment::add_conductance(conductance *cond_in)
{
    gs.push_back(cond_in);
    cond_in->connect(&state);
}

double* compartment::get_state(void)
{
    int n_cond = gs.size();
    // TODO include states of controllers + sensors
    // TODO - use std::array here?
    int st_dim = get_cond_state_dim();
    
    double* out = new double[st_dim + 2];
    
    out[0] = state.get_v();
    out[1] = state.get_c();
    
    for (int ind=2, i=0; i<n_cond; i++)
    {
        gs[i]->get_state();
        double* st = gs[i]->state2double();
        for (int j=0; j<(gs[i]->get_state_dim()); j++)
        {
            out[ind++] = st[j];
        }   
    }
    //TODO iterate over other stuff too
    return out;
}

int compartment::get_cond_state_dim(void)
{
    int n_cond = gs.size();
    // TODO include states of controllers + sensors
    // TODO - use std::array here?
    int st_dim = 0;
    
    // count states
    for (int i=0; i<n_cond; i++)
    {
        st_dim += gs[i]->get_state_dim();   
    }
    
    return st_dim;
}

void compartment::set_state(double* st_in)
{
    int n_cond = gs.size();
    // TODO include states of controllers + sensors
    // TODO - use std::array here?
    //int st_dim = get_cond_state_dim();
    
    //double* out = new double[st_dim + 2];
    
    state.set_v(st_in[0]);
    state.set_c(st_in[1]);
    
    for (int ind=2, i=0; i<n_cond; i++)
    {
        gs[i]->double2state(&st_in[ind]);
        ind += gs[i]->get_state_dim();
    }
    //TODO iterate over other stuff too
}

int compartment::get_state_dim(void)
{
    return get_cond_state_dim() + 2;
}

#endif
