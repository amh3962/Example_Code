--Aaron Halling
--CPET 241
-- Lab 6 - Seven Segment Display
-- 3/7/16
--Edited for use in Lab 11
library IEEE;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity SSD is
port(Input						  : in std_logic_vector(15 downto 0);
	HEX0, HEX1, HEX2, HEX3     	  : out std_logic_vector(6 downto 0));
end SSD;

architecture arc of SSD is
signal R1, R2, R3, R4	:std_logic_vector(3 downto 0);
constant ZERO 	        :std_logic_vector(6 downto 0) := "1000000";
constant ONE 	        :std_logic_vector(6 downto 0) := "1111001";
constant TWO 	        :std_logic_vector(6 downto 0) := "0100100";
constant THREE          :std_logic_vector(6 downto 0) := "0110000";
constant FOUR 	        :std_logic_vector(6 downto 0) := "0011001";
constant FIVE 	        :std_logic_vector(6 downto 0) := "0010010";
constant SIX  	        :std_logic_vector(6 downto 0) := "0000010";
constant SEVEN          :std_logic_vector(6 downto 0) := "1111000";
constant EIGHT          :std_logic_vector(6 downto 0) := "0000000";
constant NINE 	        :std_logic_vector(6 downto 0) := "0010000";
constant A 		        :std_logic_vector(6 downto 0) := "0001000";
constant B 	  	        :std_logic_vector(6 downto 0) := "0000011";
constant C 		        :std_logic_vector(6 downto 0) := "1000110";
constant D 		        :std_logic_vector(6 downto 0) := "0100001";
constant E 		        :std_logic_vector(6 downto 0) := "0000110";
constant F 		        :std_logic_vector(6 downto 0) := "0001110";
constant NEG            :std_logic_vector(6 downto 0) := "0111111";
constant OFF 	        :std_logic_vector(6 downto 0) := "1111111";

begin

R1 <= Input(3) & Input(2) & Input(1) & Input(0);
R2 <= Input(7) & Input(6) & Input(5) & Input(4);
R3 <= Input(11) & Input(10) & Input(9) & Input(8);
R4 <= Input(15) & Input(14) & Input(13) & Input(12);
process(R1)
Begin
		case R1 is
			when X"0" =>HEX0<=ZERO;
			when X"1" =>HEX0<=ONE;
			when X"2" =>HEX0<=TWO;
			when X"3" =>HEX0<=THREE;
			when X"4" =>HEX0<=FOUR;
			when X"5" =>HEX0<=FIVE;
			when X"6" =>HEX0<=SIX;
			when X"7" =>HEX0<=SEVEN;
			when X"8" =>HEX0<=EIGHT;
			when X"9" =>HEX0<=NINE;
			when x"A" =>HEX0<=A;
			when x"B" =>HEX0<=B;
			when x"C" =>HEX0<=C;
			when x"D" =>HEX0<=D;
			when x"E" =>HEX0<=E;
			when x"F" =>HEX0<=F;
			when others =>HEX0<=OFF;
		end case;	
end process;

process(R2)
Begin
		case R2 is
			when X"0" =>HEX1<=ZERO;
			when X"1" =>HEX1<=ONE;
			when X"2" =>HEX1<=TWO;
			when X"3" =>HEX1<=THREE;
			when X"4" =>HEX1<=FOUR;
			when X"5" =>HEX1<=FIVE;
			when X"6" =>HEX1<=SIX;
			when X"7" =>HEX1<=SEVEN;
			when X"8" =>HEX1<=EIGHT;
			when X"9" =>HEX1<=NINE;
			when x"A" =>HEX1<=A;
			when x"B" =>HEX1<=B;
			when x"C" =>HEX1<=C;
			when x"D" =>HEX1<=D;
			when x"E" =>HEX1<=E;
			when x"F" =>HEX1<=F;
			when others =>HEX1<=OFF;
		end case;
end process;

process(R3)
Begin
		case R3 is
			when X"0" =>HEX2<=ZERO;
			when X"1" =>HEX2<=ONE;
			when X"2" =>HEX2<=TWO;
			when X"3" =>HEX2<=THREE;
			when X"4" =>HEX2<=FOUR;
			when X"5" =>HEX2<=FIVE;
			when X"6" =>HEX2<=SIX;
			when X"7" =>HEX2<=SEVEN;
			when X"8" =>HEX2<=EIGHT;
			when X"9" =>HEX2<=NINE;
			when x"A" =>HEX2<=A;
			when x"B" =>HEX2<=B;
			when x"C" =>HEX2<=C;
			when x"D" =>HEX2<=D;
			when x"E" =>HEX2<=E;
			when x"F" =>HEX2<=F;
			when others =>HEX2<=OFF;
		end case;
end process;

process(R4)
Begin
		case R4 is
			when X"0" =>HEX3<=ZERO;
			when X"1" =>HEX3<=ONE;
			when X"2" =>HEX3<=TWO;
			when X"3" =>HEX3<=THREE;
			when X"4" =>HEX3<=FOUR;
			when X"5" =>HEX3<=FIVE;
			when X"6" =>HEX3<=SIX;
			when X"7" =>HEX3<=SEVEN;
			when X"8" =>HEX3<=EIGHT;
			when X"9" =>HEX3<=NINE;
			when x"A" =>HEX3<=A;
			when x"B" =>HEX3<=B;
			when x"C" =>HEX3<=C;
			when x"D" =>HEX3<=D;
			when x"E" =>HEX3<=E;
			when x"F" =>HEX3<=F;
			when others =>HEX3<=OFF;
		end case;
end process;
end arc;