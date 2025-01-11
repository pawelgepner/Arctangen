
#include <math.h>

#define biti (2)
#define bitf (30)

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



long P4(long x){
  const long k1 = long(1.0025034607882041432070217945691461 * bf);
  const long k2 = long(-0.013679575696677310464002349120340933 * bf);
  const long k3 = long(-0.34402713551558530645075676095404599 * bf);
  const long k4 = long(0.14071654365142265977615479831981054 * bf);
  /*Serial.print("P4_k1;");  Serial.print(k1, DEC); Serial.print(";");  Serial.println(double(k1)/bf,30);
  Serial.print("P4_k2;");  Serial.print(k2, DEC); Serial.print(";");  Serial.println(double(k2)/bf,30);
  Serial.print("P4_k3;");  Serial.print(k3, DEC); Serial.print(";");  Serial.println(double(k3)/bf,30);
  Serial.print("P4_k4;");  Serial.print(k4, DEC); Serial.print(";");  Serial.println(double(k4)/bf,30);*/
  long xa = abs(x);
  return Multiply(x,(k1 + Multiply(xa,(k2 + Multiply(xa,(k3 + Multiply(k4,xa)))))));
//return x * (k1 + xa * (k2 + xa * (k3 + k4 * xa)))
}

long P5(long x){
  const long k1 = long(0.99872459843609849477918094400681791 * bf);
  const long k2 = long(0.020835029941766873180965040229539301 * bf);
  const long k3 = long(-0.44437860098439551704663289431391845 * bf);
  const long k4 = long(0.25712163230498072978472105582432498 * bf);
  const long k5 = long(-0.046880178811481034204063201159136027 * bf);
  /*Serial.print("P5_k1;");  Serial.print(k1, DEC); Serial.print(";");  Serial.println(double(k1)/bf,30);
  Serial.print("P5_k2;");  Serial.print(k2, DEC); Serial.print(";");  Serial.println(double(k2)/bf,30);
  Serial.print("P5_k3;");  Serial.print(k3, DEC); Serial.print(";");  Serial.println(double(k3)/bf,30);
  Serial.print("P5_k4;");  Serial.print(k4, DEC); Serial.print(";");  Serial.println(double(k4)/bf,30);
  Serial.print("P5_k5;");  Serial.print(k5, DEC); Serial.print(";");  Serial.println(double(k5)/bf,30);*/
  long xa = abs(x);
  return Multiply(x,(k1 + Multiply(xa,(k2 + Multiply(xa,(k3 + Multiply(xa,(k4 + Multiply(k5,xa)))))))));
//return x * (k1 + xa * (k2 + xa * (k3 + xa * (k4 + k5 * xa))))
}

long P6(long x){
  const long k1 = long(0.99957274398868036466175439328131168 * bf);
  const long k2 = long(0.0081073805979023528501915581481079948 * bf);
  const long k3 = long(-0.38306246882783360559402899745151711 * bf);
  const long k4 = long(0.12932770870236211115108872301602014 * bf);
  const long k5 = long(0.073227807065460482958962366420611951 * bf);
  const long k6 = long(-0.041782005205202704002747072607342900 * bf);
  /*Serial.print("P6_k1;");  Serial.print(k1, DEC); Serial.print(";");  Serial.println(double(k1)/bf,30);
  Serial.print("P6_k2;");  Serial.print(k2, DEC); Serial.print(";");  Serial.println(double(k2)/bf,30);
  Serial.print("P6_k3;");  Serial.print(k3, DEC); Serial.print(";");  Serial.println(double(k3)/bf,30);
  Serial.print("P6_k4;");  Serial.print(k4, DEC); Serial.print(";");  Serial.println(double(k4)/bf,30);
  Serial.print("P6_k5;");  Serial.print(k5, DEC); Serial.print(";");  Serial.println(double(k5)/bf,30);
  Serial.print("P6_k6;");  Serial.print(k6, DEC); Serial.print(";");  Serial.println(double(k6)/bf,30);*/
  long xa = abs(x);
  return Multiply(x,(k1 + Multiply(xa,(k2 + Multiply(xa,(k3 + Multiply(xa,(k4 + Multiply(xa,(k5 + Multiply(k6,xa)))))))))));
//return x * (k1 + xa * (k2 + xa * (k3 + xa * (k4 + xa * (k5 + k6 * xa)))))
}
 
