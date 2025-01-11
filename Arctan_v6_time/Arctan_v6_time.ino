
#include <math.h>

#define biti (5)
#define bitf (27)

const double bf = 1 << bitf;

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

  long long start = 0;
  long long finish = 0;

  double sum_time_satan = 0;
  double sum_time_z_org = 0;
  double sum_time_z_our = 0;
  double sum_time_l_org = 0;
  double sum_time_l_our = 0;
  double sum_time_b_org = 0;
  double sum_time_b_our = 0;
  double sum_time_r_org = 0;
  double sum_time_r_our = 0;

  double mean_time_satan = 0;
  double mean_time_z_org = 0;
  double mean_time_z_our = 0;
  double mean_time_l_org = 0;
  double mean_time_l_our = 0;
  double mean_time_b_org = 0;
  double mean_time_b_our = 0;
  double mean_time_r_org = 0;
  double mean_time_r_our = 0;


  double sum_time_satan2 = 0;
  double mean_time_satan2 = 0;

  double satan = 0;
  long z_org = 0;
  long z_our = 0;
  long l_org = 0;
  long l_our = 0;
  long b_org = 0;
  long b_our = 0;
  long r_org = 0;
  long r_our = 0;

  float step = 0.00001f;  //(0.00001f); //ok 200k Sampli
  float currentValue = -1.0f + step;
  float maxValue = 1.0f;

  long x;

  Serial.print("step:     ");  Serial.println(step, 10);
  Serial.print("minValue: ");  Serial.println(currentValue, 10);
  Serial.print("maxValue: ");  Serial.println(maxValue - step, 10);

  noInterrupts();

  double i = 1;

  long sum_n=0;
  double sum_d=0;

  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    satan = atan(currentValue);
    sum_d=sum_d+satan;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_satan = finish-start;} else {sum_time_satan=111111;}
    
  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    z_org = Zarowski_orginal(x);
    sum_n=sum_n+z_org;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_z_org = finish-start;} else {sum_time_z_org=111111;}

  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    z_our = Zarowski_our(x);
    sum_n=sum_n+z_our;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_z_our = finish-start;} else {sum_time_z_our=111111;}

  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    l_org = Lynos_orginal(x);
    sum_n=sum_n+l_org;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_l_org = finish-start;} else {sum_time_l_org=111111;}

  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    l_our = Lynos_our(x);
    sum_n=sum_n+l_our;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_l_our = finish-start;} else {sum_time_l_our=111111;}
    
  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    b_org = Benammar_orginal(x);
    sum_n=sum_n+b_org;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_b_org = finish-start;} else {sum_time_b_org=111111;}

  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    b_our = Benammar_our(x);
    sum_n=sum_n+b_our;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_b_our = finish-start;} else {sum_time_b_our=111111;}
    
  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    r_org = Rajan_orginal(x);
    sum_n=sum_n+r_org;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_r_org = finish-start;} else {sum_time_r_org=111111;}

  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    r_our = Rajan_our(x);
    sum_n=sum_n+r_our;
  }
  //finish = TC0->TC_CHANNEL[0].TC_CV;  sum_time_r_our = finish-start;
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_r_our = finish-start;} else {sum_time_r_our=111111;}

  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    satan = atan(currentValue);
    sum_d=sum_d+satan;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_satan2 = finish-start;} else {sum_time_satan2=111111;}


  interrupts();

  i = i - 1;  //odlicza o jeden cykl więcej niż wykonano

  mean_time_satan = (sum_time_satan*2) / double(i);
  mean_time_z_our = (sum_time_z_our*2) / double(i);
  mean_time_l_our = (sum_time_l_our*2) / double(i);
  mean_time_b_our = (sum_time_b_our*2) / double(i);
  mean_time_r_our = (sum_time_r_our*2) / double(i);
  mean_time_z_org = (sum_time_z_org*2) / double(i);
  mean_time_l_org = (sum_time_l_org*2) / double(i);
  mean_time_b_org = (sum_time_b_org*2) / double(i);
  mean_time_r_org = (sum_time_r_org*2) / double(i);
  mean_time_satan2 = (sum_time_satan2*2) / double(i);

  Serial.print("sum_n = ");  Serial.println(sum_n);
  Serial.print("sum_d = ");  Serial.println(sum_d);

  Serial.print("cycles = i = ");  Serial.println(i);
  Serial.print("mean_time_satan = ");  Serial.println(mean_time_satan, 5);
  Serial.print("mean_time_z_our = ");  Serial.println(mean_time_z_our, 5);
  Serial.print("mean_time_l_our = ");  Serial.println(mean_time_l_our, 5);
  Serial.print("mean_time_b_our = ");  Serial.println(mean_time_b_our, 5);
  Serial.print("mean_time_r_our = ");  Serial.println(mean_time_r_our, 5);
  Serial.print("mean_time_z_org = ");  Serial.println(mean_time_z_org, 5);
  Serial.print("mean_time_l_org = ");  Serial.println(mean_time_l_org, 5);
  Serial.print("mean_time_b_org = ");  Serial.println(mean_time_b_org, 5);
  Serial.print("mean_time_r_org = ");  Serial.println(mean_time_r_org, 5);
  Serial.print("mean_time_satan2 = ");  Serial.println(mean_time_satan2, 5);
  Serial.println("");
  Serial.print("sum_time_satan = ");  Serial.println(sum_time_satan, 5);
  Serial.print("sum_time_z_our = ");  Serial.println(sum_time_z_our, 5);
  Serial.print("sum_time_l_our = ");  Serial.println(sum_time_l_our, 5);
  Serial.print("sum_time_b_our = ");  Serial.println(sum_time_b_our, 5);
  Serial.print("sum_time_r_our = ");  Serial.println(sum_time_r_our, 5);
  Serial.print("sum_time_z_org = ");  Serial.println(sum_time_z_org, 5);
  Serial.print("sum_time_l_org = ");  Serial.println(sum_time_l_org, 5);
  Serial.print("sum_time_b_org = ");  Serial.println(sum_time_b_org, 5);
  Serial.print("sum_time_r_org = ");  Serial.println(sum_time_r_org, 5);
  Serial.print("sum_time_satan2 = ");  Serial.println(sum_time_satan2, 5);
}

void loop() {
}
