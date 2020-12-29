#ifndef APP_REGISTRY_H_
#define APP_REGISTRY_H_
// こいつの自動生成がほしい．．．
typedef enum
{
  AR_NOP,                 // 0
  AR_MW_CCSDS_RX,
  AR_MW_CCSDS_MS_TX,
  AR_MW_DC_RX,
  AR_MW_FLASH,
  AR_DI_RS422_DUMMY,   // 使ってないので
  AR_DI_GSTOS_CMD_PH,
  // AR_DI_GSTOS_HKT_PH,    // EQUではない．
  AR_DI_GSTOS_MST_PH,
  AR_DI_GSTOS_RPT_PH,
  AR_DI_GSTOS_PRINT_TCF_INFO,
  AR_DI_GSTOS_PRINT_TCP_INFO,
  AR_DI_GSTOS_PRINT_CLCW_INFO,   // 10
  AR_DI_PCU_UPDATE,
  AR_DI_XTRP_UPDATE,
  AR_DI_WIRED_UPDATE,
  AR_GSC_DISPATCHER,
  AR_RTC_DISPATCHER,
  AR_TLC0_DISPATCHER,
  AR_TLC1_DISPATCHER,
  AR_TLC2_DISPATCHER,
  AR_ANOMALY_HANDLER,
  AR_MEM_DUMP,
  AR_FLASH_UTILITY,            // 29
  AR_FLASH_PARTITIONING,  // DRなど，FLASH PTNを使うアプリより先に初期化すること！
  AR_FLASH_BIG_DATA,
  AR_DR_RECORDER,          // 32 → 0
  AR_UTILITY_CMD,
  AR_UTILITY_COUNTER,
  AR_SRAM_SCRUBBER,
  AR_MRAM_UTILITY,
  AR_RESET_UTILITY,
  AR_OBC_COMMAND,
  AR_ALL_REPRO,
  AR_DBG_FLUSH_SCREEN, //DEBU
  AR_DBG_PRINT_TIMESTAMP,     // 52 → 20
  AR_DBG_PRINT_CMD_STATUS,
  AR_DBG_PRINT_PCU_STATUS,
  AR_DBG_AH_STATUS,
  AR_DBG_PRINT_XTRP_STATUS,
  AR_DBG_ONE_BIT,     // 62 → 30
  AR_RECORD_TI,
  AR_UART_FAULT_RECOVERY,
  AR_DI_HILS_UPDATE,
} AR_APP_ID;

void AR_load_initial_settings(void);

#endif // APP_REGISTRY_H_
