#pragma section REPRO
#include "rs422_dummy.h"

#include <stddef.h> // for NULL

#include "../../Library/utility.h"
#include "../../../src_core/IF_Wrapper/RS422.h"
#include "../../Settings/Port_Config.h"

static RS422_CONFIG_STRUCT rs422_dummy_ch_[22];

static void rs422_dummy_init_(void);
static int init_each_dummy_(RS422_CONFIG_STRUCT* dummy,
                            unsigned char ch);

static void rs422_dummy_s2e_com(void);

AppInfo RS422_create_dummy(void)
{
  return create_app_info("dummy", rs422_dummy_init_, rs422_dummy_s2e_com);
}

static void rs422_dummy_init_(void)
{
  int i;
  for(i=0;i<12;i++)
  {
	init_each_dummy_(&rs422_dummy_ch_[i], i);
  }
}

static int init_each_dummy_(RS422_CONFIG_STRUCT* dummy,
                            unsigned char ch)
{
  dummy->ch = ch;
  dummy->baudrate = 115200;
  dummy->stop_bit = 1;
  return RS422_init(dummy);
}

static void rs422_dummy_s2e_com(void)
{
  int test_ch = 0;
  static int count = 0;
  unsigned char test_tx_data_[5] = {'S', 'E', 'T', 'A', '\n'};
  unsigned char test_rx_data_[100];  
  // Send
  test_tx_data_[3] += count;
  RS422_TX(&rs422_dummy_ch_[test_ch], &test_tx_data_[0], 5);
  count++;
  if(count >= 26) count = 0;

  // Receive
  RS422_RX(&rs422_dummy_ch_[test_ch], &test_rx_data_[0], 100);
}
#pragma section
