
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


long P4(long x){
  const long k1 = long(1.0025034607882041432070217945691461 * bf);
  const long k2 = long(-0.013679575696677310464002349120340933 * bf);
  const long k3 = long(-0.34402713551558530645075676095404599 * bf);
  const long k4 = long(0.14071654365142265977615479831981054 * bf);
  long xa = abs(x);
  return Multiply(x,(k1 + Multiply(xa,(k2 + Multiply(xa,(k3 + Multiply(k4,xa)))))));
}

long P5(long x){
  const long k1 = long(0.99872459843609849477918094400681791 * bf);
  const long k2 = long(0.020835029941766873180965040229539301 * bf);
  const long k3 = long(-0.44437860098439551704663289431391845 * bf);
  const long k4 = long(0.25712163230498072978472105582432498 * bf);
  const long k5 = long(-0.046880178811481034204063201159136027 * bf);
  long xa = abs(x);
  return Multiply(x,(k1 + Multiply(xa,(k2 + Multiply(xa,(k3 + Multiply(xa,(k4 + Multiply(k5,xa)))))))));
}

long P6(long x){
  const long k1 = long(0.99957274398868036466175439328131168 * bf);
  const long k2 = long(0.0081073805979023528501915581481079948 * bf);
  const long k3 = long(-0.38306246882783360559402899745151711 * bf);
  const long k4 = long(0.12932770870236211115108872301602014 * bf);
  const long k5 = long(0.073227807065460482958962366420611951 * bf);
  const long k6 = long(-0.041782005205202704002747072607342900 * bf);
  long xa = abs(x);
  return Multiply(x,(k1 + Multiply(xa,(k2 + Multiply(xa,(k3 + Multiply(xa,(k4 + Multiply(xa,(k5 + Multiply(k6,xa)))))))))));
}
 
long P7(long x){
  const long k1 = long(0.999986014690233669198646555331259321605492795 * bf);
  const long k2 = long(0.0000267112350723644112343661799756864018838072241 * bf);
  const long k3 = long(-0.330449690192830935748683860800897337070635922 * bf);
  const long k4 = long(-0.0281155086387117101531648219939944994865491542 * bf);
  const long k5 = long(0.311316333734556780927317449915075557725828681 * bf);
  const long k6 = long(-0.218804577133295874357838200079088802949306408 * bf);
  const long k7 = long(0.0514392966229627485943918792179289871543520712 * bf);
  long xa = abs(x);
  return Multiply(x,(k1 + Multiply(xa,(k2 + Multiply(xa,(k3 + Multiply(xa,(k4 + Multiply(xa,(k5 + Multiply(xa,(k6 + Multiply(k7,xa)))))))))))));
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
  long xa = abs(x);
  return Multiply(x,(k1 + Multiply(xa,(k2 + Multiply(xa,(k3 + Multiply(xa,(k4 + Multiply(xa,(k5 + Multiply(xa,(k6 + Multiply(xa,(k7 + Multiply(k8,xa)))))))))))))));
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
  long xa = abs(x);
  return Multiply(x,(k1 + Multiply(xa,(k2 + Multiply(xa,(k3 + Multiply(xa,(k4 + Multiply(xa,(k5 + Multiply(xa,(k6 + Multiply(xa,(k7 + Multiply(xa,(k8 + Multiply(k9,xa)))))))))))))))));
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
  long j = long(abs(x)>>(bitf-2));
  long y = Multiply(x,(K1[j] + Multiply(K2[j],abs(x))));
  return y;
}

