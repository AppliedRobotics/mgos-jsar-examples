load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_dxl.js');

print('Start Dxl Wheel Mode app');

let id = 1;
let speed = 384; 
let baudrate_1kk = 1000000;

let motor = Dynamixelmotor.create(id);

DxlMaster.begin(baudrate_1kk);
let ret = motor.init();

if (ret !== 0) {
    print('Motor init: Error');
} else {
    print('Motor init: Ok'); 
}

motor.enableTorque(true);
motor.wheelMode();

Timer.set(2500, Timer.REPEAT, function() {
    motor.speed(speed);
    speed = -speed;
  
  }, null);