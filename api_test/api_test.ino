/*-----------------------------------------------------
parametr1 - вкл/выкл светодиод
parametr2 - значение потенциометра в пределах [0; 255]
------------------------------------------------------*/

int led_pin = 13;
int pot_pin = 0;
//значение потеницометра в предыдущий момент времени
int previous_pot_val = 0;
//"чувствительность" потенциометр
int pot_sensitivity = 2;
//Device ID
byte DID = 1;

void setup()
{
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
}

void loop()
{
  if (Serial.available() > 0)
  {
    int read_val = Serial.read() - '0';
    if (read_val == 1)
    {
      digitalWrite(led_pin, HIGH);
      Serial.print("DID=");
      Serial.print(DID);
      Serial.println(";parameter=2;value=1");
    }
    else if (read_val == 0)
    {
      digitalWrite(led_pin, LOW);
      Serial.print("DID=");
      Serial.print(DID);
      Serial.println(";parameter=2;value=0");
    }
  }
  int pot_val = map(analogRead(pot_pin), 0, 1023, 0, 255);
  if (abs(pot_val - previous_pot_val) > pot_sensitivity)
  {
    previous_pot_val = pot_val;
    Serial.print("DID=");
    Serial.print(DID);
    Serial.print(";parameter=1;value=");
    Serial.println(pot_val);
  }  
}


