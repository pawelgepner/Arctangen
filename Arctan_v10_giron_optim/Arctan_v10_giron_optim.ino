
//#include <chrono>

//#include <functional>
//#include <iomanip>
//#include <iostream>
//#include <algorithm>
#include <math.h>
//#include "half.hpp"

//using half = half_float::half;

#define biti (12)   //4 bity całkowite i 28 bitów ułamkowych, zakres -8,8
#define bitf (20)  //4 bity całkowite i 28 bitów ułamkowych, zakres -8,8

const double bf = 1 << bitf;

volatile double x_atanbf = 0;

void print_ull(unsigned long long ll) {
  uint32_t low = ll & 0xFFFFFFFF;
  uint32_t high = (ll >> 32) & 0xFFFFFFFF;
  Serial.print(high, HEX);
  Serial.print("|");
  Serial.print(low, HEX);
}

long Multiply(long i, long j) {
  long mulhi1, mullo1;

  asm("smull  %0, %1, %[input_i], %[input_j];"
      : "=r"(mullo1), "=r"(mulhi1)
      : [input_i] "r"(i), [input_j] "r"(j)
      : /* No clobbers */
  );

  long y = (mulhi1 << biti) + (mullo1 >> bitf);
  return y;
}

long Divide(long i, long j) {
  long long ill = i;

  //Serial.print("  size_i   = "); Serial.println(sizeof(i));
  //Serial.print("  size_ill = "); Serial.println(sizeof(ill));
  //Serial.print("  ill = "); print_ull(ill); Serial.println("");
  ill = ill << bitf;
  //Serial.print(" sill = "); print_ull(ill); Serial.println("");
  long long jll = j;
  //Serial.print("  jll = "); print_ull(jll); Serial.println("");
  long long yll = ill / jll;
  //Serial.print("  yll = "); print_ull(yll); Serial.println("");
  long y = long(yll);
  return y;
}

long giron(long x){
  const long k1 = long(1.5707963267948966192313216916397514 * bf);
  const long k2 = long(0.64037063384808615708449497961711650 * bf);
  const long k3 = long(1.0 * bf);
  const long k4 = long(1.6403706338480861570844949796171165 * bf);
  const long k5 = long(1.6403706338480861570844949796171165 * bf);
  /*Serial.print("giron_k1;");  Serial.print(k1, DEC); Serial.print(";");  Serial.println(double(k1)/bf,30);
  Serial.print("giron_k2;");  Serial.print(k2, DEC); Serial.print(";");  Serial.println(double(k2)/bf,30);
  Serial.print("giron_k3;");  Serial.print(k3, DEC); Serial.print(";");  Serial.println(double(k3)/bf,30);
  Serial.print("giron_k4;");  Serial.print(k4, DEC); Serial.print(";");  Serial.println(double(k4)/bf,30);*/
  return Divide(Multiply(k1,Multiply(x,(k2+Multiply(x,(k3+x))))),(k3+Multiply(x,(k4+Multiply(x,(k5+x))))));
  //k1*x*(k2+x*(1+x))/(k3+x*(k4+x*(k5+x)));
  //1.5707963267948966192313216916397514*x*(.64037063384808615708449497961711650+x*(k3+x))/(1.+x*(1.6403706338480861570844949796171165+x*(1.6403706338480861570844949796171165+x)));
}

double giron_err(long x) {
  return double(giron(x)) / bf - x_atanbf;
}


