
//#include <chrono>

//#include <functional>
//#include <iomanip>
//#include <iostream>
//#include <algorithm>
#include <math.h>
//#include "half.hpp"

//using half = half_float::half;

#define biti (5)   //4 bity całkowite i 28 bitów ułamkowych, zakres -8,8
#define bitf (27)  //4 bity całkowite i 28 bitów ułamkowych, zakres -8,8

const double bf = 1 << bitf;

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
  return Divide(Multiply(k1,Multiply(x,(k2+Multiply(x,(1+x))))),(k3+Multiply(x,(k4+Multiply(x,(k5+x))))));
  //1.5707963267948966192313216916397514*x*(.64037063384808615708449497961711650+x*(1+x))/(1.+x*(1.6403706338480861570844949796171165+x*(1.6403706338480861570844949796171165+x)));
}


void setup() {
  //cykle = SysTick->VAL;
  float step = 0.00001f;  //do zgrywaia pliku (0.00001f); //ok 200k Sampli
  float currentValue = 0.0f + step;
  float maxValue = 1.0f;
  //long y;
  long x;
  long i = 1;
  for (i = 1; currentValue < maxValue; i++) {

    x = long(currentValue * bf);  

    long y = giron(x);

    Serial.print(y);
  }
}

void loop() {
}
