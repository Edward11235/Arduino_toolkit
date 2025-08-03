import serial
import time
import sys

try:
    import termios
    import tty
    def getch():
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(fd)
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch
except ImportError:
    # Windows fallback
    import msvcrt
    def getch():
        return msvcrt.getch().decode('utf-8')

PORT = '/dev/ttyUSB0'  # Change to 'COM3', etc. on Windows
BAUD = 115200
PWM_MIN = 1300
PWM_MAX = 1700
PWM_STEP = 20
PWM_STOP = 1500

class KeyboardTeleop:
    def __init__(self, port=PORT, baud=BAUD):
        self.ser = serial.Serial(port, baud, timeout=1)
        time.sleep(2)
        self.pwm = PWM_STOP
        print("Keyboard teleop ready. Press 'w' to speed up, 's' to slow down, 'q' to quit.")
        print(f"Current speed: {self.pwm}")

    def send_pwm(self):
        msg = f"<[{self.pwm}][{self.pwm}][{self.pwm}][{self.pwm}]>"
        self.ser.write(msg.encode())
        # Wait for reply
        reply = self.ser.readline().decode().strip()
        print(f"Sent: {msg} | Received: {reply}")

    def run(self):
        try:
            while True:
                ch = getch()
                if ch == 'w':
                    self.pwm = min(self.pwm + PWM_STEP, PWM_MAX)
                    print(f"Speed up: {self.pwm}")
                    self.send_pwm()
                elif ch == 's':
                    self.pwm = max(self.pwm - PWM_STEP, PWM_MIN)
                    print(f"Speed down: {self.pwm}")
                    self.send_pwm()
                elif ch == 'q':
                    print("Quitting and stopping motors...")
                    self.pwm = PWM_STOP
                    self.send_pwm()
                    break
                else:
                    print("Press 'w' to speed up, 's' to slow down, 'q' to quit.")
        finally:
            self.ser.close()

if __name__ == "__main__":
    teleop = KeyboardTeleop()
    teleop.run() 