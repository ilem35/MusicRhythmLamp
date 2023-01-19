#ifndef P32_H
#define P32_H

#include "Arduino.h"

void setP32(){        //设置32分频
  ADCSRA|=(1<<ADPS2);  
  ADCSRA&=~(1<<ADPS1);
  ADCSRA|=(1<<ADPS0);
}

#endif
