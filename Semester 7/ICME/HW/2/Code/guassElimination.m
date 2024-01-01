%% HW2 Q3
%% Vibhanshu Jain - CS19B1027

function guassElimination

%% We are using the same example equation as used in the class
%% Here we can use this method only when the diagonal elements are non-zero

A=[ 4  -1   0;
   -1   4  -1;
    0   -1  4 ];

B = [1; 2; 3];

%% The augmented matrix
X = [ A B ];

[row,col] = size(X);  

%% Finding the lower triangular matrix
for i = 1:row-1

    temp = X(i,i);
    X(i,:) = X(i,:)/temp;
    
    for j = i+1: row
        X(j,:) = X(j,:) - X(j,i)*X(i,:);
    end
end

temp = X(row, row);
X(row,:) = X(row,:)/temp;

temp = 0;

%% The final solution to get the values
for i = row:-1:2
    for j = i+1:col
        temp = temp + X(i-1,j-1)*X(j-1,col);
        X(i-1,col) = X(j-1,col) - temp ; 
        temp = 0;
    end
end

disp("The solution of the equation is: ")
disp(X(:,col));
  