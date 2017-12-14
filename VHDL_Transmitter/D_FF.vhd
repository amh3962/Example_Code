--Chris Oakes
--Lab 11
--4/25/16
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;

ENTITY D_FF is
	Port(Clk, En, reset	:IN std_logic;
		  D					:IN std_logic_vector(15 downto 0);
		  Q					:OUT std_logic_vector(15 downto 0));
END D_FF;


ARCHITECTURE behave of D_FF is
BEGIN
	process(reset, clk)
	begin
	If (reset = '0') then
		Q <= x"0000";
	elsif (clk'Event and clk = '1') Then
		if En = '1' then
		Q <= D;
		end if;
	END If;
end process;
END behave;