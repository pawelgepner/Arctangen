
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

const double bf = 134217728; //1 << bitf;

volatile double x_atanbf = 0;

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


volatile unsigned int cor_cla_iter = 0;
volatile unsigned int cor_our_iter = 0;


const long X = 65536;

const int N_clasic = 16;
const long arctan_table_clasic[N_clasic] = {
  long(0.7853981633974483 * bf), long(0.4636476090008061 * bf), long(0.24497866312686414 * bf),
  long(0.12435499454676144 * bf), long(0.06241880999595735 * bf), long(0.031239833430268277 * bf),
  long(0.015623728620476831 * bf), long(0.007812341060101111 * bf), long(0.0039062301319669718 * bf),
  long(0.0019531225164788188 * bf), long(0.0009765621895593195 * bf),long(0.000488281211194898 * bf),
  long(0.00024414062014936177 * bf),long( 0.00012207031189367021 * bf), long(.103515617420877e-05 * bf),
  long(3.0517578115526096e-05 * bf)
};

long cordic_arctan_clasic(long x, long y) {
  cor_cla_iter=0;
  long angle = 0;
  long x_new=0;
  long y_new=0;
  for (int i = 0; i < N_clasic; ++i) {
    if (y > 0) {
      x_new = x + (y >> i);
      y_new = y - (x >> i);
      angle += arctan_table_clasic[i];
      x = x_new;
      y = y_new;
    } else {
      x_new = x - (y >> i);
      y_new = y + (x >> i);
      angle -= arctan_table_clasic[i];
      x = x_new;
      y = y_new;
    }
    cor_cla_iter++;
  }
  return angle;
}


const int N_our = 31;
const long arctan_table_our[] = {
  long(0.785398163367062807083129882812 * bf),
  long(0.463647609110921621322631835938 * bf),
  long(0.244978663045912981033325195312 * bf),
  long(0.124354994390159845352172851562 * bf),
  long(0.0624188100919127464294433593750 * bf),
  long(0.0312398332171142101287841796875 * bf),
  long(0.0156237287446856498718261718750 * bf),
  long(0.00781234120950102806091308593750 * bf),
  long(0.00390622997656464576721191406250 * bf),
  long(0.00195312267169356346130371093750 * bf),
  long(0.000976562034338712692260742187500 * bf),
  long(0.000488281250000000000000000000000 * bf),
  long(0.000244140625000000000000000000000 * bf),
  long(0.000122070312500000000000000000000 * bf),
  long(0.000061035156250000000000000000000 * bf),
  long(0.000030517578125000000000000000000 * bf),
  long(0.000015258789062500000000000000000 * bf),
  long(0.000007629394531250000000000000000 * bf),
  long(0.000003814697265625000000000000000 * bf),
  long(0.000001907348632812500000000000000 * bf),
  long(0.000000953674316406250000000000000 * bf),
  long(0.000000476837158203125000000000000 * bf),
  long(0.000000238418579101562500000000000 * bf),
  long(0.000000119209289550781250000000000 * bf),
  long(0.000000059604644775390625000000000 * bf),
  long(0.000000029802322387695312500000000 * bf),
  long(0.000000014901161193847656250000000 * bf),
  long(0.000000007450580596923828125000000 * bf),
  long(0.000000003725290298461914062500000 * bf),
  long(0.000000001862645149230957031250000 * bf),
  long(0.000000000931322574615478515625000 * bf),
  long(0.000000000465661287307739257812500 * bf)
};

long cordic_arctan_our(long x, long y) {
  cor_our_iter=0;
  long angle = 0;
  //int ii = 0;
  long dx = x;
  int i = 0;
  while (y > 1) {
    while (y < dx) {
      dx >>= 1;
      i++;
    }
    x += (y >> i);
    y -= dx;
    dx = (x >> i);
    angle += arctan_table_our[i];
    cor_our_iter++;
  }
  return angle;
}

double cor_err_clasic(long x, long y) {
  return double(cordic_arctan_clasic(x, y)) / bf - x_atanbf;
}

double cor_err_our(long x, long y) {
  return double(cordic_arctan_our(x, y)) / bf - x_atanbf;
}


