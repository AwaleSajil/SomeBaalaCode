
class Motor
{
  bool onState; //is the motor running?
  int motorPin; //the output pin number used for the motor
  unsigned long duration; //time for wgich motor is to be turned on (in milliseconds)
  unsigned long startTime; //time when the motor was started

  public:
    Motor(int motorpin, int duration){
      //constructor for the class
      //duration is sent in secounds
      this->duration = int(duration*1000);
      this->motorPin = motorpin;

      //set the motorPin as output
      pinMode(this->motorPin, OUTPUT);
    }

    void start(){
      if (this->onState == false){
        digitalWrite(this->motorPin, HIGH);  // Start the actuak motor
        this->onState = true;
        this->startTime = millis();
      }
      else{
        //if motor is already running reset the start time
        this->startTime = millis();
      }
    }

    void earlyStop(){
      if (this->onState == true){
        digitalWrite(this->motorPin, LOW);  // Stop the actuak motor
        this->onState = false;
      }
    }

    void Update(){
      //first check if motor is on;
      if (onState){
        //check if the time is up (given duration is finished)
        unsigned long currentTime = millis();
        unsigned long currentDuration = currentTime - this->startTime;
        if (currentDuration > (this->duration)){
          //if time is out stop the motor
          digitalWrite(this->motorPin, LOW);  // Stop the actuak motor
          this->onState = false;
        }
      }
    }
 
};

int angleGrinderPin = 8; //physical pin for signalling motor
int runDuration = 3 * 60;  //in seconds
Motor angleGrinder(angleGrinderPin, runDuration);

void setup() {
//  Serial.begin(9600);
  delay(100);
  angleGrinder.start();
}


void loop() {
  angleGrinder.Update();
}
