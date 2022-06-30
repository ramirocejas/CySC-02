#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"

int main() {
    float v1,v2;

    adc_init();
    adc_gpio_init(27);
    adc_gpio_init(28);

    gpio_set_function(9, GPIO_FUNC_PWM);
    gpio_set_function(10, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(9);
  
    pwm_config config = pwm_get_default_config();

    pwm_init(slice_num, &config, true);

    while(1){
      
    adc_select_input(0);
    uint16_t potenciometro = adc_read();
    adc_select_input(1);
    uint16_t LM = adc_read();

    v1= (float)potenciometro * 3.3/4095;
    int potentemp = v1 * 35 / 3.3;
    v2= (float) LM * 3.3/4095;
    int LMtemp = v2*100;
    int DifTemp = (potentemp - LMtemp) * 1000; 

    printf("Temperatura de LM %d\n,", LMtemp);
    printf("Temperatura del poten %d\n", potentemp);
    printf("Temperatura de DifTemp %d\n", DifTemp);
    sleep_ms(500);

    if (DifTemp > 10) {
      DifTemp = 10;
    }

    if (potentemp>LMtemp){
      pwm_set_gpio_level(9, DifTemp);
      pwm_set_gpio_level(10, 0);
    }
    if (potentemp<LMtemp){
      DifTemp = DifTemp*-1;
      pwm_set_gpio_level(10, DifTemp);
      pwm_set_gpio_level(9, 0);
    }
    
    DifTemp = DifTemp * 0xffff / 10;
   printf("DifTemp %d\n", diftemp);

   }
}