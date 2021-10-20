#include "mgos.h"
#include "mgos_jsar.h"

#define PIN 23

static void loop(void *arg)
{
  static uint16_t value = 0;
  LOG(LL_INFO, ("%d", value % 1024)); 
  mgos_jsar_expanderAnalogWrite(PIN, value % 1024);

  value = value + 128;
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_expanderPinMode(PIN, OUTPUT);
  mgos_set_timer(500 , MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
