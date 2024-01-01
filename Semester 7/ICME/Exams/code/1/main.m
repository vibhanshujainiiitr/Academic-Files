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

%% Define the step size
h = 0.1;

%% Define the number of steps
n = 10;

%% Define the x vector
x = x0:h:x0 + n*h;

%% Define the y vector
y = zeros(1,n+1);

%% Define the initial condition
y(1) = y0;


%% Define the Euler method
for i = 1:n
    y(i+1) = y(i) + h*myfunction(x(i), y(i));
end

%% Print the result
fprintf('The result of the Euler method is: %f', y(end));

%% Printing a line break
fprintf('\n');

%% b: Runge-Kutta 4th Order method

%% Define the function 
myfunction = @(x,y) 2*x + y;

%% Define the initial conditions
x0 = 0;
y0 = -1;

%% Define the step size
h = 0.1;

%% Define the number of steps
n = 10;

%% Define the x vector
x = x0:h:x0 + n*h;

%% Define the y vector
y = zeros(1,n+1);

%% Define the initial condition
y(1) = y0;


%% Define the Runge-Kutta 4th Order method
for i = 1:n
    k1 = myfunction(x(i), y(i));
    k2 = myfunction(x(i) + h/2, y(i) + h/2*k1);
    k3 = myfunction(x(i) + h/2, y(i) + h/2*k2);
    k4 = myfunction(x(i) + h, y(i) + h*k3);
    y(i+1) = y(i) + h/6 * (k1 + 2*k2 + 2*k3 + k4);
end

%% Print the result
fprintf('The result of the Runge-Kutta 4th Order method is: %f', y(end));