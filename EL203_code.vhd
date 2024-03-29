-- arithmetic functions with Signed or Unsigned values
--use IEEE. NUMERIC_STD. ALL;
-- Uncomment the following library declaration if instantiating any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM. VComponents.all;
----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    21:10:30 11/26/2022 
-- Design Name: 
-- Module Name:    code - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;
entity abcd is
Port (  RESET: in STD_LOGIC;
        SBT: in STD_LOGIC;
        SMM: in STD_LOGIC;
        SMP: in STD_LOGIC;
        STP: in STD_LOGIC;
        PB1: in STD_LOGIC;
        PB2: in STD_LOGIC;
        PB3: in STD_LOGIC;
        state0: out STD_LOGIC;
        state1: out STD_LOGIC;
        state2: out STD_LOGIC;
        state3: out STD_LOGIC;
        state4: out STD_LOGIC;
        state5: out STD_LOGIC;
        state6: out STD_LOGIC;
        M0: out STD_LOGIC;
        M1: out STD_LOGIC;
		  led_f1: out STD_LOGIC;
		  led_f2: out STD_LOGIC;
		  led_f3: out STD_LOGIC
);
end abcd;

architecture Behavioral of abcd is 
signal state:integer:=0;
signal up:std_logic:='0'; 
signal down:std_logic:='0';

begin
    check:process (RESET, SBT, SMM, SMP, STP, PB1, PB2, PB3) 
    begin
    if (RESET/='0') then
        if (PB1='1' and PB2='0' and PB3='0') then
            if (state=1 or state=2) then
                state<=6;
            end if;
        elsif (PB1='0' and PB2='1' and PB3='0') then 
            if (state=0) then 
                state<=3;
            elsif (state=2) then
                state<=5;
            end if;
        elsif (PB1='0' and PB2='0' and PB3='1') then 
            if (state=0 or state=1) then
                state<=4;
            end if; 
        end if;

        if(SBT='1' and SMM='0' and SMP='0' and STP='0') then
            if (state=6) then
                state<=0;
            end if;
        elsif (SBT='0' and SMM='1' and SMP='1' and STP='0') then
            if (state=5 or state=3) then
                state<=1;
            end if;
        elsif (SBT='0' and SMM='0' and SMP='0' and STP='1') then
            if (state=4) then
                state<=2;
            end if;
        end if;
    else
        state<=6;
    end if;
    
    state0 <= '0';
    state1 <= '0'; 
    state2 <= '0';
    state3 <= '0';
    state4 <= '0';
    state5 <= '0';
    state6 <= '0';
    led_f1 <= '0';
	led_f2 <= '0';
	led_f3 <= '0';

    if (state=0) then
        state0 <= '1';
        up <= '0';
        down <= '0';
		led_f1 <= '1';
    elsif (state=1) then
        state1 <= '1'; 
        up <= '0';
        down <= '0';
		led_f2 <= '1';
    elsif (state=2) then
        state2 <= '1';
        up <= '0';
        down <= '0';
		led_f3 <= '1';
    elsif (state=3) then
        state3 <= '1';
        up <= '1';
        down <= '0';
    elsif (state=4) then
        state4 <= '1';
        up <= '1';
        down <= '0';
    elsif (state=5) then
        state5 <= '1';
        up <= '0';
        down <= '1';
    elsif (state=6) then
        state6 <= '1';
        up <= '0';
        down <= '1';
    end if;

    end process;

    M0 <= down;
    M1 <= up;
end Behavioral;