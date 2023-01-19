#include "arduinoFFT.h"
#include <Adafruit_SSD1306.h>
#include "P32.h"

#define samples 64           //采样点数，2的N次幂
#define halfsamples samples/2

#define NumofCopy halfsamples*sizeof(double)
#define Interval 128/(halfsamples)

Adafruit_SSD1306 my_oled(100);
arduinoFFT FFT = arduinoFFT();

double vReal[samples];
double vImag[samples];
double vTemp[halfsamples];

void setup() {
  setP32();                                 //设置32分频,加快AD采样
  my_oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);//初始化oled
  my_oled.setTextColor(WHITE);
}

void loop() {
  my_oled.clearDisplay();
  
  for(int i=0;i<samples;i++){
    vReal[i]=analogRead(A0)-512;             //analogRead采样
    vImag[i] = 0.0;
  }

  FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD);      //加窗
  FFT.Compute(vReal, vImag, samples, FFT_FORWARD);                      //计算fft
  FFT.ComplexToMagnitude(vReal, vImag, samples);                        //计算幅度
  
  for(int i=0;i<halfsamples;i++){                                       //显示                       
    my_oled.drawPixel(i*Interval,vTemp[halfsamples-i-1]*0.007+1, WHITE);//顶部掉落点
    my_oled.drawLine(i*Interval, 0, i*Interval,vReal[halfsamples-i-1]*0.007, WHITE);
  }                                                                     //律动线条
  
  my_oled.display();
  memcpy(vTemp, vReal, NumofCopy);
}
