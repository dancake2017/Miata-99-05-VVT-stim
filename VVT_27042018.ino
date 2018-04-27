int camAngles[]={20,360,400};
int crankAngles[]={100,140,250,320,430,500,610,680};
volatile unsigned long crankTimes[9];
volatile unsigned long camTimes[4];
volatile int toothCurrentCount;
volatile int secondaryToothCount;
volatile int secondaryToothCounter;
bool readyForCalc = false;
void setup() {
 

}

void loop() {


if (readyForCalc){
  
noInterrupts();  
unsigned long tempCrankTimes [9];
unsigned long tempCamTimes[4];
tempCamTimes[1] = camTimes[1];
tempCamTimes[2] = camTimes[2];
tempCamTimes[3] = camTimes[3];

tempCrankTimes[1] = crankTimes[1];
tempCrankTimes[2] = crankTimes[2];
tempCrankTimes[3] = crankTimes[3];
tempCrankTimes[4] = crankTimes[4];
tempCrankTimes[5] = crankTimes[5];
tempCrankTimes[6] = crankTimes[6];
tempCrankTimes[7] = crankTimes[7];
tempCrankTimes[8] = crankTimes[8];
interrupts();

}

}

void crankTrigger()
{
  //add some filtering
  toothCurrentCount++;
  if ((secondaryToothCount == 2) || (toothCurrentCount >= 9))
  {
    toothCurrentCount  = 1;
  }
  crankTimes[toothCurrentCount] = micros();
  secondaryToothCount = 0;

}

void camTrigger()
{
  //write some filtering
  secondaryToothCount++;
  secondaryToothCounter++;
  if ((secondaryToothCount == 2) || (secondaryToothCounter >= 4))
{
  secondaryToothCounter = 1;
}
camTimes[secondaryToothCounter] = micros();
}

