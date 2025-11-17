
//#include <chrono>

//#include <functional>
//#include <iomanip>
//#include <iostream>
//#include <algorithm>
#include <math.h>
//#include "half.hpp"

//using half = half_float::half;

#define biti (5)   //4 bity całkowite i 28 bitów ułamkowych, zakres -8,8
//#define bitf 27  //4 bity całkowite i 28 bitów ułamkowych, zakres -8,8
#define bitf (27)

const double bf = 134217728; //1 << bitf;

void print_ull(unsigned long long ll) {
  uint32_t low = ll & 0xFFFFFFFF;
  uint32_t high = (ll >> 32) & 0xFFFFFFFF;
  Serial.print(high, HEX);
  Serial.print("|");
  Serial.print(low, HEX);
}

long Multiply(long i, long j) {
  //long mulhi1, mullo1;

  //asm("smull  %0, %1, %[input_i], %[input_j];"
  //    : "=r"(mullo1), "=r"(mulhi1)
  //    : [input_i] "r"(i), [input_j] "r"(j)
  //    : /* No clobbers */
  //);
  
  long long temp= (long long)i*(long long)j;
  long mulhi1 = (temp >> 32) & 0xFFFFFFFF;
  long mullo1 = (temp & 0xFFFFFFFF);

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


long bf_1 = long(1 * bf);
long bf_z372 = long(0.372003 * bf);
long bf_z703 = long(0.703384 * bf);
long bf_z043 = long(0.043562 * bf);
long bf_z422 = long(0.42261895 * bf);
long bf_z000 = long(1.0000458 * bf);
long bf_z755 = long(0.7551110 * bf);
long bf_z056 = long(0.0561875 * bf);

long bf_l281 = long(0.28125 * bf);
long bf_l013 = long(1.013271 * bf);
long bf_l263 = long(0.2635576 * bf);

long bf_b044 = long(0.0443 * bf);
long bf_b231 = long(0.231 * bf);
long bf_b985 = long(0.985853131 * bf);
long bf_b087 = long(0.087386734 * bf);
long bf_b201 = long(0.2010917789 * bf);

long bf_r244 = long(0.2447 * bf);
long bf_r066 = long(0.0663 * bf);
long bf_r077 = long(0.07769 * bf);
long bf_r848 = long(4.84844 * bf);
long bf_r725 = long(2.725664 * bf);

long bf_PI4 = long((PI / 4.0) * bf);

//  Zarowski
long Zarowski_orginal(long x) {
  //return x * (long(1*bf) + long(0.372003*bf) *  x^2) / (long(1*bf) + long(0.703384*bf) *  x^2 + long(0.043562*bf) * x^4);}
  return Divide(Multiply(x, (bf_1 + Multiply(bf_z372, Multiply(x, x)))), (bf_1 + Multiply(Multiply(x, x), bf_z703 + Multiply(bf_z043, Multiply(x, x)))));
}
long Zarowski_our(long x) {
  //return (x + long(0.42261895*bf) * x^3) / (long(1.0000458*bf) + long(0.7551110*bf) *  x^2 + long(0.0561875*bf) * x^4);}
  return Divide(Multiply(x, (bf_1 + Multiply(bf_z422, Multiply(x, x)))), (bf_z000 + Multiply(Multiply(x, x), bf_z755 + Multiply(bf_z056, Multiply(x, x)))));
}
// Lynos
long Lynos_orginal(long x) {
  //return x / (long(1.0*bf) + long(0.28125*bf) * x^2);}
  return Divide(x, (bf_1 + Multiply(bf_l281, Multiply(x, x))));
}
long Lynos_our(long x) {
  //return x / (long(1.013271*bf) + long(0.2635576*bf) *  x^2);}
  return Divide(x, (bf_l013 + Multiply(bf_l263, Multiply(x, x))));
}
// Benammar
long Benammar_orginal(long x) {
  //return x / (long(1.0*bf) + long(0.0443*bf) * abs(x) + long(0.231*bf) * x^2);}
  return Divide(x, (bf_1 + Multiply(bf_b044, abs(x)) + Multiply(bf_b231, Multiply(x, x))));
}
long Benammar_our(long x) {
  //return x / (long(0.985853131*bf) + long(0.087386734*bf) * abs(x) + long(0.2010917789*bf) * x^2);}
  return Divide(x, (bf_b985 + Multiply(bf_b087, abs(x)) + Multiply(bf_b201, Multiply(x, x))));
}
// Rajan
long Rajan_orginal(long x) {
  //return x * (long(PI*bf) / long(4*bf) - (abs(x) - long(1*bf)) * (long(0.2447*bf) + long(0.0663*bf) * abs(x)));}
  return Multiply(x, (bf_PI4 - Multiply((abs(x) - bf_1), bf_r244 + Multiply(bf_r066, abs(x)))));
}
long Rajan_our(long x) {
  //return long(0.07769*bf) * x * (abs(x) + long(4.84844*bf)) * (long(2.725664*bf) - abs(x));}
  return Multiply(bf_r077, Multiply(x, Multiply((abs(x) + bf_r848), (bf_r725 - abs(x)))));
}

//  Róznica wobec math.atan    extern double atan(double)
double z_err_org(long x) {
  return double(Zarowski_orginal(x)) / bf - atan(double(x) / bf);
}
double z_err_our(long x) {
  return double(Zarowski_our(x)) / bf - atan(double(x) / bf);
}
double l_err_org(long x) {
  return double(Lynos_orginal(x)) / bf - atan(double(x) / bf);
}
double l_err_our(long x) {
  return double(Lynos_our(x)) / bf - atan(double(x) / bf);
}
double b_err_org(long x) {
  return double(Benammar_orginal(x)) / bf - atan(double(x) / bf);
}
double b_err_our(long x) {
  return double(Benammar_our(x)) / bf - atan(double(x) / bf);
}
double r_err_org(long x) {
  return double(Rajan_orginal(x)) / bf - atan(double(x) / bf);
}
double r_err_our(long x) {
  return double(Rajan_our(x)) / bf - atan(double(x) / bf);
}


void setup() {
  Serial.begin(512000L);  //(9600); //do zgrywaia pliku (460800L);

  Serial.println("START SETUP");

  TCCR1B = 0x01; //wystartowanie timera z prescalerem /1

  Serial.println("START TEST");

  double error_z_our = 0;
  double error_l_our = 0;
  double error_b_our = 0;
  double error_r_our = 0;

  double max_error_z_our = 0;
  double max_error_l_our = 0;
  double max_error_b_our = 0;
  double max_error_r_our = 0;

  double max_error_z_our4x = 0;
  double max_error_l_our4x = 0;
  double max_error_b_our4x = 0;
  double max_error_r_our4x = 0;

  double mean_error_z_our = 0;
  double mean_error_l_our = 0;
  double mean_error_b_our = 0;
  double mean_error_r_our = 0;

  double error_z_org = 0;
  double error_l_org = 0;
  double error_b_org = 0;
  double error_r_org = 0;

  double max_error_z_org = 0;
  double max_error_l_org = 0;
  double max_error_b_org = 0;
  double max_error_r_org = 0;

  double max_error_z_org4x = 0;
  double max_error_l_org4x = 0;
  double max_error_b_org4x = 0;
  double max_error_r_org4x = 0;

  double mean_error_z_org = 0;
  double mean_error_l_org = 0;
  double mean_error_b_org = 0;
  double mean_error_r_org = 0;

  float step = 0.00001f;  //do zgrywaia pliku (0.00001f); //ok 200k Sampli
  float currentValue = -1.0f + step;
  float maxValue = 1.0f;

  long x;

  double count = 0;
  double count1M = 0;




  Serial.print("step:     ");  Serial.println(step, 10);
  Serial.print("minValue: ");  Serial.println(currentValue, 10);
  Serial.print("maxValue: ");  Serial.println(maxValue - step, 10);

  //wydruk do konsoli dla CSV!!!
  Serial.print("x"); Serial.print(";");
  Serial.print("x"); Serial.print(";");
  Serial.print("z_org"); Serial.print(";");
  Serial.print("z_our"); Serial.print(";");
  Serial.print("l_org"); Serial.print(";");
  Serial.print("l_our"); Serial.print(";");
  Serial.print("b_org"); Serial.print(";");
  Serial.print("b_our"); Serial.print(";");
  Serial.print("r_org"); Serial.print(";");
  Serial.print("r_our"); Serial.print(";");
  Serial.print("satan");
  Serial.println("");

  /*
  //błędy transmisji dla x
  long x4err []={
    0xFACE7880, 
    0xFAE9EE40,
    0x6698D08,
    0x4BB31C8,
    0x2DEB208,
    0xFF921B56,
    0x4B91508,
    0xFF784E2E,
    0x12B4330,
    0x614EF88,
    0xF8B03940,
    0x13C2D3C,
    0x5B69448
    };

  for (int i=0;i<13;i++){
    x=x4err[i];
*/
  long i = 1;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);  //0.7f*bf;//
    //Serial.print("   x="); Serial.println(x,HEX);
    error_z_our = z_err_our(x);
    error_l_our = l_err_our(x);
    error_b_our = b_err_our(x);
    error_r_our = r_err_our(x);

    error_z_org = z_err_org(x);
    error_l_org = l_err_org(x);
    error_b_org = b_err_org(x);
    error_r_org = r_err_org(x);

    if (abs(max_error_z_our) < abs(error_z_our)) {      max_error_z_our = error_z_our;      max_error_z_our4x = x;    }
    if (abs(max_error_l_our) < abs(error_l_our)) {      max_error_l_our = error_l_our;      max_error_l_our4x = x;    }
    if (abs(max_error_b_our) < abs(error_b_our)) {      max_error_b_our = error_b_our;      max_error_b_our4x = x;    }
    if (abs(max_error_r_our) < abs(error_r_our)) {      max_error_r_our = error_r_our;      max_error_r_our4x = x;    }

    if (abs(max_error_z_org) < abs(error_z_org)) {      max_error_z_org = error_z_org;      max_error_z_org4x = x;    }
    if (abs(max_error_l_org) < abs(error_l_org)) {      max_error_l_org = error_l_org;      max_error_l_org4x = x;    }
    if (abs(max_error_b_org) < abs(error_b_org)) {      max_error_b_org = error_b_org;      max_error_b_org4x = x;    }
    if (abs(max_error_r_org) < abs(error_r_org)) {      max_error_r_org = error_r_org;      max_error_r_org4x = x;    }

    if (i == 1) {
      mean_error_z_our = abs(error_z_our);
      mean_error_l_our = abs(error_l_our);
      mean_error_b_our = abs(error_b_our);
      mean_error_r_our = abs(error_r_our);

      mean_error_z_org = abs(error_z_org);
      mean_error_l_org = abs(error_l_org);
      mean_error_b_org = abs(error_b_org);
      mean_error_r_org = abs(error_r_org);
    } else {
      mean_error_z_our = (mean_error_z_our + abs(error_z_our));
      mean_error_l_our = (mean_error_l_our + abs(error_l_our));
      mean_error_b_our = (mean_error_b_our + abs(error_b_our));
      mean_error_r_our = (mean_error_r_our + abs(error_r_our));

      mean_error_z_org = (mean_error_z_org + abs(error_z_org));
      mean_error_l_org = (mean_error_l_org + abs(error_l_org));
      mean_error_b_org = (mean_error_b_org + abs(error_b_org));
      mean_error_r_org = (mean_error_r_org + abs(error_r_org));
    }

    currentValue = currentValue + step;

    /*
    double satan = atan(double(x)/bf);
    double z_org = double(Zarowski_orginal(x))/bf;
    double z_our = double(Zarowski_our(x))/bf;
    double l_org = double(Lynos_orginal(x))/bf;
    double l_our = double(Lynos_our(x))/bf;
    double b_org = double(Benammar_orginal(x))/bf;
    double b_our = double(Benammar_our(x))/bf;
    double r_org = double(Rajan_orginal(x))/bf;
    double r_our = double(Rajan_our(x))/bf;
    
    Serial.print("  atan(x) = "); Serial.print(satan, 40); Serial.print("  for x = "); Serial.println(double(x)/bf,40); 
    Serial.print("  z_org(x)= "); Serial.print(z_org, 40); Serial.print("  for x = "); Serial.println(double(x),2); 
    Serial.print("  z_our(x)= "); Serial.print(z_our, 40); Serial.print("  for x = "); Serial.println(x,HEX); 
    Serial.print("  l_org(x)= "); Serial.print(l_org, 40); Serial.print("  for x = "); Serial.println(double(x),2); 
    Serial.print("  l_our(x)= "); Serial.print(l_our, 40); Serial.print("  for x = "); Serial.println(x,HEX); 
    Serial.print("  b_org(x)= "); Serial.print(b_org, 40); Serial.print("  for x = "); Serial.println(double(x),2); 
    Serial.print("  b_our(x)= "); Serial.print(b_our, 40); Serial.print("  for x = "); Serial.println(x,HEX);
    Serial.print("  r_org(x)= "); Serial.print(r_org, 40); Serial.print("  for x = "); Serial.println(double(x),2); 
    Serial.print("  r_our(x)= "); Serial.print(r_our, 40); Serial.print("  for x = "); Serial.println(x,HEX);  */

    //count++;
    //if (count == 100000) {      count = 0;      count1M++;      Serial.print("100k SAMPLI: x");      Serial.println(count1M);    }

    
    double satan = atan(double(x)/bf);
    long z_org = Zarowski_orginal(x);
    long z_our = Zarowski_our(x);
    long l_org = Lynos_orginal(x);
    long l_our = Lynos_our(x);
    long b_org = Benammar_orginal(x);
    long b_our = Benammar_our(x);
    long r_org = Rajan_orginal(x);
    long r_our = Rajan_our(x);

    //wydruk do konsoli dla CSV!!!
    Serial.print(x,DEC); Serial.print(";");
    Serial.print(x,HEX); Serial.print(";");
    Serial.print(z_org,DEC); Serial.print(";");
    Serial.print(z_our,DEC); Serial.print(";");
    Serial.print(l_org,DEC); Serial.print(";");
    Serial.print(l_our,DEC); Serial.print(";");
    Serial.print(b_org,DEC); Serial.print(";");
    Serial.print(b_our,DEC); Serial.print(";");
    Serial.print(r_org,DEC); Serial.print(";");
    Serial.print(r_our,DEC); Serial.print(";");
    Serial.print(satan,40);
    Serial.println("");
    
  }
  i = i - 1;  //odlicza o jeden cykl więcej niż wykonano


  // Przeliczanie wyników na stopnie
  double dmaxGr_z_our = max_error_z_our * 180.0 / PI;
  double dmaxGr_l_our = max_error_l_our * 180.0 / PI;
  double dmaxGr_b_our = max_error_b_our * 180.0 / PI;
  double dmaxGr_r_our = max_error_r_our * 180.0 / PI;

  double dmaxGr_z_org = max_error_z_org * 180.0 / PI;
  double dmaxGr_l_org = max_error_l_org * 180.0 / PI;
  double dmaxGr_b_org = max_error_b_org * 180.0 / PI;
  double dmaxGr_r_org = max_error_r_org * 180.0 / PI;

  mean_error_z_our = (mean_error_z_our/i) * 180.0 / PI;
  mean_error_l_our = (mean_error_l_our/i) * 180.0 / PI;
  mean_error_b_our = (mean_error_b_our/i) * 180.0 / PI;
  mean_error_r_our = (mean_error_r_our/i) * 180.0 / PI;

  mean_error_z_org = (mean_error_z_org/i) * 180.0 / PI;
  mean_error_l_org = (mean_error_l_org/i) * 180.0 / PI;
  mean_error_b_org = (mean_error_b_org/i) * 180.0 / PI;
  mean_error_r_org = (mean_error_r_org/i) * 180.0 / PI;

  Serial.println("");
  Serial.println("OUR ALGORITHMS:");
  Serial.print("Maximum error for Zarowski_our (in degrees): ");  Serial.print(dmaxGr_z_our, 20);  Serial.print("   for x: ");  Serial.println(max_error_z_our4x, 20);
  Serial.print("Maximum error for Lynos_our (in degrees):    ");  Serial.print(dmaxGr_l_our, 20);  Serial.print("   for x: ");  Serial.println(max_error_l_our4x, 20);
  Serial.print("Maximum error for Benammar_our (in degrees): ");  Serial.print(dmaxGr_b_our, 20);  Serial.print("   for x: ");  Serial.println(max_error_b_our4x, 20);
  Serial.print("Maximum error for Rajan_our (in degrees):    ");  Serial.print(dmaxGr_r_our, 20);  Serial.print("   for x: ");  Serial.println(max_error_r_our4x, 20);
  Serial.println("ORGINAL ALGORITHMS:");
  Serial.print("Maximum error for Zarowski_org (in degrees): ");  Serial.print(dmaxGr_z_org, 20);  Serial.print("   for x: ");  Serial.println(max_error_z_org4x, 20);
  Serial.print("Maximum error for Lynos_org (in degrees):    ");  Serial.print(dmaxGr_l_org, 20);  Serial.print("   for x: ");  Serial.println(max_error_l_org4x, 20);
  Serial.print("Maximum error for Benammar_org (in degrees): ");  Serial.print(dmaxGr_b_org, 20);  Serial.print("   for x: ");  Serial.println(max_error_b_org4x, 20);
  Serial.print("Maximum error for Rajan_org (in degrees):    ");  Serial.print(dmaxGr_r_org, 20);  Serial.print("   for x: ");  Serial.println(max_error_r_org4x, 20);
  Serial.println("");

  Serial.println("OUR ALGORITHMS:");
  Serial.print("Mean error for Zarowski_our (in degrees): ");  Serial.println(mean_error_z_our, 20);
  Serial.print("Mean error for Lynos_our (in degrees):    ");  Serial.println(mean_error_l_our, 20);
  Serial.print("Mean error for Benammar_our (in degrees): ");  Serial.println(mean_error_b_our, 20);
  Serial.print("Mean error for Rajan_our (in degrees):    ");  Serial.println(mean_error_r_our, 20);
  Serial.println("ORGINAL ALGORITHMS:");
  Serial.print("Mean error for Zarowski_org (in degrees): ");  Serial.println(mean_error_z_org, 20);
  Serial.print("Mean error for Lynos_org (in degrees):    ");  Serial.println(mean_error_l_org, 20);
  Serial.print("Mean error for Benammar_org (in degrees): ");  Serial.println(mean_error_b_org, 20);
  Serial.print("Mean error for Rajan_org (in degrees):    ");  Serial.println(mean_error_r_org, 20);
  Serial.println("END");
  Serial.println("");

}

void loop() {
}
