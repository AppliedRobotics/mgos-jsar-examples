#include "mgos.h"
#include "mgos_jsar.h"

// id of the motor
const uint8_t id = 1;
// speed, between 0 and 1023
int16_t speed = 256;
// communication baudrate
const long unsigned int baudrate = 1000000;

DynamixelMotor * motor = NULL;

static void loop(void *arg)
{
  mgos_dxl_motor_speed(motor, speed);
  speed = -speed;

  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_dxl_master_begin(baudrate);

  motor = mgos_dxl_motor_create(id);


  uint8_t status = mgos_dxl_motor_init(motor);
  if (status != 0) {
    LOG(LL_INFO, ("Motor init: Error\n"));
  } else {
    LOG(LL_INFO, ("Motor init: Ok\n"));
  }

  mgos_dxl_motor_enableTorque(motor, true);

  mgos_dxl_motor_wheelMode(motor);

  mgos_set_timer(2000 , MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
