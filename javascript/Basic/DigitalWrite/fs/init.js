load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');

let pin = 2;

GPIO.setup_output(pin, 0)

Timer.set(2500, Timer.REPEAT, function() {
  print('Pin', pin, ' write:', GPIO.toggle(pin));
}, null);