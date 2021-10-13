#include "mgos.h"
#include "mgos_jsar.h"

#define PIN 36

static void loop(void *arg)
{
  int val = mgos_jsar_expanderAnalogRead(PIN);
  LOG(LL_INFO, ("Pin %d value: %d", PIN, val));
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_begin();
  mgos_jsar_expanderPinMode(PIN, INPUT);
  mgos_set_timer(500 , MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
