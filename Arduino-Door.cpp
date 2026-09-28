#include <Servo.h>
#include <LiquidCrystal_I2C.h>

Servo Garage;

LiquidCrystal_I2C lcd(0x27, 16, 2);
  
const int echo_pin = 6;
const int trigger_pin = 7;
const int motor_pin = 9;
const int red_led_pin = 2;
const int green_led_pin = 3;
const int sound_pin = 4;

const int posClosed = 0;
const int posOpen = 90;

const int distanceMax = 200;

int duration;
int distance;

void setup()
{
  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();
  
  pinMode(echo_pin, INPUT);
  pinMode(trigger_pin, OUTPUT);
  
  pinMode(red_led_pin, OUTPUT);
  pinMode(green_led_pin, OUTPUT);
  
  pinMode(sound_pin, OUTPUT);
  
  Garage.attach(motor_pin);
  
  digitalWrite(green_led_pin, LOW);
  digitalWrite(red_led_pin, HIGH);
  
  lcd.setCursor(0, 0);
  lcd.print("MASINOS NERA");
}

void loop()
{

  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);
  
  duration = pulseIn(echo_pin, HIGH);

  distance = (duration/2) * 0.0343 ;
  
  Serial.print(duration);
  Serial.println();
  
  if(distance > 0 && distance <= distanceMax){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MASINA PRIARTEJO");
    
    Garage.write(posOpen);
    
    digitalWrite(green_led_pin, HIGH);
    digitalWrite(red_led_pin, LOW);
    
    tone(sound_pin, 1500);
    delay(150);
    noTone(sound_pin);
    
    delay(300);
   
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("MASINOS NERA");
    
  	Garage.write(posClosed);
    
    digitalWrite(red_led_pin, HIGH);
    digitalWrite(green_led_pin, LOW);
  }
 	
  
  delay(1000);
}



















