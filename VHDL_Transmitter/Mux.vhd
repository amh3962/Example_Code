--Aaron Halling
--Lab 11 - Mux
--Ouputs the data being shifted 
library IEEE;
use ieee.std_logic_1164.all;

entity Mux is
	port(Enable	:in std_logic_vector(1 downto 0);
		Input	:in std_logic;
		GPIO  	:out std_logic);
end Mux;

architecture arc of Mux is
signal temp		:std_logic;
begin
	process(Enable, Input, temp)
	begin
	case(Enable) is
		when "00" =>
			temp <= '1';
		when "01" =>
			temp <= '0';
		when "10" =>
			temp <= Input;
		when others =>
			temp <= '1';
	end case;
	end process;
GPIO <= temp;
end arc;