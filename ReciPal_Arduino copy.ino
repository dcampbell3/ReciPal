#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

//Initialize Button Pin
const int buttonPin = 6;
int buttonState = 0;

//Initialize LCD Screen
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Initialize BlueTooth Serial Connection
SoftwareSerial bt(9,8);

//Initialize Strings
String s;
String currSubString = ""; 
int startIndex = 0; 
int indexOffset = 0;
String lines[64]; 
//String s = "One 1-pound^sirloin steak,^about 1 inch^thick^=Kosher salt and^freshly ground^black pepper ^=4 tablespoons^unsalted^butter, at room^temperature ^=1 tablespoon^finely chopped^fresh parsley ^=1 tablespoon^finely chopped^fresh chives ^=1 small clove^garlic, finely^grated ^=1/4 teaspoon^crushed red^pepper flakes ^=Allow the steak^to sit at room^temperature for^30 minutes^before cooking.^=Preheat a^3.5-quart air^fryer to 400^degrees F.^Season the^steak on both^sides with a^generous pinch^of salt and^several grinds^of black^pepper. Place^the steak in^the center of^the air fryer^basket and cook^until desired^doneness, about^10 minutes for^medium-rare, 12^minutes for^medium and 14^minutes for^medium-well.^Transfer the^steak to a^cutting board^and allow to^rest, about 10^minutes.^=Meanwhile, mash^together the^butter,^parsley,^chives, garlic^and crushed red^pepper in a^small bowl^until combined.^Slice the steak^against the^grain into^1/4-inch-thick^pieces. Top^with the^garlic-herb^butter.^=";

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  bt.begin(9600);
  Serial.begin(9600);
  Serial.setTimeout(10000);
  pinMode(buttonPin, INPUT);
}

void loop() {
  while(Serial.available()){
    s+=Serial.readString();
  }
  
  String currentSubstring;
  
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    delay(1000);
    int i = s.indexOf("=");
    currentSubstring = s.substring(startIndex, i); 
    
    // find all lines in the current instruction
    int startLine = 0;
    int endLine = currentSubstring.indexOf("^");
    int j = 0;
    while(currentSubstring.indexOf("^") != -1) {
      if(j != 0) {
        startLine = endLine + 1;
        endLine = currentSubstring.indexOf("^");
      }
      
      lines[j] = currentSubstring.substring(0, endLine);
      Serial.println(lines[j]);
      currentSubstring = currentSubstring.substring(endLine + 1);
      Serial.println(currentSubstring);
      j += 1;
    }
    lines[j] = "";
    Serial.println();

    // print lines to lcd
    if(j == 1) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(lines[0]);
    }
    else if(j == 2) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(lines[0]);
      lcd.setCursor(0, 1);
      lcd.print(lines[1]);
    }
    else {
      for(int k = 0; k < j; k+=2) {
        lcd.clear();
        String lineOne = lines[k];
        String lineTwo = lines[k+1];
        lcd.setCursor(0, 0);
        lcd.print(lineOne);
        lcd.setCursor(0, 1);
        lcd.print(lineTwo);
        delay(1000);
      }
    }
    
    s = s.substring(i+1);
  }
}
