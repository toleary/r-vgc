// LEAK CONDUCTANCE
#ifndef LIUSENSOR
#define LIUSENSOR
#include <cmath>

class liusensor {
protected:
    double Mf, Ms, Md;
    double Hf, Hs;
    double ZMf, ZMs, ZMd;
    double ZHf, ZHs;
    double GF, GS, GD;
    double F, S, D;
    double Mf_inf, Ms_inf, Md_inf;
    double Hf_inf, Hs_inf;
    double tau_Mf, tau_Ms, tau_Md;
    double tau_Hf, tau_Hs;
    cellstate *compartment_state;
    
    inline double sigmoid(double, double);
public:
    //constructor
    liusensor()
    {   }
    
    void integrate(double dt);
    //let sensor access cell/compartment state
    void connect(cellstate *s_in);
    double get_F(void);
    double get_S(void);
    double get_D(void);
};

void liusensor::integrate(double dt)
{
    //double ica = compartment_state->get_c();
    
    Mf_inf = sigmoid(2.0,1.0);
    mexPrintf("integrating, Mf_inf = %e\n", Mf_inf);
    //Mf = Mf_inf + (Mf - Mf_inf)*exp(-dt/tau_Mf);
    //F = GF*Mf*Mf*Hf;
}

void liusensor::connect(cellstate *s_in)
{
    compartment_state = s_in;
    //m = m_inf();
    //h = h_inf();
    //mexPrintf("state ptr val: %f\n",compartment_state->get_v());
}

//getters
double liusensor::get_F(void) {return F;}
double liusensor::get_S(void) {return S;}
double liusensor::get_D(void) {return D;}

double liusensor::sigmoid(double x, double a) {return 1.0/(1+exp(a + x));}

#endif
