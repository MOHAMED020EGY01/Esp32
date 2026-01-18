#define LED 2
#default BUTTON 14


bool ledStat = false;
bool beforeStatButton = HIGH;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON , INPUT);
}

void loop() {
int statusButton = digitalRead(BUTTON);

  if(statusButton == LOW && beforeStatButton == HIGH){

    beforeStatButton = !beforeStatButton;
    digitalWrite(LED ,ledStat ? HIGH : LOW );
    delay(200);
  }
  beforeStatButton =  statusButton
}
