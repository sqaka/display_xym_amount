//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte receive_data;
char byte_amount[10];
String str_amount;
int xym_amount;

void setup()
{
  lcd.init();
  Serial.begin(115200);
}

void loop()
{
  if (Serial.available() > 0) {
    receive_data = Serial.readBytesUntil('\n', byte_amount, 5);
    
    if (receive_data > 0) {
      str_amount = String(byte_amount);
      xym_amount = str_amount.toInt();
    }
  
    if (xym_amount > 0){
      lcd.backlight();
      lcd.display();
      lcd.setCursor(0, 0);
      lcd.print("thank you throw");
      lcd.setCursor(0, 1);
      lcd.print(xym_amount);
      lcd.setCursor(12, 1);
      lcd.print("XYM");
        
      for(int i=0; i<5; i++) {
        lcd.noDisplay();
        delay(500);
        lcd.display();
        delay(1000);
      }
     lcd.clear();
     Serial.flush();
    }
  }
}
