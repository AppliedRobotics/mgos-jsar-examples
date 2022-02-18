load('api_config.js');
load('api_sys.js');
load('api_gpio.js');
load('api_timer.js');
load('api_lcd_i2c.js');
load('api_jsar.js');

// I2C: SDA - 32, SDC - 33

print('Start user js app at', Sys.uptime());
let lcd = LCD_I2C.create();

lcd.begin(2, 10);
lcd.home();
lcd.print('Hello World!');
lcd.setCursor(0, 1);
lcd.print("Uptime: ");

Timer.set(1000, Timer.REPEAT, function() {
    lcd.setCursor(8, 1);
    lcd.print(Sys.uptime() |0) 
  }, null);