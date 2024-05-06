 // resistTest4i
// integrating test of sampling A0-A3
// MSLoop is the length of the integration
// DlyInLoop is time between sampling within the integration loop
// DlyOutLoop is the cycle time between sample sets
// 2024-05-06 JES redesign to report new data technique
// 22/02/21 JES report % etc
// 21/12/10 JES allow 0 as sensor
// 2/21/21
#define NumS  4
//const int Snsrs[NumS] = {A0, A1, A2, A3, A4, A5, A6, A7};// analog sensors
const int Snsrs[NumS] = {A0, A1, A2, 0};// analog sensors
/*
#define NumS  8
const int Snsrs[NumS] = {A0,A1,A2,A3, A4,A5,A6,A7};// analog sensors
*/
#define Mode  INPUT
const int MSLoop = 33;
const int DlyInLoop = 0;
const int DlyOutLoop = 2000;
const int RecalibrateMts = 1;

int idx;
long int TimeStrt;
long int Prcnt, Smpls;
long int Vals[NumS];
long int Highest[NumS];

void setup() {
  // put your setup code here, to run once:
  for (idx = 0; idx < NumS;++idx){
  if (Snsrs[idx] > 0) {pinMode(Snsrs[idx], Mode);}
  } // idx
    for (idx = 0; idx < NumS;++idx){
      Vals[idx] = Highest[idx] = 0;
    }//for

  Serial.begin(9600);
  Serial.println("Startup");
  TimeStrt = millis();
  } // setup

void loop() {
  // put your main code here, to run repeatedly:
  Smpls = 0;
    for (idx = 0; idx < NumS;++idx){Vals[idx] = 0;}
  do {
    for (idx = 0; idx < NumS;++idx){
      if (Snsrs[idx] > 0){
      Vals[idx] += analogRead(Snsrs[idx]);
    }}
    ++Smpls;
    delay(DlyInLoop);
  } while (TimeStrt + MSLoop > millis());

Serial.print(Smpls);
Serial.print(" Samples Over ");
Serial.print(MSLoop);
Serial.print(" Ms at ");
Serial.println(millis());

for (idx = 0; idx < NumS;++idx){
  if (Snsrs[idx] > 0){
  Vals[idx] /= Smpls;
  if (Highest[idx] < Vals[idx]){Highest[idx] = Vals[idx];}
  Serial.print(" Pin: " + String(Snsrs[idx]));
  Serial.print(" High: " + String(Highest[idx]));
  Prcnt = (Vals[idx]);
  Serial.print(" CurVal: " + String(Prcnt));
  Prcnt = 100.-(Prcnt * 100.) / Highest[idx];
  Serial.print(" % drop: ");
  Serial.println(String(Prcnt));
}} // for
 
 // Serial.println("Recalibrate at " + String((TimeStrt + RecalibrateMts*60000.) - millis()));
 if ((TimeStrt + RecalibrateMts*60000.) < millis()){
   for (idx = 0; idx < NumS;++idx){
      Highest[idx] = 0;}//for
  Serial.println("Recalibrate");
 };

  delay(DlyOutLoop);
}
