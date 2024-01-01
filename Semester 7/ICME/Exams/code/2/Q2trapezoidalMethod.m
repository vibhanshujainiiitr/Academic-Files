%% Final Exam Q2
%% Vibhanshu Jain - CS19B1027


%% Solve the given ODE using MATLAB
%% y'= x^2 + 4y'
%% y(0) = 1

%% a: By Trapezoidal method

%% Define the function
myFunction = @(x,y) x^2 + 4*y;

%% Define the initial conditions
x0 = 0;
y0 = 1;

%% the values where we have the find the function value
xf = 0.2;

%% Defining the number of steps
n = 100;

%% Define the step size
h = (xf - x0)/n;

%% Define the x vector
x = x0 + [0:n]*h;

%% Define the y vector
y = zeros(n+1,1);

%% Define the initial condition
y(1,1) = y0;

%% Define the trapezoidal method
for i = 1:n
    yp_kp = y(i,1) + h*myFunction(x(i),y(i,1));
    y(i+1,1) = y(i,1) + h*(myFunction(x(i),y(i,1)) + myFunction(x(i+1),yp_kp))/2;
end

%% Print the result
fprintf('The result of the Trapezoidal Method at xf %f and with number of step %f is: %f', xf, n, y(end,1));

%% Printing a line break
fprintf('\n');