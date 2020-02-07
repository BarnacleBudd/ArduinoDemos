//////////////////////////////////////////////////////////
// YouTube PCB Design Part 10 sketch
// Budd Churchward WB7FHC
// 02-05-20
//////////////////////////////////////////////////////////

int dataPin = 2;
int latchPin = 3;
int clockPin = 4;

byte segs[] = {
// ABCDEFG. These bit patterns produce the image of digits on our panel
  B11111100, //0
  B01100000, //1
  B11011010, //2
  B11110010, //3
  B01100110, //4
  B10110110, //5
  B10111110, //6
  B11100000, //7
  B11111110, //8
  B11100110  //9  
};

byte numberDeck[8];  // stores the bit paterns for the digits entered

byte spot = B11111111; // will be used to determine which digit lights up
byte data;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Sketch Begins");

  pinMode (dataPin, OUTPUT);
  pinMode (latchPin, OUTPUT);
  pinMode (clockPin, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  // we just hang out here until data is entered on the keyboard
  if (Serial.available() > 0) getDigits();
}

void getDigits() {
  delay(20); // a little time to get all the data into the buffer
  int newDigit;
  int numDigits = Serial.available();
  int i = numDigits - 1;  // arrays are indexed starting with 0 not 1
  while (Serial.available() > 0 ) {
     newDigit = Serial.read() - 48;
     numberDeck[i] = segs[newDigit];
     i--; // incoming digits are stored in array from the bottom up
  }

// We keep turning digits on over and over again until a new number comes in
while (Serial.available() == 0) {
  i=0;
  while (i < numDigits) {
    spot = B11111111;
    bitClear(spot,i); // determines which digit lights up
    shiftOut(dataPin,clockPin,LSBFIRST,spot);
    data = numberDeck[i];
    shiftOut(dataPin,clockPin,LSBFIRST,data);

// toggle the latch pin to show the digit
// only one digit is lit at any time, we just do it fast
  digitalWrite(latchPin,1);
  digitalWrite(latchPin,0);
  i++;
  //delay(50);
  }
 }
}
