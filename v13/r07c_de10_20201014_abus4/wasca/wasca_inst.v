	wasca u0 (
		.abus_avalon_sdram_bridge_0_abus_address           (<connected-to-abus_avalon_sdram_bridge_0_abus_address>),           //  abus_avalon_sdram_bridge_0_abus.address
		.abus_avalon_sdram_bridge_0_abus_read              (<connected-to-abus_avalon_sdram_bridge_0_abus_read>),              //                                 .read
		.abus_avalon_sdram_bridge_0_abus_waitrequest       (<connected-to-abus_avalon_sdram_bridge_0_abus_waitrequest>),       //                                 .waitrequest
		.abus_avalon_sdram_bridge_0_abus_addressdata       (<connected-to-abus_avalon_sdram_bridge_0_abus_addressdata>),       //                                 .addressdata
		.abus_avalon_sdram_bridge_0_abus_chipselect        (<connected-to-abus_avalon_sdram_bridge_0_abus_chipselect>),        //                                 .chipselect
		.abus_avalon_sdram_bridge_0_abus_direction         (<connected-to-abus_avalon_sdram_bridge_0_abus_direction>),         //                                 .direction
		.abus_avalon_sdram_bridge_0_abus_disable_out       (<connected-to-abus_avalon_sdram_bridge_0_abus_disable_out>),       //                                 .disable_out
		.abus_avalon_sdram_bridge_0_abus_interrupt         (<connected-to-abus_avalon_sdram_bridge_0_abus_interrupt>),         //                                 .interrupt
		.abus_avalon_sdram_bridge_0_abus_muxing            (<connected-to-abus_avalon_sdram_bridge_0_abus_muxing>),            //                                 .muxing
		.abus_avalon_sdram_bridge_0_abus_writebyteenable_n (<connected-to-abus_avalon_sdram_bridge_0_abus_writebyteenable_n>), //                                 .writebyteenable_n
		.abus_avalon_sdram_bridge_0_abus_reset             (<connected-to-abus_avalon_sdram_bridge_0_abus_reset>),             //                                 .reset
		.abus_avalon_sdram_bridge_0_sdram_addr             (<connected-to-abus_avalon_sdram_bridge_0_sdram_addr>),             // abus_avalon_sdram_bridge_0_sdram.addr
		.abus_avalon_sdram_bridge_0_sdram_ba               (<connected-to-abus_avalon_sdram_bridge_0_sdram_ba>),               //                                 .ba
		.abus_avalon_sdram_bridge_0_sdram_cas_n            (<connected-to-abus_avalon_sdram_bridge_0_sdram_cas_n>),            //                                 .cas_n
		.abus_avalon_sdram_bridge_0_sdram_cke              (<connected-to-abus_avalon_sdram_bridge_0_sdram_cke>),              //                                 .cke
		.abus_avalon_sdram_bridge_0_sdram_cs_n             (<connected-to-abus_avalon_sdram_bridge_0_sdram_cs_n>),             //                                 .cs_n
		.abus_avalon_sdram_bridge_0_sdram_dq               (<connected-to-abus_avalon_sdram_bridge_0_sdram_dq>),               //                                 .dq
		.abus_avalon_sdram_bridge_0_sdram_dqm              (<connected-to-abus_avalon_sdram_bridge_0_sdram_dqm>),              //                                 .dqm
		.abus_avalon_sdram_bridge_0_sdram_ras_n            (<connected-to-abus_avalon_sdram_bridge_0_sdram_ras_n>),            //                                 .ras_n
		.abus_avalon_sdram_bridge_0_sdram_we_n             (<connected-to-abus_avalon_sdram_bridge_0_sdram_we_n>),             //                                 .we_n
		.abus_avalon_sdram_bridge_0_sdram_clk              (<connected-to-abus_avalon_sdram_bridge_0_sdram_clk>),              //                                 .clk
		.altpll_1_areset_conduit_export                    (<connected-to-altpll_1_areset_conduit_export>),                    //          altpll_1_areset_conduit.export
		.altpll_1_locked_conduit_export                    (<connected-to-altpll_1_locked_conduit_export>),                    //          altpll_1_locked_conduit.export
		.altpll_1_phasedone_conduit_export                 (<connected-to-altpll_1_phasedone_conduit_export>),                 //       altpll_1_phasedone_conduit.export
		.buffered_spi_mosi                                 (<connected-to-buffered_spi_mosi>),                                 //                     buffered_spi.mosi
		.buffered_spi_clk                                  (<connected-to-buffered_spi_clk>),                                  //                                 .clk
		.buffered_spi_miso                                 (<connected-to-buffered_spi_miso>),                                 //                                 .miso
		.buffered_spi_cs                                   (<connected-to-buffered_spi_cs>),                                   //                                 .cs
		.clk_clk                                           (<connected-to-clk_clk>),                                           //                              clk.clk
		.clock_116_mhz_clk                                 (<connected-to-clock_116_mhz_clk>),                                 //                    clock_116_mhz.clk
		.extra_leds_conn_export                            (<connected-to-extra_leds_conn_export>),                            //                  extra_leds_conn.export
		.hex0_conn_export                                  (<connected-to-hex0_conn_export>),                                  //                        hex0_conn.export
		.hex1_conn_export                                  (<connected-to-hex1_conn_export>),                                  //                        hex1_conn.export
		.hex2_conn_export                                  (<connected-to-hex2_conn_export>),                                  //                        hex2_conn.export
		.hex3_conn_export                                  (<connected-to-hex3_conn_export>),                                  //                        hex3_conn.export
		.hex4_conn_export                                  (<connected-to-hex4_conn_export>),                                  //                        hex4_conn.export
		.hex5_conn_export                                  (<connected-to-hex5_conn_export>),                                  //                        hex5_conn.export
		.hexdot_conn_export                                (<connected-to-hexdot_conn_export>),                                //                      hexdot_conn.export
		.leds_conn_export                                  (<connected-to-leds_conn_export>),                                  //                        leds_conn.export
		.reset_reset_n                                     (<connected-to-reset_reset_n>),                                     //                            reset.reset_n
		.reset_controller_0_reset_in1_reset                (<connected-to-reset_controller_0_reset_in1_reset>),                //     reset_controller_0_reset_in1.reset
		.spi_sync_conn_export                              (<connected-to-spi_sync_conn_export>),                              //                    spi_sync_conn.export
		.switches_conn_export                              (<connected-to-switches_conn_export>),                              //                    switches_conn.export
		.uart_0_external_connection_rxd                    (<connected-to-uart_0_external_connection_rxd>),                    //       uart_0_external_connection.rxd
		.uart_0_external_connection_txd                    (<connected-to-uart_0_external_connection_txd>)                     //                                 .txd
	);
