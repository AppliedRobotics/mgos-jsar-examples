#include "mgos.h"
#include "mgos_jsar.h"

#define PIN 23

static void loop(void *arg)
{
  static uint8_t val = 0;
  mgos_jsar_expanderDigitalWrite(PIN, val++ % 2);
  LOG(LL_INFO, ("Pin %d: %d", PIN, val % 2));
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_expanderPinMode(PIN, OUTPUT);
  mgos_set_timer(2000 , MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
