
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


double p4_err(long x) {
  return double(P4(x)) / bf - x_atanbf;
}

double p5_err(long x) {
  return double(P5(x)) / bf - x_atanbf;
}

double p6_err(long x) {
  return double(P6(x)) / bf - x_atanbf;
}

double p7_err(long x) {
  return double(P7(x)) / bf - x_atanbf;
}

double p8_err(long x) {
  return double(P8(x)) / bf - x_atanbf;
}

double p9_err(long x) {
  return double(P9(x)) / bf - x_atanbf;
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

double p2_4_err(long x) {
  return double(atan_P2_4(x)) / bf - x_atanbf;
}

double p3_4_err(long x) {
  return double(atan_P3_4(x)) / bf - x_atanbf;
}

double p4_4_err(long x) {
  return double(atan_P4_4(x)) / bf - x_atanbf;
}

double p5_4_err(long x) {
  return double(atan_P5_4(x)) / bf - x_atanbf;
}

double p2_8_err(long x) {
  return double(atan_P2_8(x)) / bf - x_atanbf;
}

double p2_16_err(long x) {
  return double(atan_P2_16(x)) / bf - x_atanbf;
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

  double error_p4 = 0;
  double error_p5 = 0;
  double error_p6 = 0;
  double error_p7 = 0;
  double error_p8 = 0;
  double error_p9 = 0;

  double max_error_p4 = 0;
  double max_error_p5 = 0;
  double max_error_p6 = 0;
  double max_error_p7 = 0;
  double max_error_p8 = 0;
  double max_error_p9 = 0;

  double max_error_p44x = 0;
  double max_error_p54x = 0;
  double max_error_p64x = 0;
  double max_error_p74x = 0;
  double max_error_p84x = 0;
  double max_error_p94x = 0;

  double min_error_p4 = 0;
  double min_error_p5 = 0;
  double min_error_p6 = 0;
  double min_error_p7 = 0;
  double min_error_p8 = 0;
  double min_error_p9 = 0;

  double min_error_p44x = 0;
  double min_error_p54x = 0;
  double min_error_p64x = 0;
  double min_error_p74x = 0;
  double min_error_p84x = 0;
  double min_error_p94x = 0;

  double mean_error_p4 = 0;
  double mean_error_p5 = 0;
  double mean_error_p6 = 0;
  double mean_error_p7 = 0;
  double mean_error_p8 = 0;
  double mean_error_p9 = 0;


  double error_p2_4 = 0;
  double error_p3_4 = 0;
  double error_p4_4 = 0;
  double error_p5_4 = 0;
  double error_p2_8 = 0;
  double error_p2_16 = 0;

  double max_error_p2_4 = 0;
  double max_error_p3_4 = 0;
  double max_error_p4_4 = 0;
  double max_error_p5_4 = 0;
  double max_error_p2_8 = 0;
  double max_error_p2_16 = 0;

  double max_error_p2_44x = 0;
  double max_error_p3_44x = 0;
  double max_error_p4_44x = 0;
  double max_error_p5_44x = 0;
  double max_error_p2_84x = 0;
  double max_error_p2_164x = 0;

  double min_error_p2_4 = 0;
  double min_error_p3_4 = 0;
  double min_error_p4_4 = 0;
  double min_error_p5_4 = 0;
  double min_error_p2_8 = 0;
  double min_error_p2_16 = 0;

  double min_error_p2_44x = 0;
  double min_error_p3_44x = 0;
  double min_error_p4_44x = 0;
  double min_error_p5_44x = 0;
  double min_error_p2_84x = 0;
  double min_error_p2_164x = 0;

  double mean_error_p2_4 = 0;
  double mean_error_p3_4 = 0;
  double mean_error_p4_4 = 0;
  double mean_error_p5_4 = 0;
  double mean_error_p2_8 = 0;
  double mean_error_p2_16 = 0;

  float step = 0.00001f;  //do zgrywaia pliku (0.00001f); //ok 200k Sampli
  float currentValue = -1.0f + step;
  float maxValue = 1.0f;
  //long step = 32*32;  //32 to 8 388 608
  //long currentValue = -134217728 + step;
  //long maxValue = 134217728;

  long x;

  double count = 0;
  double count1M = 0;
  
  Serial.print("bitf:     ");  Serial.println(bitf,DEC);
  Serial.print("step:     ");  Serial.println(step, 10);
  Serial.print("minValue: ");  Serial.println(currentValue, 10);
  Serial.print("maxValue: ");  Serial.println(maxValue - step, 10);

  /*
  //wydruk do konsoli dla CSV!!!
  Serial.print("x"); Serial.print(";");
  Serial.print("x"); Serial.print(";");
  Serial.print("P4"); Serial.print(";");
  Serial.print("P5"); Serial.print(";");
  Serial.print("P6"); Serial.print(";");
  Serial.print("P7"); Serial.print(";");
  Serial.print("P8"); Serial.print(";");
  Serial.print("P9"); Serial.print(";");
  Serial.print("P2_4"); Serial.print(";");
  Serial.print("P3_4"); Serial.print(";");
  Serial.print("P4_4"); Serial.print(";");
  Serial.print("P5_4"); Serial.print(";");
  Serial.print("P2_8"); Serial.print(";");
  Serial.print("P2_16"); Serial.print(";");
  Serial.print("satan");
  Serial.println("");
  */

  long i = 1;
  for (i = 1; currentValue < maxValue; i++) {
    x = long(currentValue * bf);  //0.7f*bf;//
    //x= 939522112;
    //Serial.print("   x="); Serial.println(x,HEX);
    x_atanbf = atan(double(x) / bf);
    error_p4 = p4_err(x);
    error_p5 = p5_err(x);
    error_p6 = p6_err(x);
    error_p7 = p7_err(x);
    error_p8 = p8_err(x);
    error_p9 = p9_err(x);

    error_p2_4 = p2_4_err(x);
    error_p3_4 = p3_4_err(x);
    error_p4_4 = p4_4_err(x);
    error_p5_4 = p5_4_err(x);
    error_p2_8 = p2_8_err(x);
    error_p2_16 = p2_16_err(x);

    if (max_error_p4 < error_p4) {      max_error_p4 = error_p4;      max_error_p44x = x;    }
    if (max_error_p5 < error_p5) {      max_error_p5 = error_p5;      max_error_p54x = x;    }
    if (max_error_p6 < error_p6) {      max_error_p6 = error_p6;      max_error_p64x = x;    }
    if (max_error_p7 < error_p7) {      max_error_p7 = error_p7;      max_error_p74x = x;    }
    if (max_error_p8 < error_p8) {      max_error_p8 = error_p8;      max_error_p84x = x;    }
    if (max_error_p9 < error_p9) {      max_error_p9 = error_p9;      max_error_p94x = x;    }

    if (max_error_p2_4 < error_p2_4) {      max_error_p2_4 = error_p2_4;      max_error_p2_44x = x;    }
    if (max_error_p3_4 < error_p3_4) {      max_error_p3_4 = error_p3_4;      max_error_p3_44x = x;    }
    if (max_error_p4_4 < error_p4_4) {      max_error_p4_4 = error_p4_4;      max_error_p4_44x = x;    }
    if (max_error_p5_4 < error_p5_4) {      max_error_p5_4 = error_p5_4;      max_error_p5_44x = x;    }
    if (max_error_p2_8 < error_p2_8) {      max_error_p2_8 = error_p2_8;      max_error_p2_84x = x;    }
    if (max_error_p2_16 < error_p2_16) {    max_error_p2_16 = error_p2_16;     max_error_p2_164x = x;   }

    if (min_error_p4 > error_p4) {      min_error_p4 = error_p4;      min_error_p44x = x;    }
    if (min_error_p5 > error_p5) {      min_error_p5 = error_p5;      min_error_p54x = x;    }
    if (min_error_p6 > error_p6) {      min_error_p6 = error_p6;      min_error_p64x = x;    }
    if (min_error_p7 > error_p7) {      min_error_p7 = error_p7;      min_error_p74x = x;    }
    if (min_error_p8 > error_p8) {      min_error_p8 = error_p8;      min_error_p84x = x;    }
    if (min_error_p9 > error_p9) {      min_error_p9 = error_p9;      min_error_p94x = x;    }

    if (min_error_p2_4 > error_p2_4) {      min_error_p2_4 = error_p2_4;      min_error_p2_44x = x;    }
    if (min_error_p3_4 > error_p3_4) {      min_error_p3_4 = error_p3_4;      min_error_p3_44x = x;    }
    if (min_error_p4_4 > error_p4_4) {      min_error_p4_4 = error_p4_4;      min_error_p4_44x = x;    }
    if (min_error_p5_4 > error_p5_4) {      min_error_p5_4 = error_p5_4;      min_error_p5_44x = x;    }
    if (min_error_p2_8 > error_p2_8) {      min_error_p2_8 = error_p2_8;      min_error_p2_84x = x;    }
    if (min_error_p2_16 > error_p2_16) {    min_error_p2_16 = error_p2_16;     min_error_p2_164x = x;   }

    if (i == 1) {
      mean_error_p4 = abs(error_p4);
      mean_error_p5 = abs(error_p5);
      mean_error_p6 = abs(error_p6);
      mean_error_p7 = abs(error_p7);
      mean_error_p8 = abs(error_p8);
      mean_error_p9 = abs(error_p9);

      mean_error_p2_4 = abs(error_p2_4);
      mean_error_p3_4 = abs(error_p3_4);
      mean_error_p4_4 = abs(error_p4_4);
      mean_error_p5_4 = abs(error_p5_4);
      mean_error_p2_8 = abs(error_p2_8);
      mean_error_p2_16 = abs(error_p2_16);
    } else {
      mean_error_p4 = (mean_error_p4 + abs(error_p4));
      mean_error_p5 = (mean_error_p5 + abs(error_p5));
      mean_error_p6 = (mean_error_p6 + abs(error_p6));
      mean_error_p7 = (mean_error_p7 + abs(error_p7));
      mean_error_p8 = (mean_error_p8 + abs(error_p8));
      mean_error_p9 = (mean_error_p9 + abs(error_p9));
      
      mean_error_p2_4 = (mean_error_p2_4 + abs(error_p2_4));
      mean_error_p3_4 = (mean_error_p3_4 + abs(error_p3_4));
      mean_error_p4_4 = (mean_error_p4_4 + abs(error_p4_4));
      mean_error_p5_4 = (mean_error_p5_4 + abs(error_p5_4));
      mean_error_p2_8 = (mean_error_p2_8 + abs(error_p2_8));
      mean_error_p2_16= (mean_error_p2_16 + abs(error_p2_16));
    }
    


    currentValue = currentValue + step;

    count++;
    if (count == 100000) {      count = 0;      count1M++;      Serial.print("100k SAMPLI: x");      Serial.println(count1M);    }


    /*
    //wydruk do konsoli dla CSV!!!
    double satan = atan(double(x)/bf);
    long P4_our = P4(x);
    long P5_our = P5(x);
    long P6_our = P6(x);
    long P7_our = P7(x);
    long P8_our = P8(x);
    long P9_our = P9(x);
    long P2_4_our = atan_P2_4(x);
    long P3_4_our = atan_P3_4(x);
    long P4_4_our = atan_P4_4(x);
    long P5_4_our = atan_P5_4(x);
    long P2_8_our = atan_P2_8(x);
    long P2_16_our = atan_P2_16(x);

    //wydruk do konsoli dla CSV!!!
    Serial.print(x,DEC); Serial.print(";");
    Serial.print(x,HEX); Serial.print(";");
    Serial.print(P4_our,DEC); Serial.print(";");
    Serial.print(P5_our,DEC); Serial.print(";");
    Serial.print(P6_our,DEC); Serial.print(";");
    Serial.print(P7_our,DEC); Serial.print(";");
    Serial.print(P8_our,DEC); Serial.print(";");
    Serial.print(P9_our,DEC); Serial.print(";");
    Serial.print(P2_4_our,DEC); Serial.print(";");
    Serial.print(P3_4_our,DEC); Serial.print(";");
    Serial.print(P4_4_our,DEC); Serial.print(";");
    Serial.print(P5_4_our,DEC); Serial.print(";");
    Serial.print(P2_8_our,DEC); Serial.print(";");
    Serial.print(P2_16_our,DEC); Serial.print(";");
    Serial.print(satan,40);
    Serial.println("");
    */
  }
  i = i - 1;  //odlicza o jeden cykl więcej niż wykonano

  // Przeliczanie wyników na stopnie
  double dmaxGr_p4 = max_error_p4 * 180.0 / PI;
  double dmaxGr_p5 = max_error_p5 * 180.0 / PI;
  double dmaxGr_p6 = max_error_p6 * 180.0 / PI;
  double dmaxGr_p7 = max_error_p7 * 180.0 / PI;
  double dmaxGr_p8 = max_error_p8 * 180.0 / PI;
  double dmaxGr_p9 = max_error_p9 * 180.0 / PI;

  double dmaxGr_p2_4 = max_error_p2_4 * 180.0 / PI;
  double dmaxGr_p3_4 = max_error_p3_4 * 180.0 / PI;
  double dmaxGr_p4_4 = max_error_p4_4 * 180.0 / PI;
  double dmaxGr_p5_4 = max_error_p5_4 * 180.0 / PI;
  double dmaxGr_p2_8 = max_error_p2_8 * 180.0 / PI;
  double dmaxGr_p2_16 = max_error_p2_16 * 180.0 / PI;

  double dminGr_p4 = min_error_p4 * 180.0 / PI;
  double dminGr_p5 = min_error_p5 * 180.0 / PI;
  double dminGr_p6 = min_error_p6 * 180.0 / PI;
  double dminGr_p7 = min_error_p7 * 180.0 / PI;
  double dminGr_p8 = min_error_p8 * 180.0 / PI;
  double dminGr_p9 = min_error_p9 * 180.0 / PI;

  double dminGr_p2_4 = min_error_p2_4 * 180.0 / PI;
  double dminGr_p3_4 = min_error_p3_4 * 180.0 / PI;
  double dminGr_p4_4 = min_error_p4_4 * 180.0 / PI;
  double dminGr_p5_4 = min_error_p5_4 * 180.0 / PI;
  double dminGr_p2_8 = min_error_p2_8 * 180.0 / PI;
  double dminGr_p2_16 = min_error_p2_16 * 180.0 / PI;

  mean_error_p4 = (mean_error_p4/i) * 180.0 / PI;
  mean_error_p5 = (mean_error_p5/i) * 180.0 / PI;
  mean_error_p6 = (mean_error_p6/i) * 180.0 / PI;
  mean_error_p7 = (mean_error_p7/i) * 180.0 / PI;
  mean_error_p8 = (mean_error_p8/i) * 180.0 / PI;
  mean_error_p9 = (mean_error_p9/i) * 180.0 / PI;
  
  mean_error_p2_4 = (mean_error_p2_4/i) * 180.0 / PI;
  mean_error_p3_4 = (mean_error_p3_4/i) * 180.0 / PI;
  mean_error_p4_4 = (mean_error_p4_4/i) * 180.0 / PI;
  mean_error_p5_4 = (mean_error_p5_4/i) * 180.0 / PI;
  mean_error_p2_8 = (mean_error_p2_8/i) * 180.0 / PI;
  mean_error_p2_16 = (mean_error_p2_16/i) * 180.0 / PI;

  Serial.print("cycles = i = ");  Serial.println(i);
  Serial.println("");
  Serial.println("OUR ALGORITHMS:");
  Serial.print("For P4 errors (in degrees); max: ");  Serial.print(dmaxGr_p4, 15);  Serial.print("   for x: ");  Serial.print(max_error_p44x, 15);  Serial.print(";    min: ");  Serial.print(dminGr_p4, 15);  Serial.print("   for x: ");  Serial.println(min_error_p44x, 15);
  Serial.print("For P5 errors (in degrees); max: ");  Serial.print(dmaxGr_p5, 15);  Serial.print("   for x: ");  Serial.print(max_error_p54x, 15);  Serial.print(";    min: ");  Serial.print(dminGr_p5, 15);  Serial.print("   for x: ");  Serial.println(min_error_p54x, 15);
  Serial.print("For P6 errors (in degrees); max: ");  Serial.print(dmaxGr_p6, 15);  Serial.print("   for x: ");  Serial.print(max_error_p64x, 15);  Serial.print(";    min: ");  Serial.print(dminGr_p6, 15);  Serial.print("   for x: ");  Serial.println(min_error_p64x, 15);
  Serial.print("For P7 errors (in degrees); max: ");  Serial.print(dmaxGr_p7, 15);  Serial.print("   for x: ");  Serial.print(max_error_p74x, 15);  Serial.print(";    min: ");  Serial.print(dminGr_p7, 15);  Serial.print("   for x: ");  Serial.println(min_error_p74x, 15);
  Serial.print("For P8 errors (in degrees); max: ");  Serial.print(dmaxGr_p8, 15);  Serial.print("   for x: ");  Serial.print(max_error_p84x, 15);  Serial.print(";    min: ");  Serial.print(dminGr_p8, 15);  Serial.print("   for x: ");  Serial.println(min_error_p84x, 15);
  Serial.print("For P9 errors (in degrees); max: ");  Serial.print(dmaxGr_p9, 15);  Serial.print("   for x: ");  Serial.print(max_error_p94x, 15);  Serial.print(";    min: ");  Serial.print(dminGr_p9, 15);  Serial.print("   for x: ");  Serial.println(min_error_p94x, 15);
  
  Serial.print("For P2_4 errors (in degrees); max: ");  Serial.print(dmaxGr_p2_4, 15);  Serial.print("   for x: ");  Serial.print(max_error_p2_44x, 15);  Serial.print(";    min: ");  Serial.print(dminGr_p2_4, 15);  Serial.print("   for x: ");  Serial.println(min_error_p2_44x, 15);
  Serial.print("For P3_4 errors (in degrees); max: ");  Serial.print(dmaxGr_p3_4, 15);  Serial.print("   for x: ");  Serial.print(max_error_p3_44x, 15);  Serial.print(";    min: ");  Serial.print(dminGr_p3_4, 15);  Serial.print("   for x: ");  Serial.println(min_error_p3_44x, 15);
  Serial.print("For P4_4 errors (in degrees); max: ");  Serial.print(dmaxGr_p4_4, 15);  Serial.print("   for x: ");  Serial.print(max_error_p4_44x, 15);  Serial.print(";    min: ");  Serial.print(dminGr_p4_4, 15);  Serial.print("   for x: ");  Serial.println(min_error_p4_44x, 15);
  Serial.print("For P5_4 errors (in degrees); max: ");  Serial.print(dmaxGr_p5_4, 15);  Serial.print("   for x: ");  Serial.print(max_error_p5_44x, 15);  Serial.print(";    min: ");  Serial.print(dminGr_p5_4, 15);  Serial.print("   for x: ");  Serial.println(min_error_p5_44x, 15);
  Serial.print("For P2_8 errors (in degrees); max: ");  Serial.print(dmaxGr_p2_8, 15);  Serial.print("   for x: ");  Serial.print(max_error_p2_84x, 15);  Serial.print(";    min: ");  Serial.print(dminGr_p2_8, 15);  Serial.print("   for x: ");  Serial.println(min_error_p2_84x, 15);
  Serial.print("For P2_16 errors(in degrees); max: ");  Serial.print(dmaxGr_p2_16,15); Serial.print("   for x: ");  Serial.print(max_error_p2_164x, 15);  Serial.print(";    min: ");  Serial.print(dminGr_p2_16,15);  Serial.print("   for x: ");  Serial.println(min_error_p2_164x,15);

/*
  Serial.print("Minimum error for P4 (in degrees): ");  Serial.print(dminGr_p4, 15);  Serial.print("   for x: ");  Serial.println(min_error_p44x, 15);
  Serial.print("Minimum error for P5 (in degrees): ");  Serial.print(dminGr_p5, 15);  Serial.print("   for x: ");  Serial.println(min_error_p54x, 15);
  Serial.print("Minimum error for P6 (in degrees): ");  Serial.print(dminGr_p6, 15);  Serial.print("   for x: ");  Serial.println(min_error_p64x, 15);
  Serial.print("Minimum error for P7 (in degrees): ");  Serial.print(dminGr_p7, 15);  Serial.print("   for x: ");  Serial.println(min_error_p74x, 15);
  Serial.print("Minimum error for P8 (in degrees): ");  Serial.print(dminGr_p8, 15);  Serial.print("   for x: ");  Serial.println(min_error_p84x, 15);
  Serial.print("Minimum error for P9 (in degrees): ");  Serial.print(dminGr_p9, 15);  Serial.print("   for x: ");  Serial.println(min_error_p94x, 15);
  
  Serial.print("Minimum error for P2_4 (in degrees): ");  Serial.print(dminGr_p2_4, 15);  Serial.print("   for x: ");  Serial.println(min_error_p2_44x, 15);
  Serial.print("Minimum error for P3_4 (in degrees): ");  Serial.print(dminGr_p3_4, 15);  Serial.print("   for x: ");  Serial.println(min_error_p3_44x, 15);
  Serial.print("Minimum error for P4_4 (in degrees): ");  Serial.print(dminGr_p4_4, 15);  Serial.print("   for x: ");  Serial.println(min_error_p4_44x, 15);
  Serial.print("Minimum error for P5_4 (in degrees): ");  Serial.print(dminGr_p5_4, 15);  Serial.print("   for x: ");  Serial.println(min_error_p5_44x, 15);
  Serial.print("Minimum error for P2_8 (in degrees): ");  Serial.print(dminGr_p2_8, 15);  Serial.print("   for x: ");  Serial.println(min_error_p2_84x, 15);
  Serial.print("Minimum error for P2_16 (in degrees):");  Serial.print(dminGr_p2_16, 15); Serial.print("   for x: ");  Serial.println(min_error_p2_164x, 15);
*/
  Serial.println("");

  Serial.println("OUR ALGORITHMS:");
  Serial.print("Mean error for P4 (in degrees): ");  Serial.println(mean_error_p4, 20);
  Serial.print("Mean error for P5 (in degrees): ");  Serial.println(mean_error_p5, 20);
  Serial.print("Mean error for P6 (in degrees): ");  Serial.println(mean_error_p6, 20);
  Serial.print("Mean error for P7 (in degrees): ");  Serial.println(mean_error_p7, 20);
  Serial.print("Mean error for P8 (in degrees): ");  Serial.println(mean_error_p8, 20);
  Serial.print("Mean error for P9 (in degrees): ");  Serial.println(mean_error_p9, 20);
  
  Serial.print("Mean error for P2_4 (in degrees): ");  Serial.println(mean_error_p2_4, 20);
  Serial.print("Mean error for P3_4 (in degrees): ");  Serial.println(mean_error_p3_4, 20);
  Serial.print("Mean error for P4_4 (in degrees): ");  Serial.println(mean_error_p4_4, 20);
  Serial.print("Mean error for P5_4 (in degrees): ");  Serial.println(mean_error_p5_4, 20);
  Serial.print("Mean error for P2_8 (in degrees): ");  Serial.println(mean_error_p2_8, 20);
  Serial.print("Mean error for P2_16 (in degrees):");  Serial.println(mean_error_p2_16, 20);
  Serial.println("END");
  Serial.println("");

}

void loop() {
}
