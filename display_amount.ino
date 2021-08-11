//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String str_amount;
int str_len;
int xym_amount;

void setup()
{
  lcd.init();
  Serial.begin(9600);
}

void loop()
{
  // Serial.println('0');
  while(Serial.available()) {
    str_amount = Serial.readStringUntil('\n');
    str_len = str_amount.length();
    
    if (str_len > 0){
      xym_amount = str_amount.toInt();
      lcd.backlight();
      lcd.display();
      lcd.setCursor(0, 0);
      lcd.print("thank you throw");
      lcd.setCursor(0, 1);
      lcd.print(xym_amount);
      lcd.setCursor(12, 1);
      lcd.print("XYM");
      
      for(int i=0;i<5;i++){
        lcd.noDisplay();
        delay(500);
        lcd.display();
        delay(1000);
        }
      lcd.clear(); 
    }
  }
}
