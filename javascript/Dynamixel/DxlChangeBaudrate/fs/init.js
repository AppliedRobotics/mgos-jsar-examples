load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_dxl.js');

print('Start js app');
print('Reset dxl-sensor and reboot js-ar for appling baud change');

let rgb_id = 0x15; // RGB
let baudrate_57k = 57600;
let baudrate_1kk = 1000000;

let rgb = DynamixelDevice.create(rgb_id);

DxlMaster.begin(baudrate_57k);
rgb.init();

if (rgb.ping() === 0) {
    print('Dxl speed = ', baudrate_57k); 
    rgb.write(26, 10);
    rgb.write(28, 0);
    rgb.communicationSpeed(baudrate_1kk);
    
} else {
    DxlMaster.begin(baudrate_1kk);  
    if (rgb.ping() === 0) {
        print('Dxl speed = ', baudrate_1kk);
        rgb.write(26, 0);
        rgb.write(28, 10);
        rgb.communicationSpeed(baudrate_57k);
    } else {
        print('Dxl speed = not 57600 or 1kk - Error ');
    }
}



