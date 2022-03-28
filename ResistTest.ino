 // resistTest4i
// integrating test of sampling A0-A3
// MSLoop is the length of the integration
// DlyInLoop is time between sampling within the integration loop
// DlyOutLoop is the cycle time between sample sets
// 22/02/21 JES report % etc
// 21/12/10 JES allow 0 as sensor
// 2/21/21
#define NumS  4
const int Snsrs[NumS] = {A0, A1, A2, A3};// analog sensors
/*
#define NumS  8
const int Snsrs[NumS] = {A0,A1,A2,A3, A4,A5,A6,A7};// analog sensors
*/
#define Mode  INPUT
const int MSLoop = 33;
const int DlyInLoop = 1;
const int DlyOutLoop = 2000;

int idx;
long int TimeStrt;
long int Smpl, Rnge, Prcnt;
long int Smpls;
long int Vals[NumS];
long int Highest[NumS];
long int Lowest[NumS];

void setup() {
  // put your setup code here, to run once:
  for (idx = 0; idx < NumS;++idx){
  if (Snsrs[idx] > 0) {pinMode(Snsrs[idx], Mode);}
  } // idx
    for (idx = 0; idx < NumS;++idx){
      Vals[idx] = Highest[idx] = 0;
      Lowest[idx] = 9999;
    }//for

  Serial.begin(9600);
  } // setup

void loop() {
  // put your main code here, to run repeatedly:
  TimeStrt = millis();
  Smpls = 0;
    for (idx = 0; idx < NumS;++idx){Vals[idx] = 0;}
  do {
    for (idx = 0; idx < NumS;++idx){
      if (Snsrs[idx] > 0){
      Smpl = analogRead(Snsrs[idx]);
//  Serial.println(Smpl);
      Vals[idx] += Smpl;
      if (Smpl > Highest[idx]){Highest[idx] = Smpl;}
      if (Smpl < Lowest [idx]){Lowest[idx]  = Smpl;}
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
  Serial.print(idx);
  Serial.print(" Pin: ");
  Serial.print(Snsrs[idx]);
  Serial.print(" IVal: ");
  Prcnt = (Vals[idx] / Smpls);
  Serial.print(Prcnt);
  Serial.print(" FmHi: ");
  Prcnt = Highest[idx] - Prcnt;
  Serial.print(Prcnt);
  Serial.print("/");
  Rnge = Highest[idx] - Lowest[idx];
  Prcnt = (Prcnt) * 100 / Rnge;
  Serial.print(Rnge);
  Serial.print(" ");
  Serial.print(Prcnt);
  Serial.print("% Hi: ");
  Serial.print(Highest[idx]);
  Serial.print(" Lo: ");
  Serial.println(Lowest[idx]);
}} // for
 
  delay(DlyOutLoop);
}
