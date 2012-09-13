
mex test_compartment.cpp
tic;
v = test_compartment([0.05 1000]);
t = toc;
speedup = 1.0/t
plot(v);

