// -----------------
// Read temperature
// -----------------

// Create a variable that will store the temperature value
//First value creates temperature in Celsius, then converts to Fahrenheit

double celtemp = 0.0;

double temperature = 0.0;

void setup()
{
  // Register a Particle variable here
  Particle.variable("temperature", & temperature, DOUBLE);

  // Connect the temperature sensor to A3 and configure it
  // to be an input
  pinMode(A3, INPUT);
}

void loop()
{
  int reading = 0;
  double voltage = 0.0;

  // Keep reading the sensor value so when we make an API
  // call to read its value, we have the latest one
  reading = analogRead(A3);

  // The returned value from the Photon is going to be in the range from 0 to 4095
  // Calculate the voltage from the sensor reading
  voltage = (reading * 3.3) / 4095;

  // Calculate the temperature and update our static variable
  celtemp = (voltage - 0.5) * 100;
  
  // convert temp to Fahrenheir
  temperature = (celtemp *1.8) + 32;
  
  // Google API needs it in a string, so make it a string
  String temp = String(temperature);
  
  // This is the bit that pushes it to Particle, which sends it to IFTTT, which sends it to Google Spreadsheets. No lie. This is it.
  Particle.publish("temperature", temp);
  
  delay(20000);

}