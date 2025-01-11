
#include <math.h>

#define biti (5)
#define bitf (27)

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


  //long cykle =0;

void setup() {
  //cykle = SysTick->VAL;
  float step = 0.00001f;  // (0.00001f); //ok 200k Sampli
  float currentValue = -1.0f + step;
  float maxValue = 1.0f;
  long x;
  long i = 1;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);  

    //double y = atan(currentValue); 
    //long y = Zarowski_orginal(x);
    //long y = Zarowski_our(x);
    //long y = Lynos_orginal(x);
    //long y = Lynos_our(x);
    //long y = Benammar_orginal(x);
    //long y = Benammar_our(x);
    //long y = Rajan_orginal(x);
    long y = Rajan_our(x);

    Serial.print(y);
  }
}

void loop() {
}
