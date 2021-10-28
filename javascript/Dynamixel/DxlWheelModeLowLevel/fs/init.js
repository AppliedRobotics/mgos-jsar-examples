load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_dxl.js');

print('Start js app');

let id = 0x1; 
let baudrate_1kk = 1000000;
let speed = 512;
let led_state = false;

let motor = DynamixelDevice.create(id);

DxlMaster.begin(baudrate_1kk);

if (motor.init() !== 0) {
    print('Motor init: Error');
} else {
    print('Motor init: Ok'); 
}

motor.write(0x18, true);
motor.write16(0x06, 0);
motor.write16(0x08, 0);

let makeSpeed = function (speed) {
    if (speed < 0) {
        speed = -speed | 1024;
    } 
    return speed;
};

Timer.set(2500, Timer.REPEAT, function() {
    motor.write16(0x20, makeSpeed(speed));
    speed = -speed;

    motor.write(0x19, led_state);
    led_state = !led_state;
  
}, null);




