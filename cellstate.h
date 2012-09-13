//class for storing state of a compartment
#ifndef CELLSTATE
#define CELLSTATE

class cellstate
{
protected:
    double v;
    //calcium concentration
    double c;
    //in future, ion can be an object added to state like a channel
    double e_leak;
    double e_K;
    double e_Na;
    double e_Ca;
    double e_h;
    //Ca current (for liu sensor)
    double i_Ca;
public:
    cellstate()
    {   }
    
    cellstate(double v_in, double c_in)
    {
        v = v_in;
        c = c_in;
        //default reversal potentials
        e_leak = -60.0;
        e_K = -80.0;
        e_Na = 50.0;
        e_Ca = 120.0;
    }
    
    void set_v(double);
    void set_c(double);
    void set_e_leak(double);
    void set_e_K(double);
    void set_e_Na(double);
    void set_e_Ca(double);
    void set_e_h(double);
    void set_i_Ca(double);

    double get_v(void);
    double get_c(void);
    double get_e_leak(void);
    double get_e_Na(void);
    double get_e_K(void);
    double get_e_Ca(void);    
    double get_e_h(void);    
    double get_i_Ca(void);    
};

// setters
void cellstate::set_v(double v_in)      {v = v_in;}
void cellstate::set_c(double c_in)      {c = c_in;}
void cellstate::set_e_leak(double e_in) {e_leak = e_in;}
void cellstate::set_e_K(double e_in)    {e_K = e_in;}
void cellstate::set_e_Na(double e_in)   {e_Na = e_in;}
void cellstate::set_e_Ca(double e_in)   {e_Ca = e_in;}
void cellstate::set_e_h(double e_in)    {e_h = e_in;}
void cellstate::set_i_Ca(double iCa_in) {i_Ca = iCa_in;}

// getters
double cellstate::get_v(void)       {return v;}
double cellstate::get_c(void)       {return c;}
double cellstate::get_e_leak(void)  {return e_leak;}
double cellstate::get_e_K(void)     {return e_K;}
double cellstate::get_e_Na(void)    {return e_Na;}
double cellstate::get_e_Ca(void)    {return e_Ca;}
double cellstate::get_e_h(void)     {return e_h;}
double cellstate::get_i_Ca(void)    {return i_Ca;}

#endif
