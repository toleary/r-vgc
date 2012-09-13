
mex run_compartment.cpp
tic;

    gbar_leak = 0.01;
    gbar_na = 100;
    gbar_kd = 20;
    gbar_ka = 30;
    gbar_kca = 20;
    gbar_cas = 2;
    gbar_cat = 2;
    gbar_h = 5;


gs = [gbar_leak, gbar_na, gbar_kd, gbar_ka, gbar_kca, gbar_cas, gbar_cat, gbar_h];
v = run_compartment([0.05 100],gs);
t = toc;
speedup = 0.1/t
plot(v);

