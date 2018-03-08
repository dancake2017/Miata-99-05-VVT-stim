#define resyncPin 10
#define offsetPin A0
#define rpmPin A1

volatile int crankCount = 0;
volatile int camCount = 0;
volatile int cam2Count;
bool resync = false;
unsigned long delayMicros;
unsigned long lastTime = 0;
int offset;
int tempOffset;
volatile int lastOffset = 10;
volatile byte pinCrank = LOW;
volatile byte pinCam = LOW;
int rpm = 100000;



void setup()
{
  pinMode (rpmPin, INPUT);
  pinMode (offsetPin , INPUT);
  pinMode (resyncPin, INPUT_PULLUP);
  Serial.begin (9600);
  DDRB = B11111111;
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  OCR1A = 1000;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS10);
  // TCCR1B |=(1<<CS12);
  TIMSK1 |= (1 << OCIE1A);

  interrupts();
  
}

ISR(TIMER1_COMPA_vect)
{
  
  crankCount++;
  if (crankCount > 720 )
  {
    crankCount = 0 ;
  }

  
  // Start comparing angles from Timer derived counter

  if (crankCount >= (55-offset) && crankCount <=( 75-offset))  {
   pinCam = HIGH;
 }
  else if (crankCount >= 100 && crankCount <= 104) {
    pinCrank = HIGH;
  }
  else if (crankCount >= 170 && crankCount <= 174) {
    pinCrank = HIGH;
  }
  else if (crankCount >= 280 && crankCount <= 284) {
    pinCrank = HIGH;
  }
  else if (crankCount >= 350 && crankCount <= 354) {
    pinCrank = HIGH;
  }
  else if (crankCount>= (395-offset) && crankCount <= (415-offset)){
    pinCam = HIGH;
  }
  else if (crankCount >= (435-offset) && crankCount <= (455-offset)) {
    pinCam = HIGH;
  }
  else if (crankCount >= 460 && crankCount <= 464) {
    pinCrank = HIGH;
  }
  else if (crankCount >= 530 && crankCount <= 534) {
    pinCrank = HIGH;
  }
  else if (crankCount >= 640 && crankCount <= 644) {
    pinCrank = HIGH;
  }
  else if (crankCount >= 710 && crankCount <= 714 ) {
    pinCrank = HIGH;
  }


  else {
    pinCrank = LOW;
    pinCam = LOW;
  }

  if ( pinCam == HIGH ) {
    PORTB = B10000000;
  }
  else if ( pinCrank == HIGH ) {
    PORTB = B00000010;
  }
  else {
    PORTB = B00000000;
  }

}
void loop() {

int offsetPinRead = analogRead(offsetPin);
tempOffset = map(offsetPinRead, 0,1023,0,40);


if (tempOffset != lastOffset){
  offset = tempOffset;
  Serial.println (offset);
  lastOffset = offset;
}
  
}

