
//---------Stuff that may need changed---------------------------

//This section is dependent on the number of LEDs used.

//pin size is the number of leds used
const int pins_size = 5;

// This will need to be adjusted with the wavelengths of each led
// the first LED at pin A0 has a wavelength of 451.6nm and so on these numbers have to follow the order of the LEDs
float wavelength[pins_size] = {451.6, 570, 588, 641.8, 941};

// Pins will need to be changed in accordance with what pin you use on the arduino
float pins[5] = {A0, A1, A2, A3, A4};

//----------end of stuff that may need changed-------------------


// constants
const int h_size = pins_size + 1;
const float ref_voltage = 5.02;
const float e = 1.6022;
const float c = 2.9979;

// place Holder Variables
float analogDC = 0;
float holder = 0;

// Arrays to help hold data
float voltage[pins_size];
float h[h_size];



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

// calculates plancks constant
  
  for (int i = 0; i < (h_size - 1); i++){
    h[i] = e * voltage[i] * wavelength[i] / c;
  }
  
// averages plancks constant and puts it in an array

  for (int i = 0; i < h_size; i++){
    if (i < h_size - 1){
      holder = holder + h[i];
    }
    else{
      h[i]=holder/i;
    }
  }
  
  for (int i = 0; i < h_size; i++){
    Serial.println(h[i]); 
  }
}
