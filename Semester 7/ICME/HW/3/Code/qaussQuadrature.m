%% HW3 Q2
%% Vibhanshu Jain - CS19B1027

%% Polynomial functions

function qaussQuadrature 

%% The polynomial equation 
%% y(x) = (-4)*x^5 + (5)*x^4 + (2)*x^3 + (-3)*x^2 + (1)*x^1 + (-1)*x^0

%% the polynomial representation of matlab
p = [-4 5 2 -3 1 -1];

%% Printing the value at x = 1
disp("The value of polynomial at 1");
y = polyval(p,1)

%% The intergration of the polynomial
disp("The integration of the polynomial between -1 and 1");
i = diff(polyint(p,[-1 1]))

%% One Point Gauss-Quadrature Scheme
%% x1 = 0 and w1 = 2 
%% I = w1*f(x1)

disp("The result of one point Gauss-Quadrature Scheme");
val0 = polyval(p,0);
onePoint = 2.*val0

%% Two Point Gauss-Quadrature Scheme
%% x1 = 1/√3 & x2 = -1/√3 and w1 = 1 & w2 = 1 
%% I = w1*f(x1) + w2+f(x2)

val0 = polyval(p,1/sqrt(3));
val1 = polyval(p,-(1/sqrt(3)));
disp("The result of two point Gauss-Quadrature Scheme");
twoPoint = 1.*val0 + 1.*val1

%% Three Point Gauss-Quadrature Scheme
%% x1 = -√(3/5) & x2 = 0 & x3 = √(3/5) and w1 = 8/9 & w2 = 5/9 & w3 = 5/9
%% I = w1*f(x1) + w2+f(x2)

val0 = polyval(p,-sqrt((3/5)));
val1 = polyval(p,0);
val2 = polyval(p,sqrt((3/5)));

disp("The result of three point Gauss-Quadrature Scheme");
threePoint = (5/9)*val0 + (8/9).*val1 + (5/9).*val2

%% The value of the definite intergral
disp("The value of defininte integral");
intfun = polyint(p);
int = polyval(intfun,1) - polyval(intfun,-1)

end