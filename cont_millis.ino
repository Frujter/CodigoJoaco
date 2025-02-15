int preMillis = 0,cont = 0; 
void setup() {
  Serial.begin(115200);              
}

void loop() {
  int Millis1 = millis();  
  if (Millis1 - preMillis >= 1000) {
    preMillis = Millis1;

    cont++;

    
    Serial.println(cont);
  }

  
}
