load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_dxl.js');

print('Start Dxl Joint Mode app');

let id = 1;
let speed = 512; 
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
motor.jointMode(204, 820);
motor.speed(speed);
motor.goalPosition(512);
