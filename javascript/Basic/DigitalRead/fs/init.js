load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');

let pin = 36;

GPIO.setup_input(pin, GPIO.PULL_NONE);

Timer.set(500, Timer.REPEAT, function() {
  print('Pin state:', GPIO.read(pin));
}, null);