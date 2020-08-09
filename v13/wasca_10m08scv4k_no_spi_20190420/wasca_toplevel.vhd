-- wasca.vhd

-- Generated using ACDS version 14.1 186 at 2015.05.28.08:37:08

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;


entity wasca_toplevel is
	port (
		clk_clk                                     : in    std_logic                     := '0';             -- Saturn clock (22.579 MHz)
		external_sdram_controller_wire_addr         : out   std_logic_vector(12 downto 0);                    -- external_sdram_controller_wire.addr
		external_sdram_controller_wire_ba           : out   std_logic_vector(1 downto 0);                     -- .ba
		external_sdram_controller_wire_cas_n        : out   std_logic;                                        -- .cas_n
		external_sdram_controller_wire_cke          : out   std_logic;                                        -- .cke
		external_sdram_controller_wire_cs_n         : out   std_logic;                                        -- .cs_n
		external_sdram_controller_wire_dq           : inout std_logic_vector(15 downto 0) := (others => '0'); -- .dq
		external_sdram_controller_wire_dqm          : out   std_logic_vector(1 downto 0);                     -- .dqm
		external_sdram_controller_wire_ras_n        : out   std_logic;                                        -- .ras_n
		external_sdram_controller_wire_we_n         : out   std_logic;                                        -- .we_n
		external_sdram_clk_pin                      : out   std_logic;                                        -- .clk
		reset_reset_n                               : in    std_logic                     := '0';             -- Saturn reset, power on.
		abus_slave_0_abus_address                   : in    std_logic_vector(24 downto 16) := (others => '0'); --  abus_slave_0_abus.address
		abus_slave_0_abus_addressdata               : inout std_logic_vector(15 downto 0) := (others => '0'); --                               .data
		abus_slave_0_abus_chipselect                : in    std_logic_vector(2 downto 0)  := (others => '0'); --                               .chipselect
		abus_slave_0_abus_read                      : in    std_logic                     := '0';             --                               .read
		abus_slave_0_abus_write                     : in    std_logic_vector(1 downto 0)  := (others => '0'); --                               .write
		abus_slave_0_abus_waitrequest               : out   std_logic;                                        --                               .waitrequest
		abus_slave_0_abus_interrupt                 : out    std_logic                     := '0';            --                               .interrupt
		abus_slave_0_abus_disableout                : out   std_logic                     := '0';             --                               .muxing
		abus_slave_0_abus_muxing                    : out   std_logic_vector(1	 downto 0)  := (others => '0'); --                               .muxing
		abus_slave_0_abus_direction                 : out   std_logic                     := '0';              --                               .direction
		--spi_sd_card_MISO                                           : in    std_logic                := '0';   -- MISO
		--spi_sd_card_MOSI                                           : out   std_logic;                         -- MOSI
		--spi_sd_card_SCLK                                           : out   std_logic;                         -- SCLK
		--spi_sd_card_SS_n                                           : out   std_logic;                         -- SS_n
		uart_0_external_connection_txd : out   std_logic                     := '0';                          -- 
		uart_0_external_connection_rxd : in    std_logic                     := 'X';                          -- 
		leds_conn_export                                           : out std_logic_vector(2 downto 0); -- leds_conn_export[0]: ledr1, leds_conn_export[1]: ledg1, leds_conn_export[2]: ledr2
		switches_conn_export                                       : in  std_logic_vector(2 downto 0)  -- switches_conn_export[0]: sw1, switches_conn_export[1]: sw2, switches_conn_export[2]: STM32 SPI synchronization
		--spi_stm32_MISO                              : in    std_logic;                                        -- MISO
		--spi_stm32_MOSI                              : out   std_logic                     := '0';             -- MOSI
		--spi_stm32_SCLK                              : out   std_logic                     := '0';             -- SCLK
		--spi_stm32_SS_n                              : out   std_logic                     := '0'              -- SS_n
		--audio_out_BCLK                              : in    std_logic                     := '0';             -- BCLK
		--audio_out_DACDAT                            : out   std_logic;                                        -- DACDAT
		--audio_out_DACLRCK                           : in    std_logic                     := '0';             -- DACLRCK
		--audio_SSEL                                  : out    std_logic                     := '0'
	);
