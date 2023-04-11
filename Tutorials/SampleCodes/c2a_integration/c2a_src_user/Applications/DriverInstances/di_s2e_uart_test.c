/**
 * @file
 * @brief An example of driver Instance for UART cmmunication test with S2E
 */
#pragma section REPRO
#include "di_s2e_uart_test.h"

#include <stddef.h>

#include <src_core/Library/print.h>

static void S2E_UART_TEST_init_(void);
static void S2E_UART_TEST_update_(void);
static void S2E_UART_TEST_debug_output_(void);

static S2eUartTest s2e_uart_test_instance_;
const S2eUartTest* s2e_uart_test_instance;

AppInfo DI_S2E_UART_TEST_update(void)
{
  return AI_create_app_info("S2E UART TEST", S2E_UART_TEST_init_, S2E_UART_TEST_update_);
}

AppInfo DI_S2E_UART_TEST_debug_output(void)
{
  return AI_create_app_info("S2E UART TEST Debug", NULL, S2E_UART_TEST_debug_output_);
}

static void S2E_UART_TEST_init_(void)
{
  // Initialize UART communication
  s2e_uart_test_instance_.uart_config.ch = 1;
  s2e_uart_test_instance_.uart_config.baudrate = 115200;
  s2e_uart_test_instance_.uart_config.stop_bit = UART_STOP_BIT_1BIT;
  UART_init(&s2e_uart_test_instance_.uart_config);

  // Initialize TX data
  s2e_uart_test_instance_.tx_data[0] ='S';
  s2e_uart_test_instance_.tx_data[1] ='E';
  s2e_uart_test_instance_.tx_data[2] ='T';
  s2e_uart_test_instance_.tx_data[3] ='A';
  s2e_uart_test_instance_.tx_data[4] ='\n';

  return;
}

static void S2E_UART_TEST_update_(void)
{
  static unsigned char count = 0;
  // Send
  s2e_uart_test_instance_.tx_data[3] = 'A' + count;
  UART_tx(&s2e_uart_test_instance_.uart_config, s2e_uart_test_instance_.tx_data, 5);
  count++;
  if(count >= 26) count = 0;

  // Receive
  UART_rx(&s2e_uart_test_instance_.uart_config, s2e_uart_test_instance_.rx_data, 100);
}

static void S2E_UART_TEST_debug_output_(void)
{
  Printf("S2E_UART_TEST: received data = %c, %c, %c. \n", s2e_uart_test_instance_.rx_data[0],
                                                          s2e_uart_test_instance_.rx_data[1],
                                                          s2e_uart_test_instance_.rx_data[2]);
}
#pragma section
