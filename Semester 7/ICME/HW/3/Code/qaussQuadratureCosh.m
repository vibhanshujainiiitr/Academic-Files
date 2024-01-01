%% HW3 Q3
%% Vibhanshu Jain - CS19B1027

%% Polynomial functions

function qaussQuadratureCosh 


%% One Point Gauss-Quadrature Scheme
%% x1 = 0 and w1 
%% I = w1*f(x1)

disp("The result of one point Gauss-Quadrature Scheme");
val0 = cosh(0);
onePoint = 2.*val0

%% Two Point Gauss-Quadrature Scheme
%% x1 = 1/√3 & x2 = -1/√3 and w1 = 2 & w2 = 1 
%% I = w1*f(x1) + w2+f(x2)

val0 = cosh(1/sqrt(3));
val1 = cosh(-(1/sqrt(3)));
disp("The result of two point Gauss-Quadrature Scheme");
twoPoint = 1.*val0 + 1.*val1

%% Three Point Gauss-Quadrature Scheme
%% x1 = 0 & x2 = √(3/5) & x3 = -√(3/5) and w1 = 2 & w2 = 1 
%% I = w1*f(x1) + w2+f(x2)

val0 = cosh(-sqrt((3/5)));
val1 = cosh(0);
val2 = cosh(sqrt((3/5)));
disp("The result of three point Gauss-Quadrature Scheme");
threePoint = (5/9)*val0 + (8/9).*val1 + (5/9).*val2

end