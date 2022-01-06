// Be sure to adjust the sizes of these arrays when adjusting the number of LEDs being used.
// Pins
float pins[5] = {A0, A1, A2, A3, A4};
const int pins_size = 5;
// place Holder Variables
float analogDC = 0;
float voltage[5] = {0, 0, 0, 0, 0,};
const int voltage_size = 5;
float h[6] = {0, 0, 0, 0, 0, 0};
const int h_size = 6;
// constants
float ref_voltage = 5.02;
float e = 1.6022;
float c = 2.9979;
float wavelength[5] = {451.6, 570, 588, 641.8, 941};
const int wavelength_size = 5;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600); //Opens Serial port
}
void loop() {
  // Turns on the circuit and charges the capacitors
  for (int i = 0; i < pins_size; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], HIGH);
  } 
  //charge delay
  delay(5000);
  for (int i = 0; i < pins_size; i++) {
    digitalWrite(pins[i], LOW);
    pinMode(pins[i], INPUT);
  } 
  for (int i = 0; i < 2; i++){
    // voltage sensor section
    // note: the input pins and the voltage arrays have the same size

    for (int j = 0; j < pins_size; j++){
      analogDC = analogRead(pins[j]);
      voltage[j] = (analogDC * ref_voltage) / 1024;
      if (j < (pins_size -1)){
        Serial.print(voltage[j]);
        Serial.print("\t");
      }
      else{
        Serial.println(voltage[j]);
      }
    }
    delay(900);
  }
  for (int i = 0; i < (h_size - 1); i++){
    h[i] = e * voltage[i] * wavelength[i] / c;
  }
  // This is not the best implimentation 
  // if the number of leds change this part also needs changed accordingly
  h[h_size-1] = (h[0] + h[1] + h[2] + h[3] + h[4])/(h_size-1);
  
  for (int i = 0; i < h_size; i++){
    Serial.println(h[i]); 
  }
}
