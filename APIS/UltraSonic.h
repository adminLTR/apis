class UltraSonic {
  private:
    byte echo;
    byte trigger;
    void throwSignal() {
      digitalWrite(trigger, HIGH);
      delay(1);
      digitalWrite(trigger, LOW);
    }
  public:
    UltraSonic(byte echo, byte trigger) {
      this->echo = echo;
      this->trigger = trigger;
    }
    void begin() {
      pinMode(echo, INPUT);
      pinMode(trigger, OUTPUT);
    }
    int getDistance() {
      throwSignal();
      int duration = pulseIn(echo, HIGH);
      int distance = (duration ) / 58.2;
      return distance;
    }
};