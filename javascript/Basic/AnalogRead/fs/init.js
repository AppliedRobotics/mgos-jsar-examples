load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_adc.js');

let pin = 36;

ADC.enable(pin)

Timer.set(500, Timer.REPEAT, function() {
  print('Pin', pin, 'Analog read:', ADC.read(pin));
}, null);