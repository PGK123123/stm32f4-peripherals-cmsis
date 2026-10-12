#include "main.h"
#include "init.h"
#include "i2c.h"
#include "ssd1306.h"
#include "button.h"
#include "rgb_led.h"
#include "encoder.h"
#include "systick.h"

uint8_t display_need_update = 0;

int main(void){
    clock_init(CLOCK_PLL);

    i2c_init();
	ssd1306Init();

	tim4_init();
	buttons_init();

	rgb_led_init();

	encoder_init();

	ssd1306DrawString(0, 0, "RGB Controller");
	update_display();

	for(;;){
	    encoder_update();
	    if (display_need_update) {
	               display_need_update = 0;
	               update_display();
	           }
	}
}
