#pragma section REPRO
#include "AppRegistry.h"

#include "../../src_core/System/ApplicationManager/AppManager.h"

#include "AppHeaders.h"

static AM_ACK add_application_(size_t id,
                               AppInfo (*app_creator)(void));
void AR_load_initial_settings(void)
{
  add_application_(AR_NOP, create_nop_task);
  add_application_(AR_MW_CCSDS_RX, CCSDS_MW_rx);
  add_application_(AR_MW_CCSDS_MS_TX, CCSDS_MW_ms_tx);
  add_application_(AR_MW_DC_RX, DC_MW_rx);
  add_application_(AR_MW_FLASH, FLASH_MW_update);
  add_application_(AR_DI_RS422_DUMMY, RS422_create_dummy);
  add_application_(AR_DI_GSTOS_CMD_PH, GSTOS_cmd_packet_handler);
  add_application_(AR_DI_GSTOS_MST_PH, GSTOS_mst_packet_handler);
  add_application_(AR_DI_GSTOS_RPT_PH, GSTOS_rpt_packet_handler);
  add_application_(AR_DI_GSTOS_PRINT_TCF_INFO, GSTOS_print_tcf_info);
  add_application_(AR_DI_GSTOS_PRINT_TCP_INFO, GSTOS_print_tcp_info);
  add_application_(AR_DI_GSTOS_PRINT_CLCW_INFO, GSTOS_print_clcw_info);
  add_application_(AR_DI_PCU_UPDATE, pcu_update);
  add_application_(AR_DI_XTRP_UPDATE, xtrp_update);
  add_application_(AR_DI_WIRED_UPDATE, WDFAR_update);
  add_application_(AR_GSC_DISPATCHER, gs_cmd_dispatcher);
  add_application_(AR_RTC_DISPATCHER, rt_cmd_dispatcher);
  add_application_(AR_TLC0_DISPATCHER, tlc0_dispatcher);
  add_application_(AR_TLC1_DISPATCHER, tlc1_dispatcher);
  add_application_(AR_TLC2_DISPATCHER, tlc2_dispatcher);
  add_application_(AR_ANOMALY_HANDLER, AH_create_app);
  add_application_(AR_MEM_DUMP, MEM_create_app);
  add_application_(AR_FLASH_UTILITY, FLASH_create_app);
  add_application_(AR_FLASH_PARTITIONING, FLASH_PTN_create_app);  // DRなど，FLASH PTNを使うアプリより先に初期化すること
  add_application_(AR_FLASH_BIG_DATA, FLASH_BD_create_app);
  add_application_(AR_DR_RECORDER, DR_recorder);
  add_application_(AR_UTILITY_CMD, init_util_cmd_status);
  add_application_(AR_UTILITY_COUNTER, init_util_counter_status);
  add_application_(AR_SRAM_SCRUBBER, RamScrubber_create_app);
  add_application_(AR_MRAM_UTILITY, MRAM_create_app);
  add_application_(AR_RESET_UTILITY, RESET_create_app);
  add_application_(AR_OBC_COMMAND, OBC_create_app);
  add_application_(AR_ALL_REPRO, ARP_create_app);
  add_application_(AR_DBG_FLUSH_SCREEN, flush_screen);
  add_application_(AR_DBG_PRINT_TIMESTAMP, print_time_stamp);
  add_application_(AR_DBG_PRINT_CMD_STATUS, print_cmd_status);
  add_application_(AR_DBG_PRINT_PCU_STATUS, print_pcu_status);
  add_application_(AR_DBG_AH_STATUS, print_ah_status);
  add_application_(AR_DBG_PRINT_XTRP_STATUS, print_xtrp_status);
  add_application_(AR_DBG_ONE_BIT, one_bit_communication_print);
  add_application_(AR_RECORD_TI, RTI_create_app);    // MRAMよりあと
  add_application_(AR_UART_FAULT_RECOVERY, UART_FAULT_RECOVERY_create_app);
  add_application_(AR_DI_HILS_UPDATE, hils_update);
}

static AM_ACK add_application_(size_t id,
                               AppInfo (*app_creator)(void))
{
  AppInfo ai = app_creator();
  return AM_register_ai(id, &ai);
}
#pragma section