void setup() {
  Serial.begin(512000L);  //(9600); //do zgrywaia pliku (460800L);

  Serial.println("START SETUP");

  TCCR1B = 0x01; //wystartowanie timera z prescalerem /1

  Serial.println("START TEST");

  double error_cor_clasic = 0;
  double max_error_cor_clasic = 0;
  double max_error_cor_clasic4x = 0;
  double mean_error_cor_clasic = 0;

  double error_cor_our = 0;
  double max_error_cor_our = 0;
  double max_error_cor_our4x = 0;
  double mean_error_cor_our = 0;

  float step = 0.5f;  //do zgrywaia pliku (0.000005f); //ok 200k Sampli
  float step0 = 0.000000001f; //do zgrywaia pliku (0.000000001f);
  float step1 = 0.0000067f; //do zgrywaia pliku (0.0000067f);
  float currentValue = 0.0f + step0;
  float maxValue = 1.0f;

  long y;

  double count = 0;
  double count1M = 0;

  Serial.print("step:     ");  Serial.println(step, 10);
  Serial.print("minValue: ");  Serial.println(currentValue, 10);
  Serial.print("maxValue: ");  Serial.println(maxValue - step, 10);
  
  //wydruk do konsoli dla CSV!!!
  Serial.print("X"); Serial.print(";");
  Serial.print("y"); Serial.print(";");
  Serial.print("cor_cla"); Serial.print(";");
  Serial.print("cor_our"); Serial.print(";");
  Serial.print("cor_cla_iter"); Serial.print(";");
  Serial.print("cor_our_iter"); Serial.print(";");
  Serial.print("satan");
  Serial.println("");


  /*
  //błędy transmisji dla x
  long x4err []={
    671103872,
    671129984
    };

  for (int j=0;j<2;j++){
    y=x4err[j];
*/

  long i = 1;
  for (i = 1; currentValue < maxValue; i++) {
    y = long(currentValue * 1304065766);  //0.7f*bf;//
    //Serial.print("   x="); Serial.println(x,HEX);


    x_atanbf = atan(double(y)/double(X));
    error_cor_clasic = cor_err_clasic(X, y);
    error_cor_our = cor_err_our(X, y);
    //long zakres od -2147483648 (8000 0000)  do 2147483647 (7FFF FFFF)


    if (abs(max_error_cor_clasic) < abs(error_cor_clasic)) {      max_error_cor_clasic = error_cor_clasic;      max_error_cor_clasic4x = y;    }
    if (abs(max_error_cor_our) < abs(error_cor_our)) {      max_error_cor_our = error_cor_our;      max_error_cor_our4x = y;    }

    if (i == 1) {
      mean_error_cor_clasic = abs(error_cor_clasic);
      mean_error_cor_our = abs(error_cor_our);
    } else {
      mean_error_cor_clasic = (mean_error_cor_clasic + abs(error_cor_clasic));
      mean_error_cor_our = (mean_error_cor_our + abs(error_cor_our));
    }


    /*
    double satan = atan(double(y)/double(X));
    double cor_clasic = double(cordic_arctan_clasic(X, y))/bf;
    double cor_our = double(cordic_arctan_our(X, y))/bf;
    
    Serial.print("  atan(y/x)      = "); Serial.print(satan, 40);      Serial.print("  for y/x = "); Serial.println(double(y)/double(X),5); 
    Serial.print("  cor_clasic(y/x)= "); Serial.print(cor_clasic, 40); Serial.print("  for y   = "); Serial.println(double(y),2);
    Serial.print("  cor_our(y/x)   = "); Serial.print(cor_our, 40);    Serial.print("  for y   = "); Serial.println(double(y),2);
*/
    //count++;
    //if (count == 100000) {      count = 0;      count1M++;      Serial.print("100k SAMPLI: x");      Serial.println(count1M);    }


    x_atanbf = atan(double(y)/double(X));
    double satan = x_atanbf;
    long cor_cla = cordic_arctan_clasic(X, y);
    long cor_our = cordic_arctan_our(X, y);

    //wydruk do konsoli dla CSV!!!
    Serial.print(X,DEC); Serial.print(";");
    Serial.print(y,DEC); Serial.print(";");
    Serial.print(cor_cla,DEC); Serial.print(";");
    Serial.print(cor_our,DEC); Serial.print(";");
    Serial.print(cor_cla_iter,DEC); Serial.print(";");
    Serial.print(cor_our_iter,DEC); Serial.print(";");
    Serial.print(satan,40);
    Serial.println("");
    
    if (y<X) {
      currentValue = currentValue + step0;
    } else{
      currentValue = currentValue + step1;
    }
  }
  i = i - 1;  //odlicza o jeden cykl więcej niż wykonano


  // Przeliczanie wyników na stopnie
  double dmaxGr_error_cor_clasic = max_error_cor_clasic * 180.0 / PI;
  double dmaxGr_error_cor_our = max_error_cor_our * 180.0 / PI;

  mean_error_cor_clasic = (mean_error_cor_clasic/i) * 180.0 / PI;
  mean_error_cor_our = (mean_error_cor_our/i) * 180.0 / PI;

  Serial.print("cycles = i = ");  Serial.println(i);
  Serial.println("");
  Serial.println("OUR ALGORITHMS:");
  Serial.print("Maximum error for cordic our (in degrees): ");  Serial.print(dmaxGr_error_cor_our, 20);  Serial.print("   for Y: ");  Serial.println(max_error_cor_our4x, 20);

  Serial.println("ORGINAL ALGORITHMS:");
  Serial.print("Maximum error for cordic clasic (in degrees): ");  Serial.print(dmaxGr_error_cor_clasic, 20);  Serial.print("   for Y: ");  Serial.println(max_error_cor_clasic4x, 20);
  Serial.println("");

  Serial.println("OUR ALGORITHMS:");
  Serial.print("Mean error for cordic our (in degrees): ");  Serial.println(mean_error_cor_our, 20);
  
  Serial.println("ORGINAL ALGORITHMS:");
  Serial.print("Mean error for cordic clasic (in degrees): ");  Serial.println(mean_error_cor_clasic, 20);
  Serial.println("END");
  Serial.println("");

}

void loop() {
}
