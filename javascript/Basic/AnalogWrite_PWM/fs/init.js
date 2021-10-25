load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_pwm.js');

let pin = 2;
let freq = 50;
let duty = 0.5;

PWM.set(pin, freq, duty);

Timer.set(500, Timer.REPEAT, function() {
  print('PWM Pin', pin, 'freq:', freq, 'duty', duty);
}, null);