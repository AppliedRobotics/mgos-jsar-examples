load('api_config.js');
load('api_gpio.js');
load('api_timer.js');
load('api_sys.js');
load('api_jsar.js');
load('api_dxl.js');

print('Start js app');

let rgb_id = 0x15; // RGB
let baudrate_57k = 57600;
let baudrate_1kk = 1000000;

let rgb = DynamixelDevice.create(rgb_id);

DxlMaster.begin(baudrate_57k);
rgb.init();

rgb.write(26, 10);





