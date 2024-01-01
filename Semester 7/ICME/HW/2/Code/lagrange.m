%% HW2 Q3
%% Vibhanshu Jain - CS19B1027

function lagrange

disp("Lagrange Interplation Method");

%% The xi values of the function
xi = [-1 0 1 2];

%% The function values
fxi = [3 -4 5 -6];

%% The degree of the function
n = 3;

%% The point where we want to evaluate the value of our Lagrange function
x = 1.5;

%% The temporary value of our new function at i = 3
temp = 0;

%% Calculating the value
for i = 1:n+1
    product = 1;
    for j = 1:n+1
        if i == j 
            continue;
        end 
        product = product*((x-xi(i)) / (xi(i) - xi(j)));
    end
    temp = temp + fxi(i)*product;
end
disp("The value of our Lagrage Function at ");
disp(x);
disp("is: ");
disp(temp);
end