end entity wasca_toplevel;

architecture rtl of wasca_toplevel is

	component wasca is
		port (
			sdram_clkout_clk                            : out   std_logic;                                        -- clk
			altpll_0_areset_conduit_export              : in    std_logic                     := '0';             --        altpll_0_areset_conduit.export
			altpll_0_locked_conduit_export              : out   std_logic;                                        --        altpll_0_locked_conduit.export
			altpll_0_phasedone_conduit_export           : out   std_logic;                                        --     altpll_0_phasedone_conduit.export
			clk_clk                                     : in    std_logic                     := '0';             --                            clk.clk
			clock_116_mhz_clk                           : out   std_logic ;                                        -- cl
			external_sdram_controller_wire_addr         : out   std_logic_vector(12 downto  0);                    -- external_sdram_controller_wire.addr
			external_sdram_controller_wire_ba           : out   std_logic_vector( 1 downto  0);                                        --                               .ba
			external_sdram_controller_wire_cas_n        : out   std_logic;                                        --                               .cas_n
			external_sdram_controller_wire_cke          : out   std_logic;                                        --                               .cke
			external_sdram_controller_wire_cs_n         : out   std_logic;                                        --                               .cs_n
			external_sdram_controller_wire_dq           : inout std_logic_vector(15 downto  0) := (others => '0'); --                               .dq
			external_sdram_controller_wire_dqm          : out   std_logic_vector( 1 downto  0);                     --                               .dqm
			external_sdram_controller_wire_ras_n        : out   std_logic;                                        --                               .ras_n
			external_sdram_controller_wire_we_n         : out   std_logic;                                        --                               .we_n
			abus_slave_0_abus_address                   : in    std_logic_vector( 8 downto  0)  := (others => '0'); --  abus_slave_0_abus.address
			abus_slave_0_abus_chipselect                : in    std_logic_vector( 2 downto  0)  := (others => '0'); --                               .chipselect
			abus_slave_0_abus_read                      : in    std_logic                       := '0';             --                               .read
			abus_slave_0_abus_write                     : in    std_logic_vector( 1 downto  0)  := (others => '0'); --                               .write
			abus_slave_0_abus_waitrequest               : out   std_logic;                                        --                               .waitrequest
			abus_slave_0_abus_interrupt                 : out   std_logic                       := '0';             --                               .interrupt
			abus_slave_0_abus_addressdata               : inout std_logic_vector(15 downto  0) := (others => '0');  --                               .writedata
			abus_slave_0_abus_direction                 : out   std_logic := '0';
			abus_slave_0_abus_muxing                    : out   std_logic_vector( 1 downto  0) := (others => '0'); 
			abus_slave_0_abus_disableout                : out   std_logic                       := '0' ;             --                               .muxing
			abus_slave_0_conduit_saturn_reset_saturn_reset  : in    std_logic                     := '0';              -- saturn_reset
			--spi_sd_card_MISO                                           : in    std_logic                     := '0';             -- MISO
			--spi_sd_card_MOSI                                           : out   std_logic;                                        -- MOSI
			--spi_sd_card_SCLK                                           : out   std_logic;                                        -- SCLK
			--spi_sd_card_SS_n                                           : out   std_logic;                                        -- SS_n
			uart_0_external_connection_rxd                             : in    std_logic                     := '0';             -- rxd
			uart_0_external_connection_txd                             : out   std_logic;                                        -- txd
			leds_conn_export                                           : out   std_logic_vector(2 downto 0);
			switches_conn_export                                       : in    std_logic_vector(2 downto 0)
			--spi_stm32_MISO                                             : in    std_logic                     := '0';             -- MISO
			--spi_stm32_MOSI                                             : out   std_logic                     := '0';             -- MOSI
			--spi_stm32_SCLK                                             : out   std_logic                     := '0';             -- SCLK
			--spi_stm32_SS_n                                             : out   std_logic                     := '0'              -- SS_n
			--audio_out_BCLK                                             : in    std_logic                     := '0';             -- BCLK
			--audio_out_DACDAT                                           : out   std_logic;                                        -- DACDAT
			--audio_out_DACLRCK                                          : in    std_logic                     := '0'              -- DACLRCK
		);
	end component;

	--signal altpll_0_areset_conduit_export : std_logic := '0';
	signal altpll_0_locked_conduit_export : std_logic := '0';
	--signal altpll_0_phasedone_conduit_export : std_logic := '0';
	
	--signal abus_slave_0_abus_address_demuxed : std_logic_vector(25 downto 0) := (others => '0');
	--signal abus_slave_0_abus_data_demuxed : std_logic_vector(15 downto 0) := (others => '0');

	signal clock_116_mhz : std_logic := '0';

	begin

	--abus_slave_0_abus_muxing (0) <= not abus_slave_0_abus_muxing(1);

	my_little_wasca : component wasca
		port map (
			clk_clk => clk_clk,
			clock_116_mhz_clk => clock_116_mhz,
			external_sdram_controller_wire_addr => external_sdram_controller_wire_addr,
			external_sdram_controller_wire_ba => external_sdram_controller_wire_ba,
			external_sdram_controller_wire_cas_n => external_sdram_controller_wire_cas_n,
			external_sdram_controller_wire_cke => external_sdram_controller_wire_cke,
			external_sdram_controller_wire_cs_n => external_sdram_controller_wire_cs_n,
			external_sdram_controller_wire_dq => external_sdram_controller_wire_dq,
			external_sdram_controller_wire_dqm => external_sdram_controller_wire_dqm,
			external_sdram_controller_wire_ras_n => external_sdram_controller_wire_ras_n,
			external_sdram_controller_wire_we_n => external_sdram_controller_wire_we_n,
			abus_slave_0_abus_address => abus_slave_0_abus_address,
			abus_slave_0_abus_chipselect => "1"&abus_slave_0_abus_chipselect(1 downto 0),--work only with CS1 and CS0 for now
			--abus_slave_0_abus_chipselect => abus_slave_0_abus_chipselect,
			abus_slave_0_abus_read => abus_slave_0_abus_read,
			abus_slave_0_abus_write => abus_slave_0_abus_write,
			abus_slave_0_abus_waitrequest => abus_slave_0_abus_waitrequest,
			abus_slave_0_abus_interrupt => abus_slave_0_abus_interrupt,
			abus_slave_0_abus_addressdata => abus_slave_0_abus_addressdata,
			abus_slave_0_abus_direction => abus_slave_0_abus_direction,
			abus_slave_0_abus_muxing => abus_slave_0_abus_muxing,
			abus_slave_0_abus_disableout => abus_slave_0_abus_disableout,
			abus_slave_0_conduit_saturn_reset_saturn_reset => reset_reset_n,
			--spi_sd_card_MISO => spi_sd_card_MISO,
			--spi_sd_card_MOSI => spi_sd_card_MOSI,
			--spi_sd_card_SCLK => spi_sd_card_SCLK,
			--spi_sd_card_SS_n => spi_sd_card_SS_n,
			sdram_clkout_clk => external_sdram_clk_pin,
			altpll_0_areset_conduit_export => open,
			altpll_0_locked_conduit_export => altpll_0_locked_conduit_export,
			altpll_0_phasedone_conduit_export => open,
			uart_0_external_connection_rxd => uart_0_external_connection_rxd,
			uart_0_external_connection_txd => uart_0_external_connection_txd,
			leds_conn_export     => leds_conn_export,
			switches_conn_export => switches_conn_export
			--spi_stm32_MISO => spi_stm32_MISO,
			--spi_stm32_MOSI => spi_stm32_MOSI,
			--spi_stm32_SCLK => spi_stm32_SCLK,
			--spi_stm32_SS_n => spi_stm32_SS_n
			--audio_out_BCLK => audio_out_BCLK,
			--audio_out_DACDAT => audio_out_DACDAT,
			--audio_out_DACLRCK => audio_out_DACLRCK
		);
		
		--audio_SSEL <= '0';
		--abus_slave_0_abus_waitrequest <= '1';
		--abus_slave_0_abus_direction <= '0';
		--abus_slave_0_abus_muxing <= "01";

end architecture rtl; -- of wasca_toplevel
