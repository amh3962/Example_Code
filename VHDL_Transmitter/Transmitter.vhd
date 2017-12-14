--Aaron Halling & Chris Oakes
--Lab 11 - Transmitter & Reciever
--Transmitter by Aaron Halling
--Reciever by Chris Oakes
--Users input a 16 bit message, then a 16 bit encryption
--The input is XOR'd with the encryption, then serially transmitted by GPIO
library IEEE;
use ieee.std_logic_1164.all;

entity Transmitter is
	port(Key1, Key2, int_clk, reset	    :in std_logic;
		SW								:in std_logic_vector(15 downto 0);
		hex0, hex1, hex2, hex3 			:out std_logic_vector(6 downto 0);
		GPIO							:out std_logic);
	end Transmitter;
	
architecture arc of Transmitter is
signal clk_1us													:std_logic;
signal Q_Pin, Q_Encrypt 										:std_logic_vector(15 downto 0);
signal SH, LD, Shift_En, Timer_En, Pin_En, Key_En, XOR_En, flag :std_logic;
signal Mux_sel													:std_logic_vector(1 downto 0);
signal D_shift													:std_logic_vector(15 downto 0);
signal Counter													:std_logic;
signal data														:std_logic;
component CLK is
port(clk_50Mhz 	    :in std_logic;
	clk				:out std_logic;
	reset, En		:in std_logic);

end component;

component D_FF is
	Port(Clk, En, reset	:IN std_logic;
		  D				:IN std_logic_vector(15 downto 0);
		  Q				:OUT std_logic_vector(15 downto 0));
END component;

component Mod16 is
	port(Clk, En, reset  :in std_logic;
		Output,  flag	 :out std_logic);
	end component;
	
component Mux is
	port(Enable				:in std_logic_vector(1 downto 0);
		Input				:in std_logic;
		GPIO  				:out std_logic);
end component;

component ShiftReg is
	Port(Clk, Load, Shift, reset	:IN std_logic;
		  En						:IN std_logic_vector(1 downto 0);
		  D							:IN std_logic_vector(15 downto 0);
		  Output					:OUT std_logic);
END component;

component SSD is
port(Input						  	:in std_logic_vector(15 downto 0);
	HEX0, HEX1, HEX2, HEX3     		:out std_logic_vector(6 downto 0));
end component;

component StateMachine is
	port(clk, reset													:in std_logic;
		Key1, Key2, Timer, Counter_1us							  	:in std_logic;
		SH, LD, Shift_En, Timer_En, Pin_En, Key_En, XOR_En			:out std_logic;
		Mux_sel 													:out std_logic_vector(1 downto 0));
end component;

component Xor1 is
	Port(Clk, En, reset		:IN std_logic;
		  Input1, Input2	:IN std_logic_vector(15 downto 0);
		  Output			:OUT std_logic_vector(15 downto 0));
END component;

Begin

One_us:clk
	port map(
		clk_50Mhz => int_clk, 	
		clk => clk_1us,				
		reset => reset,
		En => Timer_En);
		
PIN_Reg:D_FF
	port map(
		Clk => int_clk,
		reset => reset,
		En	=> Pin_En,
		D => SW,
		Q => Q_Pin);

Encrypt_Reg:D_FF
	port map(
		Clk => int_clk, 
		reset => reset,
		En	=> Key_En,
		D => SW,
		Q => Q_Encrypt);
	
XOR_Reg:XOR1
	port map(
		Clk => int_clk,
		reset => reset,
		En => XOR_En,			
		Input1 => Q_Pin, 
		Input2 => Q_Encrypt,	
		Output => D_shift);	
	
FSM:StateMachine
	port map(
		clk => int_clk, 
		reset => reset,																	
		Key1 => Key1, 
		Key2 => Key2, 
		Timer => Counter,
		Counter_1us => flag,
		SH => SH, 
		LD => LD, 
		Mux_sel => Mux_sel, 
		Shift_En => Shift_En, 
		Timer_En => Timer_En, 
		Pin_En => Pin_En, 
		Key_En => Key_En, 
		XOR_En => XOR_En);
	
Transmit_Counter:MOD16
	port map(
		Clk => int_clk, 
		En => clk_1us,
		flag => flag,
		reset => reset,  
		Output => Counter);
		
Mux_3to1:Mux
	port map(
		Enable => Mux_sel,				
		Input => data,					
		GPIO => GPIO);
		
Transmit_Shift:ShiftReg
	port map(
		Clk => int_clk, 
		Load => LD, 
		Shift => SH, 
		reset => reset,	
		En(0) => clk_1us,
		En(1) => Shift_En,
		D => D_shift,				
		Output => data);
		
Display:SSD
	port map(
		Input => Q_Pin,
		HEX0 => hex0, 
		HEX1 => hex1, 
		HEX2 => hex2, 
		HEX3 => hex3);
end arc;