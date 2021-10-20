#include "mgos.h"
#include "mgos_jsar.h"


static void loop(void *arg)
{
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_MotorsBegin();

  mgos_jsar_MotorsPowerWrite(1, 50);
  mgos_jsar_MotorsPowerWrite(1, 100);
  LOG(LL_INFO, ("Start!"));
  
  mgos_msleep(1000);

  mgos_set_timer(500, MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
