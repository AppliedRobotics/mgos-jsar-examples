#include "mgos.h"
#include "mgos_jsar.h"

int16_t speed1 = 50, speed2 = 100;

static void swap(void *arg)
{
  speed1 = -speed1;
  speed2 = -speed2;

  (void) arg;
}

static void loop(void *arg)
{
  mgos_jsar_MotorsSpeedWrite(1, 100);
  mgos_jsar_MotorsSpeedWrite(2, 100);

  int16_t e1, e2, s1, s2, p1, p2;
  mgos_jsar_MotorsPositionReadAll(&e1, &e2);
  mgos_jsar_MotorsSpeedReadAll(&s1, &s2);
  mgos_jsar_MotorsPowerReadAll(&p1, &p2);

  LOG(LL_INFO, ("p1: %d\t p2: %d", p1, p2));
  LOG(LL_INFO, ("e1: %d\t e2: %d", e1, e2));
  LOG(LL_INFO, ("s1: %d\t s2: %d", s1, s2));

  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_MotorsBegin();
  mgos_jsar_MotorsLoopPeriodWrite(10);
  mgos_jsar_MotorsPidWrite(16, 32, 0);
  mgos_jsar_MotorsEncoderModeAB();
  mgos_jsar_MotorsMaxPowerWrite(500);


  LOG(LL_INFO, ("Start!"));
  
  mgos_set_timer(500, MGOS_TIMER_REPEAT, loop, NULL);
  mgos_set_timer(2000, MGOS_TIMER_REPEAT, swap, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
