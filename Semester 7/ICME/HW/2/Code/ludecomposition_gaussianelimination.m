%% HW2 Q1 A 
%% Vibhanshu Jain - CS19B1027

%% LU decomposition Methods

function ludecomposition_gaussianelimination

%% the matrices
A = [4 -1 0; -1 4 -1; 0 -1 4];
B = [1 2 3]';

disp("The given matrix A: ");
disp(A);

disp("The given matrix B: ")
disp(B);

%% let n be the size (both rows and column) of the matrix A and b the number of columns of the matrix b
n2 = size(A);
m = size(B);
n = n2(1);
if n ~= m
    disp("Please enter the correct values. ")
    return
end

%% Calcuting using the LU decomposition method. 

%%  LU Decomposition of A
[L,U] = lu(A);

%% forward substitution
g = Fwd_subs(L,n,B);
%% backward substitution
x = Bck_subs(U,n,g);
%% finding A inverse
AI = find_A_inv(L,U,n);

SolutionLU = AI*B;
disp("Solution using the manual implementaiton of LU by Gaussian Elimination Method: ")
disp(SolutionLU)
end


%% Forward substitution function
function g = Fwd_subs(L,n,B)
g = zeros(n,1);
for i = 1:1:n
    temp = 0;
    for j = 1:i-1
        temp = temp - L(i,j)*g(j);
    end
    g(i) = (B(i)+temp) / L(i,i);
end
end

%% Backward substitution function
function x = Bck_subs(U,n,g)
x = zeros(n,1);
for i= n:-1:1
    temp = 0;
    for j = i+1:n
        temp = temp - U(i,j)*x(j);
    end
    x(i) = (g(i)+temp)/U(i,i);
end
end

%% The find A inverse function
function AInverse = find_A_inv(L, U, n)

AInverse = zeros(n,n);

for i =1:n
    ei = zeros(n,1);
    ei(i) = 1;
    g = Fwd_subs(L,n,ei);
    xi = Bck_subs(U,n,g);
    AInverse(:,i) = xi;
end
end

