#include "mgos.h"
#include "mgos_jsar.h"
#include "mgos_adc.h"

#define PIN 36

static void loop(void *arg)
{
  int val = mgos_adc_read(PIN);
  LOG(LL_INFO, ("Value: %d", val));
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_begin();
  mgos_adc_enable(PIN);
  mgos_set_timer(500 , MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}

