#include "mgos.h"
#include "mgos_pwm.h"
#include "mgos_jsar.h"


static void loop(void *arg)
{
  static uint8_t step = 0;
  mgos_pwm_set(2, 1000, step++ / 256.);

  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_set_timer(10, MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
