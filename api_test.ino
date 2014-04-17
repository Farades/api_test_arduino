/*-----------------------------------------------------
parametr1 - вкл/выкл светодиод
parametr2 - значение потенциометра в пределах [0; 255]
Формат строки:
DID=1;CMD=2;PRM=2;DAT=123
Для включения светодиода:
DID=1;CMD=1;PRM=1;DAT=1
Для выключения светодиода:
DID=1;CMD=1;PRM=1;DAT=0
------------------------------------------------------*/

int led_pin = 13;
int pot_pin = 0;
//значение потеницометра в предыдущий момент времени
int previous_pot_val = 0;
//"чувствительность" потенциометр
int pot_sensitivity = 2;
//Device ID
byte DID = 1;
char DID_in[10];
char CMD_in[10];
char PRM_in[10];
char DAT_in[100];

void setup()
{
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
}

void loop()
{
  int i=0;
  char buffer[100];
  if (Serial.available() > 0)
  {
    delay(100);
    while( Serial.available() && i< 99) 
    {
      buffer[i++] = Serial.read();
    }
    buffer[i++]='\0';
  }
  if(i>0)
  {     
    Serial.println(String(buffer));
    //разбераем его на части отделенные запятой
    sscanf(buffer, "%*c%*c%*c%*c%[^';'];%*c%*c%*c%*c%[^';'];%*c%*c%*c%*c%[^';'];%*c%*c%*c%*c%s",
      &DID_in, &CMD_in, &PRM_in, &DAT_in);
   
    if (((String)DAT_in == "1") && ((String)CMD_in == "1") && ((String)PRM_in == "1")) digitalWrite(led_pin, HIGH);
    if (((String)DAT_in == "0") && ((String)CMD_in == "1") && ((String)PRM_in == "1")) digitalWrite(led_pin, LOW);
    Serial.println(DID_in);   
    Serial.println(CMD_in);
    Serial.println(PRM_in); 
    Serial.println(DAT_in);
  }
  int pot_val = map(analogRead(pot_pin), 0, 1023, 0, 255);
  if (abs(pot_val - previous_pot_val) > pot_sensitivity)
  {
    previous_pot_val = pot_val;
    Serial.print("DID=");
    Serial.print(DID);
    Serial.print(";CMD=2;PRM=2;DAT=");
    Serial.println(pot_val);
  }  
}


