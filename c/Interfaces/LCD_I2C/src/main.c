#include "mgos.h"
#include <mgos_i2c.h>
#include "mgos_jsar.h"
#include "mgos_lcd_i2c.h"

LiquidCrystal_I2C *lcdi2c;

static void loop(void *arg)
{
    mgos_lcd_i2c_clear(lcdi2c);
    mgos_lcd_i2c_home(lcdi2c);
    mgos_lcd_i2c_print(lcdi2c, "Hello");
    mgos_lcd_i2c_set_cursor(lcdi2c, 2, 1);
    mgos_lcd_i2c_print(lcdi2c, "World!");
    
}

enum mgos_app_init_result mgos_app_init(void)
{
    LOG(LL_INFO, ("Start"));
    lcdi2c = mgos_lcd_i2c_create(0x27);
    mgos_lcd_i2c_begin(lcdi2c, 2, 16, 0);

    mgos_set_timer(1000, MGOS_TIMER_REPEAT, loop, NULL);

    return MGOS_APP_INIT_SUCCESS;
}