#pragma section REPRO
/**
 * @file   di_s2e_uart_test.h
 * @brief  S2Eを使ったUART通信テスト用アプリ
 */

#include "di_s2e_uart_test.h"

#include <stddef.h> // for NULL
#include <src_core/IfWrapper/uart.h>
#include <src_core/Library/print.h>


static UART_Config S2E_UART_TEST_channel_;
static uint8_t S2E_UART_TEST_port_id_ = 1;
static uint8_t S2E_UART_TEST_count_ = 0;

static void S2E_UART_TEST_init_(void);
static void S2E_UART_TEST_update_(void);

AppInfo S2E_UART_TEST_update(void)
{
  return AI_create_app_info("s2e_uart_test", S2E_UART_TEST_init_, S2E_UART_TEST_update_);
}

static void S2E_UART_TEST_init_(void)
{
  S2E_UART_TEST_channel_.ch = S2E_UART_TEST_port_id_;
  S2E_UART_TEST_channel_.baudrate = 115200;
  S2E_UART_TEST_channel_.stop_bit = UART_STOP_BIT_1BIT;
}

static void S2E_UART_TEST_update_(void)
{
  uint8_t test_tx_data_[5] = {'S', 'E', 'T', 'A', '\n'};
  uint8_t test_rx_data_[100];
  uint8_t i;
  // Send
  test_tx_data_[3] = 'A' + S2E_UART_TEST_count_;
  UART_tx(&S2E_UART_TEST_channel_, test_tx_data_, 5);
  S2E_UART_TEST_count_++;
  if(S2E_UART_TEST_count_ >= 26) S2E_UART_TEST_count_ = 0;

  // Receive
  UART_rx(&S2E_UART_TEST_channel_, &test_rx_data_, 100);
  Printf("S2E_UART_TEST: received data = ");
  for (i = 0; i < 3; i++)
  {
    Printf("%c, ", test_rx_data_[i]);
  }
  Printf("\n");
}

#pragma section
