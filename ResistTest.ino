 // resistTest4i
// integrating test of sampling A0-A3
// MSLoop is the length of the integration
// DlyInLoop is time between sampling within the integration loop
// DlyOutLoop is the cycle time between sample sets
// 2024-07-08 JES fix for 0
// 2024-05-09 JES redesign to report new data technique
// *************************************************************************
// This code is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This software is distributed WITHOUT ANY WARRANTY; 
// without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// http://www.gnu.org/licenses/.
// *************************************************************************
/* #define NumS  4
//const int Snsrs[NumS] = {A0, A1, A2, A3, A4, A5, A6, A7};// analog sensors
const int Snsrs[NumS] = {A0, A1, A2, A3};// analog sensors
*/
#define NumS  8
const int Snsrs[NumS] = {A0,A1,A2,A3, A4,A5,A6,A7};// analog sensors
//
#define Mode  INPUT
const int MSLoop = 33;
const int DlyInLoop = 0;
const int DlyOutLoop = 5000;
const int RecalibrateMts = 1;

int idx;
long int TimeStrt, RecalStrt;
long int Prcnt, Smpls;
long int Vals[NumS];
long int Highest[NumS];

void setup() {
  // put your setup code here, to run once:
  for (idx = 0; idx < NumS;++idx){
  if (Snsrs[idx] > 0) {pinMode(Snsrs[idx], INPUT);}
  } // idx
    for (idx = 0; idx < NumS;++idx){
      Vals[idx] = Highest[idx] = 0;
    }//for
  RecalStrt = millis();
  Serial.begin(9600);
  Serial.println("Startup");
  } // setup

void loop() {
  // put your main code here, to run repeatedly:
  Smpls = 0;
  TimeStrt = millis();
  for (idx = 0; idx < NumS;++idx){Vals[idx] = 0;}
  do {
    for (idx = 0; idx < NumS;++idx){
      if (Snsrs[idx] > 0){
      Vals[idx] += analogRead(Snsrs[idx]);
    }}
    ++Smpls;
    if (DlyInLoop > 0) {delay(DlyInLoop);}
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
  Serial.print(" Pin: " + String(idx) + " " + String(Snsrs[idx]));
  Serial.print(" High: " + String(Highest[idx]));
  Prcnt = (Vals[idx]);
  Serial.print(" CurVal: " + String(Prcnt));
  Prcnt = (Highest[idx] > 0)?100.-(Prcnt * 100.) / Highest[idx]:0;
  Serial.print(" % drop: ");
  Serial.println(String(Prcnt));
}} // for
 
 // Serial.println("Recalibrate at " + String((TimeStrt + RecalibrateMts*60000.) - millis()));
 if ((RecalStrt + RecalibrateMts*60000.) < millis()){
   for (idx = 0; idx < NumS;++idx){
      Highest[idx] = 0;}//for
  Serial.println("Recalibrate");
  RecalStrt = millis();
 };

  delay(DlyOutLoop);
}
