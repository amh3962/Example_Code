--Aaron Halling
--Lab 11 - Clk 
--1 us clock
library IEEE;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity CLK is
port(clk_50Mhz 	:in std_logic;
	clk				:out std_logic;
	reset, En		:in std_logic);

end CLK;

architecture arc of CLK is
signal count		:unsigned(27 downto 0);
signal temp_clk	:std_logic;

Begin
	process(clk_50Mhz, temp_clk, reset)
	begin
		if (reset = '0') then
			count <= (others => '0');
			temp_clk <= '0';
		elsif(rising_edge(clk_50Mhz)) then
			if (En = '1') then
				if(count = x"0000032") then --50 counts = 1us
					count <= (others => '0');
					temp_clk <= '1';
				else	
					count <= count + "1";
					temp_clk <= '0';
				end if;
			end if;
		end if;
end process;
clk <= temp_clk;
end arc;