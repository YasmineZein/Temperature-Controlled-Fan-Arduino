#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>

#define DHTPIN 7         
#define DHTTYPE DHT11   

#define MOTOR_PIN_ENA 9  
#define MOTOR_PIN_IN1 10  
#define MOTOR_PIN_IN2 11  

#define TEMPERATURE_THRESHOLD 22 
#define TEMPERATURE_THRESHOLD1 25

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2); 

void setup() {
  Serial.begin(9600);
  dht.begin();

  Wire.begin();
  lcd.begin(); 
  lcd.backlight();  
  lcd.setCursor(0, 0);
  lcd.print("Temperature:");
}

void loop() {
  delay(2000); 

  float temperature = dht.readTemperature(); 
  if (isnan(temperature)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  lcd.setCursor(0, 1); 
  lcd.print("                "); 

  // Adjust motor speed based on temperature
  if (temperature > TEMPERATURE_THRESHOLD1) {
    // Increase motor speed
    analogWrite(MOTOR_PIN_ENA, 255);    
    digitalWrite(MOTOR_PIN_IN1, HIGH);  
    digitalWrite(MOTOR_PIN_IN2, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Motor Speed: Max");
  }
  else if (temperature > TEMPERATURE_THRESHOLD) {
    // Increase motor speed
    analogWrite(MOTOR_PIN_ENA, 100);   
    digitalWrite(MOTOR_PIN_IN1, HIGH);  
    digitalWrite(MOTOR_PIN_IN2, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Motor Speed: Med");
  }
  else {
    // Decrease motor speed
    analogWrite(MOTOR_PIN_ENA, 45);    
    digitalWrite(MOTOR_PIN_IN1, HIGH);  
    digitalWrite(MOTOR_PIN_IN2, LOW);
    lcd.setCursor(0, 1);
    lcd.print("Motor Speed: Low");
  }

  lcd.setCursor(12, 0); 
  lcd.print(temperature); 
}
