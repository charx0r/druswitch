char buffer[18];
int red, green, blue;
int LivingLight = 11;
int SecurityLight = 6;
int BedroomLight = 3;

void setup() 
{ 
  Serial.begin(9600);
  Serial.flush();
  pinMode(LivingLight, OUTPUT);
  pinMode(SecurityLight, OUTPUT);
  pinMode(BedroomLight, OUTPUT);
} 

void loop() { 
  if (Serial.available() > 0) {
  int index=0;
  delay(100); // let the buffer fill up
  int numChar = Serial.available();
    if (numChar>15) {
      numChar=15;
    }
    while (numChar--) {
      buffer[index++] = Serial.read();
    }
    Serial.print("DEBUG Buffer is: ");
    Serial.println(buffer);
    splitString(buffer);
  }
}

void splitString(char* data) {
  Serial.print("Data sent to Arduino: ");
  Serial.println(data);
  char* parameter; 
  parameter = strtok (data, " ,");
  while (parameter != NULL) {
    setLED(parameter);
    parameter = strtok (NULL, " ,");
  }

// Clear the text and serial buffers
  for (int x=0; x<16; x++) {
    buffer[x]='\0';
  }
  Serial.flush();
}
void setLED(char* data) {
  if ((data[0] == 'r') || (data[0] == 'R')) {
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,255);

    analogWrite(LivingLight, Ans);
Serial.print("Living room lights luminosity is set to: ");
    Serial.println(Ans);
  }

  if ((data[0] == 'g') || (data[0] == 'G')) {
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,255);
    analogWrite(SecurityLight, Ans);
    Serial.print("Security lights luminosity is set to: ");
    Serial.println(Ans);
  }

  if ((data[0] == 'b') || (data[0] == 'B')) {
    int Ans = strtol(data+1, NULL, 10);
    Ans = constrain(Ans,0,255);
    analogWrite(BedroomLight, Ans);
    Serial.print("Bedroom lights luminosity is set to: ");
    Serial.println(Ans);
  }
}
