#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define rs 2
#define en 3
#define d4 4
#define d5 5
#define d6 6
#define d7 7
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
SoftwareSerial phsensor(11, 12);
//SoftwareSerial gsm(11, 12);
int ldr_pin = A0;  // Assuming you're using an analog pin for the LDR
int light_pin = 13;
const int dallasTempPin = 9;
int gas = 10;
int buzzer = 8;
String pHval;
String msg;

OneWire oneWire(dallasTempPin);
DallasTemperature tempSensor(&oneWire);
float tempC;
DeviceAddress insideThermometer;

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  phsensor.begin(9600);
  //gsm.begin(9600);
  
  pinMode(ldr_pin, INPUT);
  pinMode(gas, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(light_pin, OUTPUT);
  
  digitalWrite(light_pin, HIGH);
  digitalWrite(buzzer, LOW);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enhancing milk ");
  lcd.setCursor(0, 1);
  lcd.print("Quality");
  delay(1000);
}

void loop() {
  // Temperature Reading
  tempSensor.requestTemperatures();
  tempC = tempSensor.getTempCByIndex(0);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC);
  delay(2000);
  
  // LDR value reading (Fat/Thickness Calculation)
  int ldrValue = analogRead(ldr_pin);  // Read analog value from LDR pin
  int fatPercentage = map(ldrValue, 0, 1023, 0, 100);  // Map LDR value to fat percentage
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LDR Value: ");
  lcd.print(ldrValue);
  
  lcd.setCursor(0, 1);
  lcd.print("Fat %: ");
  lcd.print(fatPercentage);  // Display the mapped value (fat percentage)
  delay(2000);
  
  // Gas value reading (spoiled milk detection)
  int gasValue = digitalRead(gas);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Gas Value: ");
  lcd.print(gasValue);
  delay(1000);
  
  if (tempC >= 32) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("High Temperature");
    lcd.setCursor(0, 1);
    lcd.print("Temp: ");
    lcd.print(tempC);
    digitalWrite(buzzer, HIGH);
    delay(2000);
    digitalWrite(buzzer, LOW);
     msg = "HIGH Temperature";
      SendMessage();
      delay(2000);
  }
  
  if (gasValue == 0) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Spoiled Milk");
    digitalWrite(buzzer, HIGH);
    delay(2000);
    digitalWrite(buzzer, LOW);
     msg = "spoiled milk";
      SendMessage();
      delay(2000);
  }

  // pH value reading (Milk pH level)
  if (phsensor.available() > 0) {
    pHval = phsensor.readString();
    int a = pHval.indexOf(':');
    int b = pHval.indexOf(',');
    a = a + 1;
    pHval = pHval.substring(a, b);
    
    lcd.clear();
    lcd.print("PH Value: ");
    lcd.print(pHval);
    delay(1500);

    if ((pHval.toFloat() < 5) || (pHval.toFloat() > 9)) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("pH Abnormal");
      digitalWrite(buzzer, HIGH);
      delay(2000);
      digitalWrite(buzzer, LOW);
       msg = "abnormal pH value";
      SendMessage();
      delay(2000);
    }
  }
  String uno = "a" + String(tempC) + "b" + String( pHval) + "c" + String(gasValue)+ "d" +String(ldrValue)+ "e";
  Serial.println(uno);
  delay(1000);
}
void SendMessage()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Message sending........");
  Serial.println("Setting the GSM in text mode");
  phsensor.println("AT+CMGF=1\r");
  delay(2000);
  Serial.println("Sending SMS to the desired phone number!");
 phsensor.println("AT+CMGS=\" HERE ENTER YOUR MOBILE NUMBER\"\r");          // Replace  with your mobile number
  delay(2000);
 phsensor.println(msg);    // SMS Text
  delay(2000);
  phsensor.write(26);               // ASCII code of CTRL+Z
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Message sent.......");
  delay(1000);
}
