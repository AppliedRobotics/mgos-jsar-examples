load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');

let pin = 36;

JsAr.expanderPinMode(pin, 1);

Timer.set(500, Timer.REPEAT, function() {
  print('Pin', pin, 'Analog read:', JsAr.expanderAnalogRead(pin));
}, null);