#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <DHT_U.h>
#include <pitches.h>
#include <TimeLib.h>

#define DHTPIN 7
#define DHTTYPE DHT11

LiquidCrystal_I2C lcd(0x27,20,4);
DHT dht(DHTPIN, DHTTYPE);

// 해 모양 사용자 정의 문자
byte sun0[8] = {0b00000, 0b00000, 0b00000, 0b01100, 0b00110, 0b00000, 0b00001, 0b01101};
byte sun1[8] = {0b00100, 0b00100, 0b00000, 0b01110, 0b10001, 0b00000, 0b00000, 0b00000};
byte sun2[8] = {0b00000, 0b00000, 0b00100, 0b01100, 0b01000, 0b00000, 0b10000, 0b10110};
byte sun3[8] = {0b00001, 0b00000, 0b00010, 0b00110, 0b00100, 0b00000, 0b00000, 0b00000};
byte sun4[8] = {0b00000, 0b00000, 0b10001, 0b01110, 0b00000, 0b00100, 0b00100, 0b00000};
byte sun5[8] = {0b10000, 0b00000, 0b01100, 0b00110, 0b00000, 0b00000, 0b00000, 0b00000};

// 달 모양 사용자 정의 문자
byte moon6[8] = {0b00000, 0b00000, 0b00000, 0b00001, 0b00001, 0b00011, 0b00011, 0b00011};
byte moon7[8] = {0b00000, 0b01000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b11000};
byte moon8[8] = {0b00011, 0b00011, 0b00001, 0b00001, 0b00000, 0b00000, 0b00000, 0b00000};
byte moon9[8] = {0b11000, 0b11110, 0b11111, 0b11111, 0b11111, 0b01110, 0b00000, 0b00000};
byte moon10[8] = {0b00000, 0b00100, 0b11000, 0b10000, 0b00000, 0b00000, 0b00000, 0b00000};

int speakerPin = A1;
unsigned long noteLength = 250;
int melody_index = 0;
unsigned long melody_prev_time = millis();
int MELODY[] = {
  NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, 
  NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5, 0
  };
int MELODY_LENGTH = sizeof(MELODY)/sizeof(0);

