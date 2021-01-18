Library ieee;
Use ieee.std_logic_1164.all;
entity system_st is;
   port( A, B, Cin : in bit;
	Sum, Carry : out bit;)
end system_st ;

architecture structural of sysytem_st is
	component gate1
		port (in_A, in_B, in_C : in bit;
			out_Z: out bit);
	end component;
	component gate2
		port (in_A, in_B, in_C : in bit;
			out_Z: out bit);
	end component;
begin
	G1: gate1
		port map (A, B, C, Sum);
	G2: gate2
		port map (A, B, C, Carry);
end structural;


