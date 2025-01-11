
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
            }
  return angle;
}

double cor_err_clasic(long x, long y) {
  return double(cordic_arctan_clasic(x, y)) / bf - atan(double(y)/double(x));
}

double cor_err_our(long x, long y) {
  return double(cordic_arctan_our(x, y)) / bf - atan(double(y)/double(x));
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
  double sum_time_cordic_our = 0;
  double sum_time_cordic_clasic = 0;

  double mean_time_satan = 0;
  double mean_time_cordic_our = 0;
  double mean_time_cordic_clasic = 0;


  double sum_time_satan2 = 0;
  double mean_time_satan2 = 0;

  double satan = 0;
  long cordic_our = 0;
  long cordic_clasic = 0;

  float step = 0.000005f;  //(0.00001f); //ok 200k Sampli
  float currentValue = 0.0f + step;
  float maxValue = 1.0f;

  long y;

  Serial.print("step:     ");  Serial.println(step, 10);
  Serial.print("minValue: ");  Serial.println(currentValue, 10);
  Serial.print("maxValue: ");  Serial.println(maxValue - step, 10);

  noInterrupts();

  double i = 1;

  long sum_n=0;
  double sum_d=0;

  currentValue = 0.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    y = long(currentValue * 1304065766);    currentValue = currentValue + step;
    satan = atan(double(y)/double(X));
    sum_d=sum_d+satan;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_satan = finish-start;} else {sum_time_satan=111111;}
    
  currentValue = 0.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    y = long(currentValue * bf);    currentValue = currentValue + step;
    cordic_clasic = cordic_arctan_clasic(X, y);
    sum_n=sum_n+cordic_clasic;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_cordic_clasic = finish-start;} else {sum_time_cordic_clasic=111111;}

  currentValue = 0.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    y = long(currentValue * bf);    currentValue = currentValue + step;
    cordic_our = cordic_arctan_our(X, y);
    sum_n=sum_n+cordic_our;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_cordic_our = finish-start;} else {sum_time_cordic_our=111111;}

  currentValue = 0.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    y = long(currentValue * bf);    currentValue = currentValue + step;
    satan = atan(double(y)/double(X));
    sum_d=sum_d+satan;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_satan2 = finish-start;} else {sum_time_satan2=111111;}


  interrupts();

  i = i - 1;  //odlicza o jeden cykl więcej niż wykonano

  mean_time_satan = (sum_time_satan*2) / double(i);
  mean_time_cordic_clasic = (sum_time_cordic_clasic*2) / double(i);
  mean_time_cordic_our = (sum_time_cordic_our*2) / double(i);
  
  mean_time_satan2 = (sum_time_satan2*2) / double(i);

  Serial.print("sum_n = ");  Serial.println(sum_n);
  Serial.print("sum_d = ");  Serial.println(sum_d);

  Serial.print("cycles = i = ");  Serial.println(i);
  Serial.print("mean_time_satan         = ");  Serial.println(mean_time_satan, 5);
  Serial.print("mean_time_cordic_clasic = ");  Serial.println(mean_time_cordic_clasic, 5);
  Serial.print("mean_time_cordic_our    = ");  Serial.println(mean_time_cordic_our, 5);
  Serial.print("mean_time_satan2        = ");  Serial.println(mean_time_satan2, 5);
  Serial.println("");
  Serial.print("sum_time_satan         = ");  Serial.println(sum_time_satan, 5);
  Serial.print("sum_time_cordic_clasic = ");  Serial.println(sum_time_cordic_clasic, 5);
  Serial.print("sum_time_cordic_our    = ");  Serial.println(sum_time_cordic_our, 5);
  Serial.print("sum_time_satan2        = ");  Serial.println(sum_time_satan2, 5);
}

void loop() {
}
