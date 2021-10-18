#include "mgos.h"
#include "mgos_jsar.h"

static void loop(void *arg)
{
  uint16_t e1, e2, e3, e4;

  e1 = mgos_jsar_KeysPositionRead(1);
  e2 = mgos_jsar_KeysPositionRead(2);
  e3 = mgos_jsar_KeysPositionRead(3);
  e4 = mgos_jsar_KeysPositionRead(4);
  
  LOG(LL_INFO, ("e1: %d\t e4: %d\t", e1, e2));
  LOG(LL_INFO, ("e3: %d\t e4: %d\t", e3, e4));


  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_begin();
  mgos_jsar_KeysBegin();

  mgos_jsar_KeysSpeedWrite(1, 50);
  mgos_jsar_KeysSpeedWrite(2, 100);
  mgos_jsar_KeysSpeedWrite(3, 150);
  mgos_jsar_KeysSpeedWrite(4, 200);



  mgos_set_timer(1000 , MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}