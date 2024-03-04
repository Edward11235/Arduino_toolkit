import serial
import time

# Open serial port (adjust '/dev/ttyUSB0' as necessary for your setup)
ser = serial.Serial('/dev/ttyUSB0', 9600)
time.sleep(2)  # Wait for the connection to initialize

try:
    while True:
        num = input("Enter an integer: ")
        message = f"<{num}>"  # Enclose the integer in delimiters
        ser.write(message.encode())  # Send the delimited message
        
        # Wait for and read the response from Arduino
        while ser.in_waiting == 0:
            pass  # Wait until there is data to read
        received_line = ser.readline().decode().strip()  # Read the response
        print("Received back:", received_line)  # Print the received response

except KeyboardInterrupt:
    ser.close()  # Close the serial connection gracefully
