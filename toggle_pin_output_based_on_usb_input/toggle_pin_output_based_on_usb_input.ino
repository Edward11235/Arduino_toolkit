String inputString = "";  // A String to hold incoming data
boolean stringComplete = false;  // Whether the string is complete

void setup() {
  Serial.begin(9600);  // Start serial communication at 9600 baud
  pinMode(13, OUTPUT);  // Set pin 13 as OUTPUT
}

void loop() {
  while (Serial.available()) {
    // Get the new byte:
    char inChar = (char)Serial.read();
    // Add it to the inputString:
    inputString += inChar;
    // If the incoming character is the end delimiter, set stringComplete:
    if (inChar == '>') {
      stringComplete = true;
    }
  }

  if (stringComplete) {
    // Look for the start ('<') and end ('>') delimiters
    int startIndex = inputString.indexOf('<');
    int endIndex = inputString.lastIndexOf('>'); // Use lastIndexOf in case of multiple messages

    // If both delimiters are found, parse the integer
    if (startIndex >= 0 && endIndex > startIndex) {
      String numberString = inputString.substring(startIndex + 1, endIndex);
      int number = numberString.toInt();

      // Echo the received number back
      Serial.println(number);

      // Decide whether to set the pin HIGH or LOW based on the received value
      if (number > 10) {
        digitalWrite(13, HIGH);
      } else {
        digitalWrite(13, LOW);
      }

      // Clear the inputString for the next message
      inputString = "";
    }
    stringComplete = false;  // Reset the flag for the next message
  }
}
