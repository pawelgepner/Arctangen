
#include <math.h>

#define biti (5)
#define bitf (27)

const double bf = 1 << bitf;

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


  //long cykle =0;

void setup() {
  //cykle = SysTick->VAL;
  float step = 0.00001f;  // (0.00001f); //ok 200k Sampli
  float currentValue = 0.0f + step;
  float maxValue = 1.0f;
  long y;
  long i = 1;
  for (i = 1; currentValue < maxValue; i++) {
    y = long(currentValue * 1304065766);

    //long y_cor = cordic_arctan_clasic(X, y);
    long y_cor = cordic_arctan_our(X, y);
    
    Serial.print(y_cor);
  }
}

void loop() {
}
