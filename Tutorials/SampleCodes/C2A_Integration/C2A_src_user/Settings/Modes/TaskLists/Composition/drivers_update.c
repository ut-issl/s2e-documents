#pragma section REPRO
#include "drivers_update.h"

#include "../../../../../src_core/CmdTlm/BlockCommandTable.h"
#include "../../../../CmdTlm/BlockCommandDefinitions.h"
#include "../../../../CmdTlm/CommandDefinitions.h"
#include "../../../../Applications/AppRegistry.h"
#include "../../../../../src_core/Library/endian_memcpy.h"

void BC_load_drivers_update_initial(bct_id_t pos)
{
  CTCP temp;
  unsigned char param[SIZE_OF_BCT_ID_T];
  bct_id_t bc_id;

  BCT_store_pos();
  BCT_clear_block(pos);

  CCP_form_app_cmd(&temp, 0, AR_DI_RS422_DUMMY);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 1, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 2, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 3, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 4, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 5, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 6, AR_DI_PCU_UPDATE);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 7, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 8, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 9, AR_MW_FLASH);   // driverではなくMiddlewareだが，コピーするだけなのでとりあえずここに（2018/10/02 鈴本）
  BCT_register_cmd(&temp);

  BCT_activate_block();
  BCT_restore_pos();
}


void BC_load_drivers_update_ground_test(bct_id_t pos)
{
  CTCP temp;
  unsigned char param[SIZE_OF_BCT_ID_T];
  bct_id_t bc_id;

  BCT_store_pos();
  BCT_clear_block(pos);

  CCP_form_app_cmd(&temp, 0, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 1, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 2, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 3, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 4, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 5, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 6, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 7, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 8, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 9, AR_MW_FLASH);   // driverではなくMiddlewareだが，コピーするだけなのでとりあえずここに（2018/10/02 鈴本）
  BCT_register_cmd(&temp);

  BCT_activate_block();
  BCT_restore_pos();
}

void BC_load_drivers_update_dv1(bct_id_t pos)
{
  CTCP temp;

  BCT_store_pos();
  BCT_clear_block(pos);

  CCP_form_app_cmd(&temp, 0, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 1, AR_DI_XTRP_UPDATE);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 2, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 3, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 4, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 5, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 6, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 7, AR_DI_PCU_UPDATE);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 8, AR_NOP);
  BCT_register_cmd(&temp);

  CCP_form_app_cmd(&temp, 9, AR_MW_FLASH);   // driverではなくMiddlewareだが，コピーするだけなのでとりあえずここに（2018/10/02 鈴本）
  BCT_register_cmd(&temp);

  BCT_activate_block();
  BCT_restore_pos();
}

#pragma section