long P7(long x){
  const long k1 = long(0.999986014690233669198646555331259321605492795 * bf);
  const long k2 = long(0.0000267112350723644112343661799756864018838072241 * bf);
  const long k3 = long(-0.330449690192830935748683860800897337070635922 * bf);
  const long k4 = long(-0.0281155086387117101531648219939944994865491542 * bf);
  const long k5 = long(0.311316333734556780927317449915075557725828681 * bf);
  const long k6 = long(-0.218804577133295874357838200079088802949306408 * bf);
  const long k7 = long(0.0514392966229627485943918792179289871543520712 * bf);
  /*Serial.print("P7_k1;");  Serial.print(k1, DEC); Serial.print(";");  Serial.println(double(k1)/bf,30);
  Serial.print("P7_k2;");  Serial.print(k2, DEC); Serial.print(";");  Serial.println(double(k2)/bf,30);
  Serial.print("P7_k3;");  Serial.print(k3, DEC); Serial.print(";");  Serial.println(double(k3)/bf,30);
  Serial.print("P7_k4;");  Serial.print(k4, DEC); Serial.print(";");  Serial.println(double(k4)/bf,30);
  Serial.print("P7_k5;");  Serial.print(k5, DEC); Serial.print(";");  Serial.println(double(k5)/bf,30);
  Serial.print("P7_k6;");  Serial.print(k6, DEC); Serial.print(";");  Serial.println(double(k6)/bf,30);
  Serial.print("P7_k7;");  Serial.print(k7, DEC); Serial.print(";");  Serial.println(double(k7)/bf,30);*/
  long xa = abs(x);
  return Multiply(x,(k1 + Multiply(xa,(k2 + Multiply(xa,(k3 + Multiply(xa,(k4 + Multiply(xa,(k5 + Multiply(xa,(k6 + Multiply(k7,xa)))))))))))));
//return x * (k1 + xa * (k2 + xa * (k3 + xa * (k4 + xa * (k5 + xa * (k6 + k7 * xa))))))
}
 
long P8(long x){
  const long k1 = long(1.0000227186634212561492934945364103 * bf);
  const long k2 = long(-0.00078452280885890775704082177743929688 * bf);
  const long k3 = long(-0.32408930598043657859982318734957029 * bf);
  const long k4 = long(-0.052400836030249085344768278790056773 * bf);
  const long k5 = long(0.36174883733483435391074441160816800 * bf);
  const long k6 = long(-0.27701489145809597317142805726895120 * bf);
  const long k7 = long(0.086538529604234421426630251640041770 * bf);
  const long k8 = long(-0.0086221587401693631050684422148725164 * bf);
  /*Serial.print("P8_k1;");  Serial.print(k1, DEC); Serial.print(";");  Serial.println(double(k1)/bf,30);
  Serial.print("P8_k2;");  Serial.print(k2, DEC); Serial.print(";");  Serial.println(double(k2)/bf,30);
  Serial.print("P8_k3;");  Serial.print(k3, DEC); Serial.print(";");  Serial.println(double(k3)/bf,30);
  Serial.print("P8_k4;");  Serial.print(k4, DEC); Serial.print(";");  Serial.println(double(k4)/bf,30);
  Serial.print("P8_k5;");  Serial.print(k5, DEC); Serial.print(";");  Serial.println(double(k5)/bf,30);
  Serial.print("P8_k6;");  Serial.print(k6, DEC); Serial.print(";");  Serial.println(double(k6)/bf,30);
  Serial.print("P8_k7;");  Serial.print(k7, DEC); Serial.print(";");  Serial.println(double(k7)/bf,30);
  Serial.print("P8_k8;");  Serial.print(k8, DEC); Serial.print(";");  Serial.println(double(k8)/bf,30);*/
  long xa = abs(x);
  return Multiply(x,(k1 + Multiply(xa,(k2 + Multiply(xa,(k3 + Multiply(xa,(k4 + Multiply(xa,(k5 + Multiply(xa,(k6 + Multiply(xa,(k7 + Multiply(k8,xa)))))))))))))));
//return x * (k1 + xa * (k2 + xa * (k3 + xa * (k4 + xa * (k5 + xa * (k6 + xa * (k7 + k8 * xa)))))))
}
 
