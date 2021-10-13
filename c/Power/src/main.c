#include "mgos.h"
#include "mgos_jsar.h"


static void loop(void *arg)
{
  LOG(LL_INFO, ("Value: %f", mgos_jsar_readVoltage()));
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_begin();
  mgos_jsar_writeMinVoltageToStart(6.5);
  mgos_jsar_writeMinVoltageToWork(6.0);
  mgos_set_timer(500 , MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
