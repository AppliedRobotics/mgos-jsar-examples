#include "mgos.h"
#include "mgos_jsar.h"

#define PIN 36

static void loop(void *arg)
{
  int val = mgos_gpio_read(PIN);
  LOG(LL_INFO, ("Value: %d", val));
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_begin();
  mgos_gpio_set_mode(PIN, MGOS_GPIO_MODE_INPUT);
  mgos_set_timer(500 , MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