long P9(long x){
  const long k1 = long(1.0000053559539437176687408358076361 * bf);
  const long k2 = long(-0.00020468780407282606067440041179182 * bf);
  const long k3 = long(-0.33068263893179769015150924739104005 * bf);
  const long k4 = long(-0.016264443217369764218048905826732495 * bf);
  const long k5 = long(0.25249391963414153032875152063187714 * bf);
  const long k6 = long(-0.084994388343297341368432582752049948 * bf);
  const long k7 = long(-0.10882143767159966505736902274606444 * bf);
  const long k8 = long(0.098050019149726774574978713653060964 * bf);
  const long k9 = long(-0.02418357942892264094997752226884160 * bf);
  /*Serial.print("P9_k1;");  Serial.print(k1, DEC); Serial.print(";");  Serial.println(double(k1)/bf,30);
  Serial.print("P9_k2;");  Serial.print(k2, DEC); Serial.print(";");  Serial.println(double(k2)/bf,30);
  Serial.print("P9_k3;");  Serial.print(k3, DEC); Serial.print(";");  Serial.println(double(k3)/bf,30);
  Serial.print("P9_k4;");  Serial.print(k4, DEC); Serial.print(";");  Serial.println(double(k4)/bf,30);
  Serial.print("P9_k5;");  Serial.print(k5, DEC); Serial.print(";");  Serial.println(double(k5)/bf,30);
  Serial.print("P9_k6;");  Serial.print(k6, DEC); Serial.print(";");  Serial.println(double(k6)/bf,30);
  Serial.print("P9_k7;");  Serial.print(k7, DEC); Serial.print(";");  Serial.println(double(k7)/bf,30);
  Serial.print("P9_k8;");  Serial.print(k8, DEC); Serial.print(";");  Serial.println(double(k8)/bf,30);
  Serial.print("P9_k9;");  Serial.print(k9, DEC); Serial.print(";");  Serial.println(double(k9)/bf,30);*/
  long xa = abs(x);
  return Multiply(x,(k1 + Multiply(xa,(k2 + Multiply(xa,(k3 + Multiply(xa,(k4 + Multiply(xa,(k5 + Multiply(xa,(k6 + Multiply(xa,(k7 + Multiply(xa,(k8 + Multiply(k9,xa)))))))))))))))));
//return x * (k1 + xa * (k2 + xa * (k3 + xa * (k4 + xa * (k5 + xa * (k6 + xa * (k7 + xa * (k8 + k9 * xa))))))))
}


