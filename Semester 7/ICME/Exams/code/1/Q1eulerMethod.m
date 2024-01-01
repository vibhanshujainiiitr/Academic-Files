%% Final Exam Q1
%% Vibhanshu Jain - CS19B1027


%% Solve the given ODE using MATLAB
%% y'= 2x + y
%% y(0) = -1


%% a: Euler Method

%% Define the function
myfunction = @(x,y) 2*x + y;

%% Define the initial conditions
x0 = 0;
y0 = -1;

%% the values where we have the find the function value
xf = 0.2;

%% Defining the number of steps
n = 3;

%% Define the step size
h = (xf - x0)/n;

%% Define the x vector
x = x0 + [0:n]*h;

%% Define the y vector
y = zeros(n+1,1);

%% Define the initial condition
y(1,1) = y0;

%% Define the Euler method
for i = 1:n
    y(i+1,1) = y(i,1) + h*myfunction(x(i), y(i,1));
end

%% Print the result
fprintf('The result of the Euler method at xf: %f and with number of step %f is: %f', xf, n, y(end,1));

%% Printing a line break
fprintf('\n');