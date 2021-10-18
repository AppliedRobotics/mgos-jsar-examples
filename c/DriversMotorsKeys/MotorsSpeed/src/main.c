#include "mgos.h"
#include "mgos_jsar.h"


static void loop(void *arg)
{
  int16_t pos1, pos2;

  mgos_jsar_MotorsPositionReadAll(&pos1, &pos2);
  LOG(LL_INFO, ("Pos1: %d\t Pos2: %d", pos1, pos2));

  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_begin();
  mgos_jsar_MotorsBegin();
  mgos_jsar_MotorsEncoderModeAB();

  mgos_jsar_MotorsSpeedWrite(1, 100);
  mgos_jsar_MotorsSpeedWrite(2, 100);

  LOG(LL_INFO, ("Start!"));
  
  mgos_set_timer(500, MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
