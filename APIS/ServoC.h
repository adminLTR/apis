class ServoC {
  private:
    byte angle;
    Servo servo;
    byte pin;
  public:
    ServoC(int pin) {
      this->pin = pin;
      angle = 20;
    }
    void begin() {
      servo.attach(pin);
      servo.write(20);
    }
    void move(byte angle, int factor) {
      if (factor>0) {
        for (int i=this->angle; i<angle; i++) {
          this->angle = i;
          this->servo.write(i);
          delay(20);
        }
      } else {
        for (int i=this->angle; i>angle; i--) {
          this->angle = i;
          this->servo.write(i);
          delay(20);
        }
      }
    }
};