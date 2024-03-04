String inputString = "";      // A String to hold incoming data
boolean stringComplete = false;  // Whether the string is complete

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  if (stringComplete) {
    if (inputString.startsWith("<[") && inputString.endsWith("]>")) {
      // Extract and parse the integers
      int nums[4]; // Array to hold the parsed integers
      int startIdx = 2; // Start after "<["
      for (int i = 0; i < 4; i++) {
        int endIdx = inputString.indexOf("]", startIdx);
        if (endIdx != -1) {
          nums[i] = inputString.substring(startIdx, endIdx).toInt();
          startIdx = endIdx + 2; // Move past the "]" and to the start of the next number
        }
      }

      // Echo the numbers back
      Serial.print("<[");
      for (int i = 0; i < 4; i++) {
        Serial.print(nums[i]);
        if (i < 3) Serial.print("][");
      }
      Serial.println("]>");

      // Reset the input string and the complete flag
      inputString = "";
      stringComplete = false;
    }
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '>') {
      stringComplete = true;
    }
  }
}
