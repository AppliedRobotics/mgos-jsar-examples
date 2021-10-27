load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');

let pin = 23; 
let value = false;

JsAr.expanderPinMode(pin, JsAr.MODE_OUTPUT);

Timer.set(2000, Timer.REPEAT, function() {
  print('Pin', pin, 'Digital write:', JsAr.expanderDigitalWrite(pin, value));
  value = !value;
}, null);