%% HW2 Q2
%% Vibhanshu Jain - CS19B1027

%% Polynomial functions

function polynomial 

%% The polynomial equation 
%% y(x) = (1)*x^4 + (-4)*x^3 + 7*x^2 + (-16)*x^1 + 12*x^0

%% the polynomail representation of matlab
p = [1 -4 7 -16 12];

%% Printing the value at x = 1
disp("The value of polynomial at 1");
y = polyval(p,1)

%% The root of the polynomial
disp("The root of the polynomial");
r = roots(p)

%% The intergration of the polynomial
disp("The integration of the polynomail");
i = polyint(p)

%% The derivate
d  = polyder(p);

%% Derivate value at 3.1 & 0.2
disp("The value of derivation at 3.1");
v1 = polyval(d,3.1)
disp("The value of derivation at 0.2");
v2 = polyval(d,0.2)
end