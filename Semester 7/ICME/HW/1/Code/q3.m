%% HW 1 Vibhanshu Jain
%% Question 3

%% Creating a matrix
A = [3 4 5;
     8  9 10];
B = [1 4; 
     2 5;
     9 6];

%% Outputting the input matrix
disp("The first matrix is");
disp(A);
disp("The second matrix is");
disp(B);

%% The direct method to calculate the matrix multiplication
Cdirect = A*B;
disp("The output using the direct method provided by matlab: ");
disp(Cdirect);

%% Applying the manual method to calculate the matrix multiplication. 

%% as we already know that the size of the matrices are [3,2] and [2,3], therefore our
%% result matrix will be [2,2]

%% Initializing the result matrix
C = zeros(2,2);

%% Calculating the values of the resultant matrix
for i=1:2;
    for j=1:2;
        for k=1:3;
          C(i,j) = C(i,j) + A(i,k)*B(k,j);
        end
    end
end

%% Displaying the output

disp("The result after calculating the matrix multiplication manually: ");
disp(C);

%% Part b

%% Converting the matrix C to vector
X = [1 2 3 4];
Y = C(:);

%% Plotting the bar graph
figure, bar(X, diag(Y), 'stacked');

%% Question 3 end