long  atan_P2_4(long x){
const long K1[] = {long(1.0083366242390652727700098651261399 * bf),
          long(1.0358733071762243415825112212949779 * bf),
          long(1.0670168023201508743172031364935320 * bf),
          long(1.0755971143576130939891979852247055 * bf)};
const long K2[] = {long(-0.11078014944361409990283694248553670 * bf),
          long(-0.2149300315739419912184216270602979 * bf),
          long(-0.27808224252019023357039291797527924 * bf),
          long(-0.29029079768054708727873800960828195 * bf)};
  /*Serial.print("P2_4_K1[0];");  Serial.print(K1, DEC); Serial.print(";");  Serial.println(double(K1[0])/bf,30);
  Serial.print("P2_4_K1[1];");  Serial.print(K2, DEC); Serial.print(";");  Serial.println(double(K1[1])/bf,30);
  Serial.print("P2_4_K1[2];");  Serial.print(K3, DEC); Serial.print(";");  Serial.println(double(K1[2])/bf,30);
  Serial.print("P2_4_K1[3];");  Serial.print(K4, DEC); Serial.print(";");  Serial.println(double(K1[3])/bf,30);
  Serial.print("P2_4_K2[0];");  Serial.print(K5, DEC); Serial.print(";");  Serial.println(double(K2[0])/bf,30);
  Serial.print("P2_4_K2[1];");  Serial.print(K6, DEC); Serial.print(";");  Serial.println(double(K2[1])/bf,30);
  Serial.print("P2_4_K2[2];");  Serial.print(K7, DEC); Serial.print(";");  Serial.println(double(K2[2])/bf,30);
  Serial.print("P2_4_K2[3];");  Serial.print(K8, DEC); Serial.print(";");  Serial.println(double(K2[3])/bf,30);*/
  long j = long(abs(x)>>(bitf-2));
  long y = Multiply(x,K1[j] + Multiply(K2[j],abs(x)));
  //y = x * (K1[j] + K2[j] * np.fabs(x))
  return y;
}

long  atan_P3_4(long x){
const long K1[] = {long(1.0002880167803320930679331381181339 * bf),
          long(1.0084264526689389026367133442503632 * bf),
          long(1.0401954891948177179593812079875483 * bf),
          long(1.0850394701840971950932122888525131 * bf)};
const long K2[] = {long(-0.006121838089436189909196399756144237 * bf),
          long(-0.064653110965738437430856587088264457 * bf),
          long(-0.19086985499541117593700925117442104 * bf),
          long(-0.31162066371367399467929466944519813 * bf)};
const long K3[] = {long(-0.30174061136598465869347966592859658 * bf),
          long(-0.19548067695815569702438124124586404 * bf),
          long(-0.069511106771492688426680746471645609 * bf),
          long(0.011947243197312155915074454543066357 * bf)};
  long j = long(abs(x)>>(bitf-2));
  //long y = Multiply(x,(K1[j] + Multiply(abs(x),K2[j] + Multiply(K3[j],Multiply(x,x)))));
  long y = Multiply(x,(K1[j] + Multiply(abs(x),K2[j]) + Multiply(K3[j],Multiply(x,x))));
  return y;
}

long  atan_P4_4(long x){
const long K1[] = {long(0.99995638941467053758113796074638816 * bf),
          long(0.99897956919549519709586699637477940 * bf),
          long(1.0053157003120656461349430328284556 * bf),
          long(1.0349432256143936282487151841885385 * bf)};
const long K2[] = {long(0.0017464884521639358448629130269594730 * bf),
          long(0.013825721919340377973814380733592951 * bf),
          long(-0.020999377671891922146334418960222032 * bf),
          long(-0.13846946407697883240781302320276290 * bf)};
const long K3[] = {long(-0.35524161386017821151967017033747423 * bf),
          long(-0.40631265077391591892145116918756660 * bf),
          long(-0.34243857087078470312750935659279513 * bf),
          long(-0.18651117990688840060633041491596000 * bf)};
const long K4[] = {long(0.11026552319700385004520628793801835 * bf),
          long(0.18384515231725048371456898386918861 * bf),
          long(0.14473188810512657119124119714481157 * bf),
          long(0.07543722366963362600905258397976350 * bf)};
  long j = long(abs(x)>>(bitf-2));
  long y =  Multiply(x,(K1[j] +  Multiply(abs(x),K2[j]) +  Multiply(Multiply(x,x), K3[j] +  Multiply(K4[j], abs(x)))));
  return y;
}