void setup() {
  Serial.begin(460800L);  //(9600); //do zgrywaia pliku (460800L);

  Serial.println("START SETUP");
  
  PMC->PMC_PCER0 |= PMC_PCER0_PID27;  // // Enable peripheral TC1 (TC0 Channel 0)
  // Set Timer 1 to normal mode at F_CPU.
  TC0->TC_CHANNEL[0].TC_CMR =  //TC_CMR_BCPC_SET |           // Set TIOB on counter match with RC0
    //TC_CMR_ACPC_SET |           // Set TIOA on counter match with RC0
    //TC_CMR_BCPB_CLEAR |         // Clear TIOB on counter match with RB0
    //TC_CMR_ACPA_CLEAR |         // Clear TIOA on counter match with RA0
    //TC_CMR_ABETRG   |           // TIOA is used as the external trigger
    //TC_CMR_WAVE |               // Enable wave mode
    // TC_CMR_WAVSEL_UP_RC |       // Count up with automatic trigger on RC compare
    //TC_CMR_EEVT_XC0 |           // Set event selection to XC0 to make TIOB an output make an output
    TC_CMR_TCCLKS_TIMER_CLOCK1;  // Set the timer clock to TCLK1 (MCK/2 = 84MHz/2 = 42MHz)

  //TC0->TC_CHANNEL[0].TC_CCR = TC_CCR_SWTRG | TC_CCR_CLKEN; // Software trigger and enable
  REG_TC0_CCR0 = TC_CCR_SWTRG | TC_CCR_CLKEN;


  Serial.println("START TEST");

  double error_giron = 0;

  double max_error_giron = 0;
  double max_error_giron4x = 0;

  double min_error_giron = 0;
  double min_error_giron4x = 0;

  double mean_error_giron = 0;

  float step = 0.001;//0.00005f;  //do zgrywaia pliku (0.00001f); //ok 200k Sampli
  float currentValue = 0.0f + step;
  float maxValue = 10.0f;

  ///OK:
  //step = 0.001;   maxValue = 1.75f;  Q5.27
  //step = 0.001;   maxValue = 10.0f;  Q12.20

  long x;

  //double count = 0;
  //double count1M = 0;
  
  Serial.print("bitf:     ");  Serial.println(bitf,DEC);
  Serial.print("step:     ");  Serial.println(step, 10);
  Serial.print("minValue: ");  Serial.println(currentValue, 10);
  Serial.print("maxValue: ");  Serial.println(maxValue - step, 10);

  //wydruk do konsoli dla CSV!!!
  Serial.print("x"); Serial.print(";");
  Serial.print("x"); Serial.print(";");
  Serial.print("Giron"); Serial.print(";");
  Serial.print("satan");
  Serial.println("");

  long i = 1;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);  //0.7f*bf;//
    //x= 939522112;
    //Serial.print("   x="); Serial.println(x,HEX);
    x_atanbf = atan(double(x) / bf);
    error_giron = giron_err(x);

    if (max_error_giron < error_giron) {      max_error_giron = error_giron;      max_error_giron4x = x;    }
    if (min_error_giron > error_giron) {      min_error_giron = error_giron;      min_error_giron4x = x;    }

    if (i == 1) {
      mean_error_giron = abs(error_giron);
    } else {
      mean_error_giron = (mean_error_giron + abs(error_giron));
    }

    //count++;
    //if (count == 100000) {      count = 0;      count1M++;      Serial.print("100k SAMPLI: x");      Serial.println(count1M);    }
/*
    long giron_our = giron(x);

    //wydruk do konsoli dla CSV!!!
    Serial.print(x,DEC); Serial.print(";");
    Serial.print(x,HEX); Serial.print(";");
    Serial.print(giron_our,DEC); Serial.print(";");
    Serial.print(double(giron_our)/bf,40); Serial.print(";");/////////////
    Serial.print(x_atanbf,40);
    Serial.println("");
*/
    currentValue = currentValue + step;
  }
  i = i - 1;  //odlicza o jeden cykl więcej niż wykonano

  // Przeliczanie wyników na stopnie
  double dmaxGr_giron = max_error_giron * 180.0 / PI;
  double dminGr_giron = min_error_giron * 180.0 / PI;

  mean_error_giron = (mean_error_giron/i) * 180.0 / PI;

  Serial.print("cycles = i = ");  Serial.println(i);
  Serial.println("");
  Serial.println("OUR ALGORITHMS:");
  Serial.print("For Giron errors (in degrees); max: ");  Serial.print(dmaxGr_giron, 15);  Serial.print("   for x: ");  Serial.print(max_error_giron4x, 15);  Serial.print(";    min: ");  Serial.print(dminGr_giron, 15);  Serial.print("   for x: ");  Serial.println(min_error_giron4x, 15);

  Serial.println("");

  Serial.println("OUR ALGORITHMS:");
  Serial.print("Mean error for Giron (in degrees): ");  Serial.println(mean_error_giron, 20);
  Serial.println("END");
  Serial.println("");

}

void loop() {
}
