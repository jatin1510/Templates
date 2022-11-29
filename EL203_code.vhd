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
entity elevator is
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
end elevator;

architecture Behavioral of elevator is 
signal state:integer:=0;
signal s3:std_logic:='0'; 
signal s4:std_logic:='0';
signal s5:std_logic:='0'; 
signal s6:std_logic:='0';

begin
    check:process (RESET, SBT, SMM, SMP, STP, PB1, PB2, PB3) 
        begin
        if (RESET='0') then
            state<=0;
        end if;
        
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

        if (state=0) then
            state0 <= '1';
            state1 <= '0'; 
            state2 <= '0';
            state3 <= '0';
            state4 <= '0';
            state5 <= '0';
            state6 <= '0';
            s3 <= '0';
            s4 <= '0';
            s5 <= '0';
            s6 <= '0';
            led_f1 <= '1';
            led_f2 <= '0';
            led_f3 <= '0';
        elsif (state=1) then
            state0 <= '0';
            state1 <= '1'; 
            state2 <= '0';
            state3 <= '0';
            state4 <= '0';
            state5 <= '0';
            state6 <= '0';
            s3 <= '0';
            s4 <= '0';
            s5 <= '0';
            s6 <= '0';
            led_f1 <= '0';
            led_f2 <= '1';
            led_f3 <= '0';
        elsif (state=2) then
            state0 <= '0';
            state1 <= '0'; 
            state2 <= '1';
            state3 <= '0';
            state4 <= '0';
            state5 <= '0';
            state6 <= '0';
            s3 <= '0';
            s4 <= '0';
            s5 <= '0';
            s6 <= '0';
            led_f1 <= '0';
            led_f2 <= '0';
            led_f3 <= '1';
        elsif (state=3) then
            state0 <= '0';
            state1 <= '0'; 
            state2 <= '0';
            state3 <= '1';
            state4 <= '0';
            state5 <= '0';
            state6 <= '0';
            s3 <= '1';
            s4 <= '0';
            s5 <= '0';
            s6 <= '0';
            led_f1 <= '0';
            led_f2 <= '0';
            led_f3 <= '0';
        elsif (state=4) then
            state0 <= '0';
            state1 <= '0'; 
            state2 <= '0';
            state3 <= '0';
            state4 <= '1';
            state5 <= '0';
            state6 <= '0';
            s3 <= '0';
            s4 <= '1';
            s5 <= '0';
            s6 <= '0';
            led_f1 <= '0';
            led_f2 <= '0';
            led_f3 <= '0';
        elsif (state=5) then
            state0 <= '0';
            state1 <= '0'; 
            state2 <= '0';
            state3 <= '0';
            state4 <= '0';
            state5 <= '1';
            state6 <= '0';
            s3 <= '0';
            s4 <= '0';
            s5 <= '1';
            s6 <= '0';
            led_f1 <= '0';
            led_f2 <= '0';
            led_f3 <= '0';
        elsif (state=6) then
            state0 <= '0';
            state1 <= '0'; 
            state2 <= '0';
            state3 <= '0';
            state4 <= '0';
            state5 <= '0';
            state6 <= '1';
            s3 <= '0';
            s4 <= '0';
            s5 <= '0';
            s6 <= '1';
            led_f1 <= '0';
            led_f2 <= '0';
            led_f3 <= '0';
        end if;
    end process;

    M0 <= s5 or s6;
    M1 <= s3 or s4;
    
end Behavioral;