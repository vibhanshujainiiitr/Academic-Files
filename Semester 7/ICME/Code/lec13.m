A = [
    1  1  1;
    1  2  3;
    1  4  9];
b = [2 4 26/3]';

w = A\b

%% results 
w1 = 1/3;
w2 = 4/3;
w3 = 1/3;

%% Integrate a constant polynomial(0 degree)
p = [1];
p_i = polyint(p);
I_f = diff(polyval(p_i, [1,3]));

%% quadrate
q = [5 3]
q_i = polyint(q);
x1 = 1;
x2 = 2;
x3 = 3;
f1 = 3*x1^2 ;
f2 = 1;
f3 = 1;

%% Ihat_f = 