long  atan_P3_4(long x){
const long K1[] = {long(1.0002880167803320930679331381181339 * bf),
          long(1.0084264526689389026367133442503632 * bf),
          long(1.0401954891948177179593812079875483 * bf),
          long(1.0850394701840971950932122888525131 * bf)};
const long K2[] = {long(-0.06121838089436189909196399756144237 * bf),
          long(-0.064653110965738437430856587088264457 * bf),
          long(-0.19086985499541117593700925117442104 * bf),
          long(-0.31162066371367399467929466944519813 * bf)};
const long K3[] = {long(-0.30174061136598465869347966592859658 * bf),
          long(-0.19548067695815569702438124124586404 * bf),
          long(-0.069511106771492688426680746471645609 * bf),
          long(0.011947243197312155915074454543066357 * bf)};
  long j = long(abs(x)>>(bitf-2));
  long y = Multiply(x,(K1[j] + Multiply(abs(x),K2[j] + Multiply(K3[j],Multiply(x,x)))));
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
  long y = Multiply(x,(K1[j] + Multiply(abs(x),K2[j] + Multiply(Multiply(x,x),K3[j] + Multiply(K4[j],abs(x))))));
  return y;
}

long  atan_P5_4(long x){
const long K1[] = {long(0.9999975964759876 * bf),
          long(0.9948861737406166 * bf),
          long(0.9948861737406166 * bf),
          long(0.9991580916067022 * bf)};
const long K2[] = {long(0.00013028819536007726 * bf),
          long(0.046744232087946556 * bf),
          long(0.046744232087946556 * bf),
          long(0.026450162455216635 * bf)};
const long K3[] = {long(-0.3355854876429768 * bf),
          long(-0.5063109720988022 * bf),
          long(-0.5063109720988022 * bf),
          long(-0.4705449092935895 * bf)}; 
const long K4[] = {long(0.016201080063245343 * bf),
          long(0.31972484365845205 * bf),
          long(0.31972484365845205 * bf),
          long(0.29210508279189074 * bf)};
const long K5[] = {long(0.15500543751429005 * bf),
          long(-0.06961567792059027 * bf),
          long(-0.06961567792059027 * bf),
          long(-0.061770299160417534 * bf)};
  long j = long(abs(x)>>(bitf-2));
  long y = Multiply(x,(K1[j] + Multiply(abs(x),K2[j] + Multiply(Multiply(x,x),K3[j] + Multiply(K4[j],abs(x)) + Multiply(K5[j],Multiply(x,x))))));
  return y;
}

long  atan_P2_8(long x){
const long K1[] = {long(1.0022020982721835 * bf),
          long(1.0110060309227178 * bf),
          long(1.0272377858060056 * bf),
          long(1.04565293289239 * bf),
          long(1.061830421010721 * bf),
          long(1.0727212261456525 * bf),
          long(1.0727212261456525 * bf),
          long(1.0742737699176217 * bf)};
const long K2[] = {long(-0.05733310996133802 * bf),
          long(-0.12271115275172279 * bf),
          long(-0.1870427658501457 * bf),
          long(-0.23615705491487868 * bf),
          long(-0.26863712912770704 * bf),
          long(-0.28618682076209223 * bf),
          long(-0.28618682076209223 * bf),
          long(-0.2889218451792166 * bf)};
  long j = long(abs(x)>>(bitf-3));
  long y = Multiply(x,(K1[j] + Multiply(K2[j],abs(x))));
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
  return y;
}




  //long cykle =0;

void setup() {
  //cykle = SysTick->VAL;
  float step = 0.00001f;  // (0.00001f); //ok 200k Sampli
  float currentValue = 0.0f + step;
  float maxValue = 1.0f;
  //long y;
  long x;
  long i = 1;
  for (i = 1; currentValue < maxValue; i++) {
    
    x = long(currentValue * bf);  

    //long y = P4(x);
    //long y = P5(x);
    //long y = P6(x);
    //long y = P7(x);
    //long y = P8(x);
    //long y = P9(x);

    //long y = atan_P2_4(x);
    //long y = atan_P3_4(x);
    //long y = atan_P4_4(x);
    //long y = atan_P5_4(x);
    //long y = atan_P2_8(x);
    long y = atan_P2_16(x);

    Serial.print(y);

  }
}

void loop() {
}
