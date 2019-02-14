#include <LiquidCrystal.h>
const int TEMPERATURE_PIN = 0, BUTTON_PIN = 6, RED_LED = 7, YELLOW_LED = 8, GREEN_LED = 9, BLUE_LED = 10;
int tempRead, tempC, tempF;
boolean currButton = LOW, lightState = LOW;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

boolean debounce(boolean);
void lightUpLED();
void updateLED();
void turnOffLED();

void setup()
{
  //Sets the pinMode for each LED to Output
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  //Begins serial and lcd display
  Serial.begin(9600);
  lcd.begin(16, 2);
}
void loop()
{
  // Reads the temperature and does math to figure out fahrenheit and celsius
  tempRead = analogRead(TEMPERATURE_PIN);
  tempF = (5.0 * tempRead * 100.0) / 1024.0;
  tempC = (tempF - 32) * (5.0 / 9.0);

  //Prints the temperatures to Serial
  Serial.println("Temp:" + (String)tempF + " F");
  Serial.println("Temp:" + (String)tempC + " C");

  // Displays temperature to LCD
  lcd.clear();
  lcd.print("Temp: " + (String)tempF + (char)223 + "F");
  lcd.setCursor(0, 1);
  lcd.print("Temp: " + (String)tempC + (char)223 + "C");

  //Run lightUpLED function
  lightUpLED();
  // Wait 1 second
  delay(1000);
}
/**
   Debounce function in order to remove electrical noise from the circuit
   Provided by Patrick Kelley extended by us
*/
boolean debounce(boolean last)
{
  boolean current = digitalRead(BUTTON_PIN);
  if (last != current)
  {
    delay(5);
    current = digitalRead(BUTTON_PIN);
  }
  return current;
}
void lightUpLED()
{
  // Debounce the button
  currButton = debounce(LOW);
  //If the button was pressed and lights are not on
  if (currButton == HIGH && !lightState)
  {
    // Run the updateLED function and set lightState to on
    updateLED();
    lightState = HIGH;
  }

  // Else if the button was pressed and the lights are on
  else if (currButton == HIGH && lightState)
  {
    // run turnOffLED and set lightstate to low
    turnOffLED();
    lightState = LOW;
  }
  // Else if the lights are on
  else if (lightState)
  {
    // Run the updateLED function
    updateLED();
  }
  // Wait 200 ms
  delay(200);
}
void updateLED()
{
  // If the temp is below 51
  if (tempF <= 50)
  {
    // Turn on Blue
    digitalWrite(BLUE_LED, 63);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }
  // Else if the temperature is between 51 and 78
  else if ( tempF > 50 && tempF <= 78)
  {
    // Turn on Blue and Green
    digitalWrite(BLUE_LED, 63);
    digitalWrite(GREEN_LED, 63);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(RED_LED, LOW);
  }
  // Else if the temp is between 79 and 90
  else if ( tempF > 78 && tempF <= 90)
  {
    // Turn on Blue, Green, and Yellow
    digitalWrite(BLUE_LED, 63);
    digitalWrite(GREEN_LED, 63);
    digitalWrite(YELLOW_LED, 63);
    digitalWrite(RED_LED, LOW);
  }
  // Else turn on all the lights
  else
  {
    digitalWrite(BLUE_LED, 63);
    digitalWrite(GREEN_LED, 63);
    digitalWrite(YELLOW_LED, 63);
    digitalWrite(RED_LED, 63);
  }
}
/**
   Function to set all LED states to LOW
*/
void turnOffLED()
{
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
}
