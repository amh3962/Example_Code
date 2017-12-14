--Aaron Halling
--Lab 11 - StateMachine
library IEEE;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
entity StateMachine is
	port(clk, reset												:in std_logic;
		Key1, Key2, Timer, Counter_1us							:in std_logic;
		SH, LD, Shift_En, Timer_En, Pin_En, Key_En, XOR_En		:out std_logic;
		Mux_sel													:out std_logic_vector(1 downto 0));
end StateMachine;

architecture arc of StateMachine is
type state_type is (Idle, Pin_Lock, Pin_Locked, Encrypt_Lock, XOR_State, Load, Transmit);
signal current_state, next_state : state_type;
begin
sync: Process(clk, reset)
	Begin
		if (reset = '0') then
			current_state <= Idle;
		elsif (rising_edge(clk)) then
			current_state <= next_state;
		end if;
	end process;
	
comb: Process(current_state, next_state, Key1, Key2, Timer)
	Begin
		Case (current_state) is
			When Idle =>
				if Key1 = '0' then
					next_state <= Pin_Lock;
				else
					next_state <= Idle;
				end if;
			When Pin_Lock =>
				next_state <= Pin_Locked;
			When Pin_Locked =>
				if Key2 = '0' then
					next_state <= Encrypt_Lock;
				else 
					next_state <= Pin_Locked;
				end if;
			When Encrypt_Lock =>
				next_state <= XOR_State;
			When XOR_State =>
				next_state <= Load;
			When Load =>
				next_state <= Transmit;
			When Transmit =>
				if Timer = '1' then
					next_state <= Idle;
				else 
					next_state <= Transmit;
				end if;
		end case;
	end process;
	
Output: Process (current_state, Counter_1us)
	Begin
		Case (current_state) is
			When Idle =>
				SH <= '0';
				LD <= '0';
				Mux_sel <= "00";
				Shift_En <= '0';
				Timer_En <= '0';
				Pin_En <= '0';
				Key_En <= '0';
				XOR_En <= '0';
			When Pin_Lock =>
				SH <= '0';
				LD <= '0';
				Mux_sel <= "00";
				Shift_En <= '0';
				Timer_En <= '0';
				Pin_En <= '1';
				Key_En <= '0';
				XOR_En <= '0';
			When Pin_Locked =>
				SH <= '0';
				LD <= '0';
				Mux_sel <= "00";
				Shift_En <= '0';
				Timer_En <= '0';
				Pin_En <= '0';
				Key_En <= '0';
				XOR_En <= '0';
			When Encrypt_Lock =>
				SH <= '0';
				LD <= '0';
				Mux_sel <= "00";
				Shift_En <= '0';
				Timer_En <= '0';
				Pin_En <= '0';
				Key_En <= '1';
				XOR_En <= '0';
			When XOR_State =>
				SH <= '0';
				LD <= '0';
				Mux_sel <= "00";
				Shift_En <= '0';
				Timer_En <= '0';
				Pin_En <= '0';
				Key_En <= '0';
				XOR_En <= '1';
			When Load =>
				SH <= '0';
				LD <= '1';
				Mux_sel <= "00";
				Shift_En <= '0';
				Timer_En <= '0';
				Pin_En <= '0';
				Key_En <= '0';
				XOR_En <= '0';
			When Transmit =>
				SH <= '1';
				LD <= '0';
				Shift_En <= '1';
				Timer_En <= '1';
				Pin_En <= '0';
				Key_En <= '0';
				XOR_En <= '0';
				if (Counter_1us = '1') then
					Mux_sel <= "10"; --select data
				elsif(Timer = '1') then
					Mux_sel <= "00"; -- select '1' for end of transmittion
				else
					Mux_sel <= "01"; -- output '0' for 1us
				end if;
			end case;
		end process;
	end arc;