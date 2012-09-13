//class for storing state of a compartment
#ifndef CONDSTATE
#define CONDSTATE

class condstate
{
protected:
    double m;
    double h;
public:
    condstate()
    {   }
    
    void set_m(double);
    void set_h(double);
    
    double get_m(void);    
    double get_h(void);    
};

void condstate::set_m(double m_in) {m = m_in;}
void condstate::set_h(double h_in) {h = h_in;}

double condstate::get_m(void) {return m;}
double condstate::get_h(void) {return h;}

#endif
