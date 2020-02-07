/////////////////////////////////////////////////
// 8 DIGIT PANEL COUNTING DEMO
// Budd Churchward WB7FHC
// 02.07.20
/////////////////////////////////////////////////


int dataPin = 2;
int latchPin = 3;
int clockPin = 4;

long timeCheck;
long i = 12345678; // start counting here
int updown = -1;    // 1 counts up ... -1 counts down
boolean neg = false;

int speed = 1; // set speed between 1 - 1000
int data;
int digit0, digit1, digit2, digit3, digit4, digit5, digit6, digit7;

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
  B11100110, //9  
  B00000010, // -
  B10011110  // E
};

String myString;
String parseString;

void setup(){
  //Serial.begin(115200);
  //Serial.println("\nbegin\ngood for you");
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  buildNum();
  timeCheck = millis();
}

void showDigit(int digit, int pos) {
   byte spot=B11111111;
   bitClear(spot,pos);
   data = segs[digit];
   if (pos == 6 || pos == 3) data++; // add a decimal point to these digits
  
  shiftOut(dataPin,clockPin, LSBFIRST,spot);
  shiftOut(dataPin,clockPin, LSBFIRST,data);
  digitalWrite(latchPin,1);
  digitalWrite(latchPin, 0);

}

void buildNum () {
  neg=false;
  if (i<0) {
    neg=true;
    myString = myString.substring(1);
    i = i * -1;
  }
  
myString = String(i);
  digit0=-1;
  digit1=-1;
  digit2=-1;
  digit3=-1;
  digit4=-1;
  digit5=-1;
  digit6=-1;
  digit7=-1;
  
  if (i>9999999) // 8 digits
  {
    parseString = myString.substring(0,1);
    //Serial.print("....");
    //Serial.println(parseString);
    digit7 = parseString.toInt();
    myString = myString.substring(1);
    //showDigit(digit0,0);
    //Serial.print(' ');
    //Serial.println(myString);
    
  }
  if (i>999999) // 7 digits
  {
    parseString = myString.substring(0,1);
    //Serial.print("....");
    //Serial.println(parseString);
    digit6 = parseString.toInt();
    myString = myString.substring(1);
    //showDigit(digit0,0);
    //Serial.print(' ');
    //Serial.println(myString);
    
  }
  if (i>99999) // 6 digits
  {
    parseString = myString.substring(0,1);
    //Serial.print("....");
    //Serial.println(parseString);
    digit5 = parseString.toInt();
    myString = myString.substring(1);
    //showDigit(digit0,0);
    //Serial.print(' ');
    //Serial.println(myString);
    
  }
  if (i>9999) // 5 digits
  {
    parseString = myString.substring(0,1);
    //Serial.print("....");
    //Serial.println(parseString);
    digit4 = parseString.toInt();
    myString = myString.substring(1);
    //showDigit(digit0,0);
    //Serial.print(' ');
    //Serial.println(myString);
    
  }
  if (i>999) // 4 digits
  {
    parseString = myString.substring(0,1);
    //Serial.print("....");
    //Serial.println(parseString);
    digit3 = parseString.toInt();
    myString = myString.substring(1);
    //showDigit(digit0,0);
    //Serial.print(' ');
    //Serial.println(myString);
    
  }

  if (i>99)  // 3 digits
  {
    parseString = myString.substring(0,1);
    //Serial.print("...");
    //Serial.println(parseString);
    digit2 = parseString.toInt();
    myString = myString.substring(1);
    //showDigit(digit1,1);
    //Serial.print(' ');
     //Serial.println(myString);
 }
  if (i>9)  // 2 digits
    {
      parseString = myString.substring(0,1);
      digit1 = parseString.toInt();
      myString = myString.substring(1);
    }    
  digit0 = myString.toInt();
  if (neg) i = i * -1; // put the minus sign back for the next go around 
}

void showError(){
for (int m=0; m<20; m++){
  showDigit(10,1);
  delay(10);
  showDigit(11,2);
  delay(10);
}


  digit0=-1;
  digit1=-1;
  digit2=-1;
  digit3=-1;
  digit4=-1;
  digit5=-1;
  digit6=-1;
  digit7=-1;
}



void loop(){
    int negSpot = -1;

    if (digit7 >= 0) {
      if (neg) {
        showError();
      }else{
        showDigit(digit7,7);
      }
    }
    if (digit6 >= 0) {
      showDigit(digit6,6);
      if (neg) negSpot=6;
      neg = false;
    }


    if (digit5 >= 0) {
      showDigit(digit5,5);
      if (neg) negSpot=5;
      neg = false;
    }
    if (digit4 >= 0) {
      showDigit(digit4,4);
      if (neg) negSpot=4;
      neg = false;
    }
    if (digit3 >= 0) {
      showDigit(digit3,3);
      if (neg) negSpot=3;
      neg = false;
    }

    if (digit2 >= 0) 
    {
      showDigit(digit2,2);
      if (neg) negSpot=2;
      neg = false;
    }
        
    if (digit1 >= 0) {
      showDigit(digit1,1);
      if (neg) negSpot=1;
      neg = false;
    }
    if (digit0 >= 0) {
      showDigit(digit0,0);
      if (neg) negSpot=0;
      neg = false;
    }
    
    //Serial.print("negSpot=");Serial.println(negSpot);
    if (negSpot>=0) {
      showDigit(10,negSpot+1);
      neg = true;
    }
    if (millis() - timeCheck >= 1000 - speed)
      {
    ////Serial.println(timeCheck);
        timeCheck = millis();
        if (i == 99999999) updown = -1;
        if (i < -9999999) updown = 1;
        i=i+updown;
        buildNum();  
      }
      
}
