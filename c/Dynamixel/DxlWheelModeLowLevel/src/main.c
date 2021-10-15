#include "mgos.h"
#include "mgos_jsar.h"


enum DynMotorAddress {
	/** \brief Clockwise angle limit, uint16_t , writable */
	DYN_ADDRESS_CW_LIMIT			= 0x06,

	/** \brief Counnter clockwise angle limit, uint16_t , writable */
	DYN_ADDRESS_CCW_LIMIT			= 0x08,

	/** \brief Maximum torque, uint16_t , writable */
	DYN_ADDRESS_MAX_TORQUE			= 0x0E,

	/** \brief Enable torque, uint8_t , writable */
	DYN_ADDRESS_ENABLE_TORQUE		= 0x18,

	/** \brief LED state, uint8_t , writable */
	DYN_ADDRESS_LED					= 0x19,

	/** \brief CW compliance margin, uint8_t , writable */
	DYN_ADDRESS_CW_COMP_MARGIN		= 0x1A,

	/** \brief CCW compliance margin, uint8_t , writable */
	DYN_ADDRESS_CCW_COMP_MARGIN 	= 0x1B,

	/** \brief CW compliance slope, uint8_t , writable */
	DYN_ADDRESS_CW_COMP_SLOPE		= 0x1C,

	/** \brief CCW compliance slope, uint8_t , writable */
	DYN_ADDRESS_CCW_COMP_SLOPE  	= 0x1D,

	/** \brief Goal position, uint16_t , writable */
	DYN_ADDRESS_GOAL_POSITION		= 0x1E,

	/** \brief Goal speed, uint16_t , writable */
	DYN_ADDRESS_GOAL_SPEED			= 0x20,

	DYN_ADDRESS_TORQUE_LIMIT		= 0x22,

	/** \brief Current position, uint16_t , readable */
	DYN_ADDRESS_CURRENT_POSITION	= 0x24,

	/** \brief Nonzero if any movement, uint8_t, readable */
	DYN_ADDRESS_MOVING				= 0x2E
};


// id of the motor
const uint8_t id = 1;

// speed, between -1023 and 1023
int16_t speed = 512;

// communication baudrate
const long unsigned int baudrate = 1000000;

int16_t makeSpeed(int16_t speed)
{
  if (speed < 0) {
    speed = -speed | 1024;
  }
  return speed;
}

DynamixelDevice * motor = NULL;

static void loop(void *arg)
{
  mgos_dxl_write16(motor, DYN_ADDRESS_GOAL_SPEED, makeSpeed(speed));
  speed = -speed;

  static uint8_t led_state = 0;
  mgos_dxl_write(motor, DYN_ADDRESS_LED, led_state++ % 2);
  
  (void) arg;
}

enum mgos_app_init_result mgos_app_init(void) 
{
  mgos_jsar_begin();
  mgos_dxl_master_begin(baudrate);

  motor = mgos_dxl_module_create(id);

  uint8_t status = mgos_dxl_init(motor);
  if (status != 0) {
    LOG(LL_INFO, ("Motor init: Error\n"));
  } else {
    LOG(LL_INFO, ("Motor init: Ok\n"));
  }

  mgos_dxl_write(motor, DYN_ADDRESS_ENABLE_TORQUE, true); 
  mgos_dxl_write16(motor, DYN_ADDRESS_CW_LIMIT, 0);
  mgos_dxl_write16(motor, DYN_ADDRESS_CCW_LIMIT, 0); 

  mgos_set_timer(2000 , MGOS_TIMER_REPEAT, loop, NULL);

  return MGOS_APP_INIT_SUCCESS;
}
