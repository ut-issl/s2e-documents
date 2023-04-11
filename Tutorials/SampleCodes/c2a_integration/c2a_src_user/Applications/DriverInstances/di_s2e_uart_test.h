/**
 * @file
 * @brief An example of driver Instance for UART cmmunication test with S2E
 */
#ifndef DI_S2E_UART_TEST_H_
#define DI_S2E_UART_TEST_H_

#include <src_core/System/ApplicationManager/app_info.h>
#include <src_core/IfWrapper/uart.h>

/**
 * @struct S2eUartTest
 * @brief  Struct for S2E UART TEST
 * @note   TODO: Move this struct to Driver
 */
typedef struct
{
  UART_Config uart_config;     //!< UART communication instance TODO: move to Driver
  unsigned char rx_data[100];  //!< Received data
  unsigned char tx_data[5];    //!< Transmission data
} S2eUartTest;

extern const S2eUartTest* s2e_uart_test_instance;

AppInfo DI_S2E_UART_TEST_update(void);
AppInfo DI_S2E_UART_TEST_debug_output(void);

#endif // DI_S2E_UART_TEST_H_
