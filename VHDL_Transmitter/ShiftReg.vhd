--Chris Oakes
--Lab 11
--4/25/16
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.std_logic_unsigned.all;

ENTITY ShiftReg is
	Port(Clk, Load, Shift, reset	:IN std_logic;
		  En								:IN std_logic_vector(1 downto 0);
		  D								:IN std_logic_vector(15 downto 0);
		  Output							:OUT std_logic);
END ShiftReg;


ARCHITECTURE behave of ShiftReg is
    Signal tempOut	:std_logic;
    Signal temp	   :std_logic_vector(15 downto 0);

BEGIN
	Process (Clk, D, Load, Shift, En, reset)
    BEGIN
       If (reset='0') then
             temp <= x"0000";
       Elsif (Clk'event and Clk='1') then
			if (load = '1') then
				temp(15 downto 0) <= D(15 downto 0);
			elsif (Shift = '1' and En = "11") then
             tempOut <= temp(15);
				 temp(15) <= temp(14);
				 temp(14) <= temp(13);
				 temp(13) <= temp(12);
				 temp(12) <= temp(11);
				 temp(11) <= temp(10);
				 temp(10) <= temp(9);
				 temp(9) <= temp(8);
				 temp(8) <= temp(7);
				 temp(7) <= temp(6);
				 temp(6) <= temp(5);
				 temp(5) <= temp(4);
				 temp(4) <= temp(3);
				 temp(3) <= temp(2);
				 temp(2) <= temp(1);
				 temp(1) <= temp(0);
             temp(0) <= '1';
			end if;
       END If;
    END Process;
	Output <= tempOut;
END behave;
