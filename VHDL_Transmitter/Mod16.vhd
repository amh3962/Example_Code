--Aaron Halling
--Counter
--Counts pulses from the 1us clock. This will be used to track how long a transmission has occurred.
library IEEE;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.numeric_std.all;

entity Mod16 is
	port(Clk, En, reset  :in std_logic;
		flag		  :out std_logic;
		Output	  :out std_logic);
	end Mod16;

architecture arc of Mod16 is
signal temp, tempFlag :std_logic;
signal count :std_logic_vector(4 downto 0);
Begin
	Process(reset, Clk, temp)
	begin
	if(reset = '0') then
		count <= "00000";
		tempFlag <= '0';
		temp <= '0';
	elsif(rising_edge(Clk) and (En = '1')) then
		if (count >= "00000" and count < "10000") then
			tempFlag <= '1';
			count <= count + '1';
		elsif (count = "10000") then
			count <= "00000";
			temp <= '1';
			tempFlag <= '0';
		end if;
	end if;
end process;
flag <= tempFlag;
Output <= temp;
end arc;
		
		