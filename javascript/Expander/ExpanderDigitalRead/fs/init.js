load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');

let pin = 23;

JsAr.expanderPinMode(pin, JsAr.MODE_INPUT);

Timer.set(500, Timer.REPEAT, function() {
  print('Pin', pin, 'Digital read:', JsAr.expanderDigitalRead(pin));
}, null);