long  atan_P5_4(long x){
const long K1[] = {long(0.9999975964759876 * bf),
          long(0.9991572487068143 * bf),
          long(0.9948861737406166 * bf),
          long(0.9991580916067022 * bf)};
const long K2[] = {long(0.00013028819536007726 * bf),
          long(0.01180426099487469 * bf),
          long(0.046744232087946556 * bf),
          long(0.026450162455216635 * bf)};
const long K3[] = {long(-0.3355854876429768 * bf),
          long(-0.3978558818016045 * bf),
          long(-0.5063109720988022 * bf),
          long(-0.4705449092935895 * bf)}; 
const long K4[] = {long(0.016201080063245343 * bf),
          long(0.1684185810224557 * bf),
          long(0.31972484365845205 * bf),
          long(0.29210508279189074 * bf)};
const long K5[] = {long(0.15500543751429005 * bf),
          long(0.01036229101348984 * bf),
          long(-0.06961567792059027 * bf),
          long(-0.061770299160417534 * bf)};
  long j = long(abs(x)>>(bitf-2));
  long y = Multiply(x,(K1[j] + Multiply(abs(x),K2[j]) + Multiply(Multiply(x,x), K3[j] + Multiply(K4[j],abs(x)) + Multiply(K5[j],Multiply(x,x)))));

  //  y = x * (k1[j] + np.fabs(x) * k2[j] + k3[j] * x * x + k4[j] * x * x * np.fabs(x) + k5[j] * x * x * x * x)
  return y;
}

long  atan_P2_8(long x){
const long K1[] = {long(1.0022020982721834 * bf),
          long(1.0110060309227178 * bf),
          long(1.0272377858060056 * bf),
          long(1.04565293289239 * bf),
          long(1.061830421010721 * bf),
          long(1.0727212261456524 * bf),
          long(1.0769168930483971 * bf),
          long(1.0742737699176216 * bf)};
const long K2[] = {long(-0.05733310996133802 * bf),
          long(-0.12271115275172279 * bf),
          long(-0.1870427658501457 * bf),
          long(-0.23615705491487867 * bf),
          long(-0.26863712912770703 * bf),
          long(-0.28618682076209224 * bf),
          long(-0.29187379767105756 * bf),
          long(-0.28892184517921662 * bf)};
  long j = long(abs(x)>>(bitf-3));
  long y = Multiply(x,(K1[j] + Multiply(K2[j],abs(x))));
  //  y = x * (k1[j] + k2[j] * np.fabs(x))=
  return y;
}

