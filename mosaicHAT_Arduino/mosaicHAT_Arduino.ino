#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

SoftwareSerial mosaicSerial = SoftwareSerial(10, 11);; // RX, TX of software serial (mosaicHAT connection)
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  pinMode(10,INPUT); //RX of software serial, input mode
  pinMode(11,OUTPUT); //TX of software serial, output mode
  mosaicSerial.begin(9600);// Software Serial connects to mosaicHAT
  Serial.begin(9600);  // default Serial connects to a computer via USB
  pinMode(2, INPUT_PULLUP);
  lcd.begin();
   lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("  mosaicHAT");
  lcd.setCursor(1,1);
  lcd.print("  &Arduino");
  delay(1000); // wait a second to show the intro 
} 

String nmea_string,sreadString;
String Latitude,Longitude,Latitude_direction,Longitude_direction,Quality_indicator,SVs_Number,Height,Geoid_separation,Quality_indicator_string; //nmea message elements
String quality_string_array [6]={"No Fix","GNSS fix","DGPS","","RTK","RTK Float"}; //string meanings of quality indicator values
bool nmea_flag=false,button_flag=false,push_button=true;
int separator_indices[14];
int page=0,disp_counter=0;

void loop() {

  push_button = digitalRead(2);
  push_button=!push_button; //convert from active LOW to active HIGH (true = clicked)

  // 
  if(push_button == true &&button_flag==false){
      page++;
      if(page>=3)page=0;
      button_flag=true;
  }else if(push_button==false){
      button_flag=false;
  }

  while (mosaicSerial.available()) {
    char c;
    delay(2) ; //delay to allow buffer to fill
    if (mosaicSerial.available() >0) {
         c = mosaicSerial.read();  //gets one byte from serial buffer
        sreadString += c; //makes the string sreadString  
    } 
  } 
  if(sreadString!="" ){
    Serial.println(sreadString);
    nmea_flag=true;
    nmea_string=sreadString;
  }
  sreadString="";
  
  if(nmea_flag){
    int c=0;
    for(int i=0;i<nmea_string.length();i++){
      if(nmea_string[i]==','){
        separator_indices[c]=i;
        c++;
      }
    }

    //parse nmea message into its important elements
    Quality_indicator= nmea_string.substring(separator_indices[5]+1,separator_indices[6]);
    SVs_Number= nmea_string.substring(separator_indices[6]+1,separator_indices[7]);
    Height=nmea_string.substring(separator_indices[8]+1,separator_indices[9]);
    Geoid_separation=nmea_string.substring(separator_indices[10]+1,separator_indices[11]);
    Latitude= nmea_string.substring(separator_indices[1]+1,separator_indices[2]);
    Longitude=nmea_string.substring(separator_indices[3]+1,separator_indices[4]);
    Latitude_direction= nmea_string.substring(separator_indices[2]+1,separator_indices[3]);
    Longitude_direction=nmea_string.substring(separator_indices[4]+1,separator_indices[5]);

    nmea_flag=false;
  }

  disp_counter++; 
  
  if(disp_counter>=10000){ // reducing update rate to avoid screen flickering
        lcd.clear();
    if(page==0){ // first page: Quality and SVs umber
      lcd.setCursor(1,0);
      Quality_indicator_string = quality_string_array[Quality_indicator.toInt()];
      lcd.print("Q: "+Quality_indicator_string);
      lcd.setCursor(1,1);
      lcd.print("SVs: "+SVs_Number);
    }else if(page==1){ // second page: Latitude and Longitude
      lcd.setCursor(0,0);
      lcd.print(Latitude+Latitude_direction);
      lcd.setCursor(0,1);
      lcd.print(Longitude+Longitude_direction);
    }else if(page==2){ // third page: Height and Geoidal Separation
      lcd.setCursor(1,0);
      lcd.print("H: "+Height+"m");
      lcd.setCursor(1,1);
      lcd.print("S: "+Geoid_separation+"m");
    }
     
    disp_counter=0;
  } 
} 
