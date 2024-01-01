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

%% Define the step size
h = 0.1;

%% Define the number of steps
n = 10;

%% Define the x vector
x = x0:h:x0 + n*h;

%% Define the y vector
y = zeros(1, length(x));

%% Define the initial condition
y(1) = y0;

%% Define the trapezoidal method
for i = 1:n
    y(i+1) = y(i) + h/2 * (myFunction(x(i), y(i)) + myFunction(x(i+1), y(i) + h*myFunction(x(i), y(i))));
end

%% Print the result
fprintf('The result of the trapezoidal method is: %f', y(end));
fprintf('\n');

%% b: By Runge-Kutta method

%% Define the function
myFunction = @(x,y) x^2 + 4*y;

%% Define the initial conditions
x0 = 0;
y0 = 1;

%% Define the step size
h = 0.1;

%% Define the number of steps
n = 10;

%% Define the x vector
x = x0:h:x0 + n*h;

%% Define the y vector
y = zeros(1, length(x));

%% Define the initial condition
y(1) = y0;

%% Define the Runge-Kutta method
for i = 1:n
    k1 = myFunction(x(i), y(i));
    k2 = myFunction(x(i) + h/2, y(i) + h/2 * k1);
    k3 = myFunction(x(i) + h/2, y(i) + h/2 * k2);
    k4 = myFunction(x(i) + h, y(i) + h * k3);
    y(i+1) = y(i) + h/6 * (k1 + 2*k2 + 2*k3 + k4);
end

%% Print the result
fprintf('The result of the Runge-Kutta method is: %f', y(end));
fprintf('\n');

%% c: By MATLAB's ode45

%% Define the function
myFunction = @(x,y) x^2 + 4*y;

%% Define the initial conditions
x0 = 0;
y0 = 1;

%% Define the step size
h = 0.1;

%% Define the number of steps
n = 10;

%% Define the x vector
x = x0:h:x0 + n*h;

%% Define the y vector
y = zeros(1, length(x));

%% Define the initial condition
y(1) = y0;

%% Define the ode45 method
[t, y] = ode45(myFunction, x, y0);

%% Print the result
fprintf('The result of the ode45 method is: %f', y(end));
