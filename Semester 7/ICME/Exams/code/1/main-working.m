%% Final Exam Q1
%% Vibhanshu Jain - CS19B1027


%% Solve the given ODE using MATLAB
%% y'= 2x + y'
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
y(1) = y0;

%% Define the error vector
error = zeros(1,n+1);

%% Define the exact solution vector
exact = zeros(1,n+1);

%% Define the exact solution function
exact_solution = @(x) -1/2*x^2 + x - 1/2;

%% Calculate the exact solution
for i = 1:n+1
    exact(i) = exact_solution(x(i));
end

%% Calculate the error
for i = 1:n
    y(i+1) = y(i) + h*myfunction(x(i),y(i));
    error(i+1) = abs(exact(i+1) - y(i+1));
end

%% Plot the error
plot(x,error);
title('Error vs x');
xlabel('x');
ylabel('Error');

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
y(1) = y0;

%% Define the error vector
error = zeros(1,n+1);

%% Define the exact solution vector
exact = zeros(1,n+1);

%% Define the exact solution function
exact_solution = @(x) -1/2*x^2 + x - 1/2;

%% Calculate the exact solution
for i = 1:n+1
    exact(i) = exact_solution(x(i));
end

%% Calculate the error
for i = 1:n
    k1 = myfunction(x(i),y(i));
    k2 = myfunction(x(i) + h/2, y(i) + h*k1/2);
    k3 = myfunction(x(i) + h/2, y(i) + h*k2/2);
    k4 = myfunction(x(i) + h, y(i) + h*k3);
    y(i+1) = y(i) + h*(k1 + 2*k2 + 2*k3 + k4)/6;
    error(i+1) = abs(exact(i+1) - y(i+1));
end

%% Plot the error
plot(x,error);
title('Error vs x');
xlabel('x');
ylabel('Error');

