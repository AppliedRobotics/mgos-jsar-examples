#include "mgos.h"
#include "mgos_jsar.h"

#define PIN 36

static void loop(void *arg)
{
  LOG(LL_INFO, ("Value: %d", mgos_gpio_toggle(PIN)));
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_begin();
  mgos_gpio_set_mode(PIN, MGOS_GPIO_MODE_OUTPUT);
  mgos_gpio_set_pull(PIN, MGOS_GPIO_PULL_NONE);
  mgos_set_timer(500 , MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