long  atan_P2_16(long x){
const long K1[] = {long(1.0022020982721834 * bf),
    long(1.0029046388485984 * bf),
    long(1.0077818149369457 * bf),
    long(1.0146233846757446 * bf),
    long(1.0228934497235388 * bf),
    long(1.0319935399208884 * bf),
    long(1.0413164218631783 * bf),
    long(1.0502974938837690 * bf),
    long(1.0584523335150643 * bf),
    long(1.0653981113453207 * bf),
    long(1.0708602566729138 * bf),
    long(1.0746677037011018 * bf),
    long(1.0767406756823790 * bf),
    long(1.0770739125792823 * bf),
    long(1.0757220663454407 * bf),
    long(1.0727794884608447 * bf)};
const long K2[] = {long(-0.05733310996133802 * bf),
    long(-0.06360365885724302 * bf),
    long(-0.10206248881283969 * bf),
    long(-0.13835879903322141 * bf),
    long(-0.17136740578457378 * bf),
    long(-0.20046648667821867 * bf),
    long(-0.22532933001124547 * bf),
    long(-0.24586966979100597 * bf),
    long(-0.26219549417050241 * bf),
    long(-0.27456036279589475 * bf),
    long(-0.28331562972227497 * bf),
    long(-0.28886782689946334 * bf),
    long(-0.29164386456253436 * bf),
    long(-0.29206447207659822 * bf),
    long(-0.29052775994279864 * bf),
    long(-0.28739580361124232 * bf)};
  long j = long(abs(x)>>(bitf-4));
  long y = Multiply(x,(K1[j] + Multiply(K2[j],abs(x))));
  //  y = x * (k1[j] + k2[j] * np.fabs(x))
  return y;
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
  double sum_time_P4 = 0;
  double sum_time_P5 = 0;
  double sum_time_P6 = 0;
  double sum_time_P7 = 0;
  double sum_time_P8 = 0;
  double sum_time_P9 = 0;

  double sum_time_P2_4 = 0;
  double sum_time_P3_4 = 0;
  double sum_time_P4_4 = 0;
  double sum_time_P5_4 = 0;
  double sum_time_P2_8 = 0;
  double sum_time_P2_16 = 0;

  double mean_time_satan = 0;
  double mean_time_P4 = 0;
  double mean_time_P5 = 0;
  double mean_time_P6 = 0;
  double mean_time_P7 = 0;
  double mean_time_P8 = 0;
  double mean_time_P9 = 0;

  double mean_time_P2_4 = 0;
  double mean_time_P3_4 = 0;
  double mean_time_P4_4 = 0;
  double mean_time_P5_4 = 0;
  double mean_time_P2_8 = 0;
  double mean_time_P2_16 = 0;

  double sum_time_satan2 = 0;
  double mean_time_satan2 = 0;

  double satan = 0;
  long aP4 = 0;
  long aP5 = 0;
  long aP6 = 0;
  long aP7 = 0;
  long aP8 = 0;
  long aP9 = 0;

  long aP2_4 = 0;
  long aP3_4 = 0;
  long aP4_4 = 0;
  long aP5_4 = 0;
  long aP2_8 = 0;
  long aP2_16 = 0;

  float step = 0.00001f;  //(0.00001f); //ok 200k Sampli
  float currentValue = -1.0f + step;
  float maxValue = 1.0f;

  long x;

  Serial.print("step:     ");  Serial.println(step, 10);
  Serial.print("minValue: ");  Serial.println(currentValue, 10);
  Serial.print("maxValue: ");  Serial.println(maxValue - step, 10);

  //noInterrupts();

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
    aP4 = P4(x);
    sum_n=sum_n+aP4;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_P4 = finish-start;} else {sum_time_P4=111111;}

  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    aP5 = P5(x);
    sum_n=sum_n+aP5;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_P5 = finish-start;} else {sum_time_P5=111111;}

  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    aP6 = P6(x);
    sum_n=sum_n+aP6;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_P6 = finish-start;} else {sum_time_P6=111111;}

  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    aP7 = P7(x);
    sum_n=sum_n+aP7;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_P7 = finish-start;} else {sum_time_P7=111111;}
    
  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    aP8 = P8(x);
    sum_n=sum_n+aP8;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_P8 = finish-start;} else {sum_time_P8=111111;}

  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    aP9 = P9(x);
    sum_n=sum_n+aP9;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_P9 = finish-start;} else {sum_time_P9=111111;}
    
  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    aP2_4 = atan_P2_4(x);
    sum_n=sum_n+aP2_4;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_P2_4 = finish-start;} else {sum_time_P2_4=111111;}

  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    aP3_4 = atan_P3_4(x);
    sum_n=sum_n+aP3_4;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_P3_4 = finish-start;} else {sum_time_P3_4=111111;}

  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    aP4_4 = atan_P4_4(x);
    sum_n=sum_n+aP4_4;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_P4_4 = finish-start;} else {sum_time_P4_4=111111;}

  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    aP5_4 = atan_P5_4(x);
    sum_n=sum_n+aP5_4;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_P5_4 = finish-start;} else {sum_time_P5_4=111111;}
    
  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    aP2_8 = atan_P2_8(x);
    sum_n=sum_n+aP2_8;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_P2_8 = finish-start;} else {sum_time_P2_8=111111;}
    
  currentValue = -1.0f + step;  i = 1;
  start = TC0->TC_CHANNEL[0].TC_CV;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);    currentValue = currentValue + step;
    aP2_16 = atan_P2_16(x);
    sum_n=sum_n+aP2_16;
  }
  finish = TC0->TC_CHANNEL[0].TC_CV;  if (finish>start) {sum_time_P2_16 = finish-start;} else {sum_time_P2_16=111111;}

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
  mean_time_P4 = (sum_time_P4*2) / double(i);
  mean_time_P5 = (sum_time_P5*2) / double(i);
  mean_time_P6 = (sum_time_P6*2) / double(i);
  mean_time_P7 = (sum_time_P7*2) / double(i);
  mean_time_P8 = (sum_time_P8*2) / double(i);
  mean_time_P9 = (sum_time_P9*2) / double(i);

  mean_time_P2_4 = (sum_time_P2_4*2) / double(i);
  mean_time_P3_4 = (sum_time_P3_4*2) / double(i);
  mean_time_P4_4 = (sum_time_P4_4*2) / double(i);
  mean_time_P5_4 = (sum_time_P5_4*2) / double(i);
  mean_time_P2_8 = (sum_time_P2_8*2) / double(i);
  mean_time_P2_16 = (sum_time_P2_16*2) / double(i);
  mean_time_satan2 = (sum_time_satan2*2) / double(i);

  Serial.print("sum_n = ");  Serial.println(sum_n);
  Serial.print("sum_d = ");  Serial.println(sum_d);

  Serial.print("cycles = i = ");  Serial.println(i);
  Serial.print("mean_time_satan = ");  Serial.println(mean_time_satan, 5);
  Serial.print("mean_time_P4    = ");  Serial.println(mean_time_P4, 5);
  Serial.print("mean_time_P5    = ");  Serial.println(mean_time_P5, 5);
  Serial.print("mean_time_P6    = ");  Serial.println(mean_time_P6, 5);
  Serial.print("mean_time_P7    = ");  Serial.println(mean_time_P7, 5);
  Serial.print("mean_time_P8    = ");  Serial.println(mean_time_P8, 5);
  Serial.print("mean_time_P9    = ");  Serial.println(mean_time_P9, 5);

  Serial.print("mean_time_P2_4  = ");  Serial.println(mean_time_P2_4, 5);
  Serial.print("mean_time_P3_4  = ");  Serial.println(mean_time_P3_4, 5);
  Serial.print("mean_time_P4_4  = ");  Serial.println(mean_time_P4_4, 5);
  Serial.print("mean_time_P5_4  = ");  Serial.println(mean_time_P5_4, 5);
  Serial.print("mean_time_P2_8  = ");  Serial.println(mean_time_P2_8, 5);
  Serial.print("mean_time_P2_16 = ");  Serial.println(mean_time_P2_16, 5);
  Serial.print("mean_time_satan2= ");  Serial.println(mean_time_satan2, 5);
  Serial.println("");
  Serial.print("sum_time_satan = ");  Serial.println(sum_time_satan, 5);
  Serial.print("sum_time_P4    = ");  Serial.println(sum_time_P4, 5);
  Serial.print("sum_time_P5    = ");  Serial.println(sum_time_P5, 5);
  Serial.print("sum_time_P6    = ");  Serial.println(sum_time_P6, 5);
  Serial.print("sum_time_P7    = ");  Serial.println(sum_time_P7, 5);
  Serial.print("sum_time_P8    = ");  Serial.println(sum_time_P8, 5);
  Serial.print("sum_time_P9    = ");  Serial.println(sum_time_P9, 5);

  Serial.print("sum_time_P2_4  = ");  Serial.println(sum_time_P2_4, 5);
  Serial.print("sum_time_P3_4  = ");  Serial.println(sum_time_P3_4, 5);
  Serial.print("sum_time_P4_4  = ");  Serial.println(sum_time_P4_4, 5);
  Serial.print("sum_time_P5_4  = ");  Serial.println(sum_time_P5_4, 5);
  Serial.print("sum_time_P2_8  = ");  Serial.println(sum_time_P2_8, 5);
  Serial.print("sum_time_P2_16 = ");  Serial.println(sum_time_P2_16, 5);
  Serial.print("sum_time_satan2= ");  Serial.println(sum_time_satan2, 5);
}

void loop() {
}
