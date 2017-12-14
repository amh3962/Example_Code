--Chris Oakes
--Lab 11
--4/25/16
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;

ENTITY Xor1 is
	Port(Clk, En, reset	:IN std_logic;
		  Input1, Input2	:IN std_logic_vector(15 downto 0);
		  Output				:OUT std_logic_vector(15 downto 0));
END Xor1;


ARCHITECTURE behave of Xor1 is
BEGIN
	process(reset, clk)
	begin
	if (reset = '0') then 
		Output <= x"0000";
	elsif (clk'Event and clk = '1') Then
		if (En = '1') then
		Output <= Input1 Xor Input2;
		end if;
	END If;
end process;
END behave;