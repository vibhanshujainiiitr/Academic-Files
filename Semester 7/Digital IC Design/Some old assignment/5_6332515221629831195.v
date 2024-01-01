// design
module q1 #(parameter n =4) (input clk,input [n-1:0] x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,h0,h1,h2,h3,h4,h5,h6,h7,h8,h9,output reg [2*n-1:0] r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,output reg [2*n+2:0]y);
  always @(posedge clk) begin 
    r9<=x9*h9;
    r8<=x8*h8;
    r7<=x7*h7;
    r6<=x6*h6;
    r5<=x5*h5;
    r4<=x4*h4;
    r3<=x3*h3;
    r2<=x2*h2;
    r1<=x1*h1;
    r0<=x0*h0;
  end
  always @(negedge clk) y<=r9+r8+r7+r6+r5+r4+r3+r2+r1+r0;
endmodule

// testbench
module q1tb #(parameter n=4,parameter clk_period=10);
  reg [n-1:0]x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,h0,h1,h2,h3,h4,h5,h6,h7,h8,h9;
  reg clk=1'b0;
  wire [2*n-1+3:0]y;
  wire [2*n-1:0] r0,r1,r2,r3,r4,r5,r6,r7,r8,r9;
  q1 #(n) dut (clk,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,h0,h1,h2,h3,h4,h5,h6,h7,h8,h9,r0,r1,r2,r3,r4,r5,r6,r7,r8,r9,y);
  
  //clock generation
  always @(*) #(clk_period/2) clk<=~clk;
  
  initial 
    repeat(5) begin 
      {x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,h0,h1,h2,h3,h4,h5,h6,h7,h8,h9}=$random();
      #(clk_period);
     end
  
endmodule