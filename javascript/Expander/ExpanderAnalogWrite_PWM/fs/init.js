load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');

let pin = 22; //18-23
let value = 0;

JsAr.expanderPinMode(pin, JsAr.MODE_OUTPUT);

Timer.set(2000, Timer.REPEAT, function() {
  JsAr.expanderAnalogWrite(pin, value % 1024);
  print('Pin', pin, 'Analog write:', value % 1024);
  value = value + 128;
}, null);