int cds = A0;
int vibrate = 11;
int count = 0;
int h=25;
int m=0;
int s=0;
int button_T = 2;
int button_A = 3;
int button_P = 4;
int state = 0;
int MONTH_DAY[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
String WEEK_DAY[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

bool is_leap_year(int input_year) {
  if((input_year%4==0) && (input_year%400==0 || input_year%100!=0)) {return true;}
  else {return false;} 
}
int get_month_day(int _year, int _month) {
  if ( is_leap_year(_year) && _month==2 ) {return 29;}
  else {return MONTH_DAY[_month - 1];}
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  setTime(00,00,00,01,01,2022);
  dht.begin();
  pinMode(vibrate, INPUT);
}

void timeSetting() {
  lcd.init();
  int Year = year();
  int Month = month();
  int Day = day();
  int Hour = hour();
  int Min = minute();
  int Sec = second();

  lcd.setCursor(3,0);
  lcd.print("Clock  Setting");

  while(state<=3) {
    lcd.setCursor(6,2);
    if( (Hour/10)==0 ) {lcd.print(String("0") + Hour);}
    else {lcd.print(Hour);}
    lcd.print(":");
    if( (Min/10)==0 ) {lcd.print(String("0") + Min);}
    else {lcd.print(Min);}
    lcd.print(":");
    if( (Sec/10)==0 ) {lcd.print(String("0") + Sec);}
    else {lcd.print(Sec);}
    
    if(state==1){
      lcd.setCursor(6,1);
      lcd.print("v");
      if(digitalRead(button_P)) {
        Hour++;
        if(Hour==24) {Hour=0;}
        delay(300);
      }
    }

    if(state==2){
      lcd.setCursor(6,1);
      lcd.print(" ");
      lcd.setCursor(9,1);
      lcd.print("v");
      if(digitalRead(button_P)) {
        Min++;
        if(Min==60) {Min=0;}
        delay(300);
      }
    }

    if(state==3){
      lcd.setCursor(9,1);
      lcd.print(" ");
      lcd.setCursor(12,1);
      lcd.print("v");
      if(digitalRead(button_P)) {
        Sec++;
        if(Sec==60) {Sec=0;}
        delay(300);
      }
    }

    if(digitalRead(button_T)) {
      state++;
      delay(300);
      if(state==4) {
        break;
      }
    }
  }
  
  while(state>=4 && state<=6) {
    lcd.setCursor(5,2);
    lcd.print(Year);
    lcd.print("/");
    if( (Month/10)==0 ) {
      lcd.print(String("0") + Month);
    }else {lcd.print(Month);}
    lcd.print("/");
    if( (Day/10)==0 ) {
      lcd.print(String("0") + Day);
    }else {lcd.print(Day);}

    if(state==4){
      lcd.setCursor(12,1);
      lcd.print(" ");
      lcd.setCursor(5,1);
      lcd.print("v");
      if(digitalRead(button_P)) {
        Year++;
      }
      delay(300);
    }

    if(state==5){
      lcd.setCursor(5,1);
      lcd.print(" ");
      lcd.setCursor(10,1);
      lcd.print("v");
      if(digitalRead(button_P)) {
        Month++;
        if(Month==13) {Month=1;}
      }
      delay(300);
    }

    if(state==6){
      lcd.setCursor(10,1);
      lcd.print(" ");
      lcd.setCursor(13,1);
      lcd.print("v");
      if(digitalRead(button_P)) {
        Day++;
        if(Day>get_month_day(Year, Month)) {Day=1;}
      }
      delay(300);
    }

    if(digitalRead(button_T)) {
      state++;
      delay(100);
      if(state==7) {
        state=0;
        break;
      }
    }
  }

  setTime(Hour,Min,Sec,Day,Month,Year);
  lcd.init();
}

void alarmSetting() {
  lcd.init();
  int Hour = h;
  int Min = m;
  int Sec = s;

  lcd.setCursor(3,0);
  lcd.print("Alarm  Setting");

  while(state<=3) {
    lcd.setCursor(6,2);
    if( (Hour/10)==0 ) {lcd.print(String("0") + Hour);}
    else {lcd.print(Hour);}
    lcd.print(":");
    if( (Min/10)==0 ) {lcd.print(String("0") + Min);}
    else {lcd.print(Min);}
    lcd.print(":");
    if( (Sec/10)==0 ) {lcd.print(String("0") + Sec);}
    else {lcd.print(Sec);}
    
    if(state==1){
      lcd.setCursor(6,1);
      lcd.print("v");
      if(digitalRead(button_P)) {
        Hour++;
        if(Hour>=24) {Hour=0;}
        delay(300);
      }
    }

    if(state==2){
      lcd.setCursor(6,1);
      lcd.print(" ");
      lcd.setCursor(9,1);
      lcd.print("v");
      if(digitalRead(button_P)) {
        Min++;
        if(Min==60) {Min=0;}
        delay(300);
      }
    }

    if(state==3){
      lcd.setCursor(9,1);
      lcd.print(" ");
      lcd.setCursor(12,1);
      lcd.print("v");
      if(digitalRead(button_P)) {
        Sec++;
        if(Sec==60) {Sec=0;}
        delay(300);
      }
    }

    if(digitalRead(button_A)) {
      state++;
      delay(100);
      if(state==4) {
        state=0;
        break;
      }
    }
  }

  h=Hour;
  m=Min;
  s=Sec;
  lcd.init();
}

void alarm() {
  lcd.init();
  lcd.setCursor(0,0);
  lcd.print("Now you have to wake");
  lcd.setCursor(6,2);
  if( (h/10)==0 ) {
    lcd.print(String("0") + h);
  }else {lcd.print(h);}
  lcd.print(":");
  if( (m/10)==0 ) {
    lcd.print(String("0") + m);
  }else {lcd.print(m);}
  lcd.print(":");
  if( (s/10)==0 ) {
    lcd.print(String("0") + s);
  }else {lcd.print(s);}
    
  lcd.setCursor(2,3);
  lcd.print("!!mission: ");
  lcd.setCursor(15,3);
  lcd.print(String("T!!"));
  
  while(count!=50) {
    unsigned long melody_cur_time = millis();
    if ( melody_cur_time - melody_prev_time >=  noteLength ) {
      tone(speakerPin, MELODY[melody_index % MELODY_LENGTH], noteLength);
      melody_index += 1;
      melody_prev_time = melody_cur_time;
    }
    
    if(digitalRead(vibrate)==LOW) {
      count++;
      delay(30);
    }
    lcd.setCursor(13,3);
    if( (count/10)==0 ) {lcd.print(String("0") + count);}
    else {lcd.print(count);}
  }
  lcd.init();
  count=0;
}

void day_night() {
  int cdsValue = analogRead(cds);
  if(cdsValue<350) {
    lcd.createChar(0, sun0);
    lcd.createChar(1, sun1);
    lcd.createChar(2, sun2);
    lcd.createChar(3, sun3);
    lcd.createChar(4, sun4);
    lcd.createChar(5, sun5);    
    lcd.setCursor(15,1);
    lcd.write(0);
    lcd.write(1);
    lcd.write(2);
    lcd.setCursor(15,2);
    lcd.write(3);
    lcd.write(4);
    lcd.write(5);
  }
  else{
    lcd.createChar(6, moon6);
    lcd.createChar(7, moon7);    
    lcd.createChar(8, moon8);
    lcd.createChar(9, moon9);
    lcd.createChar(10, moon10);
    lcd.setCursor(15,1);
    lcd.write(6);
    lcd.write(7);
    lcd.print(" ");
    lcd.setCursor(15,2);
    lcd.write(8);
    lcd.write(9);
    lcd.write(10);
  }
}

void LCDclockDisplay() {
  lcd.setCursor(2,1);
  lcd.print(year());                   // year
  
  lcd.print("/");
  if( (month()/10)==0 ) {
    lcd.print(String("0") + month());  // month
  }else {lcd.print(month());}
  
  lcd.print("/");
  if( (day()/10)==0 ) {
    lcd.print(String("0") + day());  // day
  }else {lcd.print(day());}

  lcd.setCursor(3,2);
  if( (hour()/10)==0 ) {
    lcd.print(String("0") + hour());   // hour
  }else {lcd.print(hour());}
  
  lcd.print(":");
  if( (minute()/10)==0 ) {
    lcd.print(String("0") + minute());  // minute
  }else {lcd.print(minute());}

  lcd.print(":");
  if( (second()/10)==0 ) {
    lcd.print(String("0") + second());  // second
  }else {lcd.print(second());}

  lcd.setCursor(15,0);
  int w = weekday()-1;
  lcd.print(WEEK_DAY[w]);
  
  float temp = dht.readTemperature();
  lcd.setCursor(14,3);
  lcd.print(temp);
  lcd.setCursor(18,3);
  lcd.print("C");
  day_night();

  if(digitalRead(button_T)) {
    state++;
    delay(50);
    timeSetting();
  }

  if(digitalRead(button_A)) {
    state++;
    delay(50);
    alarmSetting();
  }
  
  if(hour()==h && minute()==m && second()==s) {
    alarm();
  }
}

void loop() {
  LCDclockDisplay();
}
