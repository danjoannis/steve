/*
 * STEVE - Self-Training Electronic Vehicle for Exploration
 * 
 * steve_io : Hardware controller over serial
 * 
 * Allows for the control of STEVE's motors and peripherals,
 * as well as measurement and sampling of various sensors.
 */

// Motors
#define MOTOR_EN1 PD0
#define MOTOR_EN2 PD1
#define MOTOR_A1 PD2
#define MOTOR_B1 PD3
#define MOTOR_A2 PD4
#define MOTOR_B2 PD5

#define NEUTRAL 0
#define FORWARD 1
#define REVERSE 2
#define BRAKE  3
#define CENTRE  0
#define LEFT  1
#define RIGHT   2

// Ultrasonic rangefinder
#define US_TRIG PD6
#define US_ECHO PD7
#define US_TIMEOUT 0xffff
#define US_NO_OBSTACLE 0xfffe

// IMU
#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C
 
#define    GYRO_FULL_SCALE_250_DPS    0x00  
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18
 
#define    ACC_FULL_SCALE_2_G        0x00  
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

////////////////////////////////////////////////////////

#include <Wire.h>

////////////////////////////////////////////////////////

volatile unsigned char data_in[8];
volatile unsigned char command_in[8];

volatile unsigned char data_count;
volatile unsigned char command_ready;

////////////////////////////////////////////////////////

void setup() {

  // Initialize communications
  Wire.begin();
  Serial.begin(115200);

  // Initialize pins
  motors_init();
  us_init();
  MPU_init();

  // Serial welcome
  Serial.print("Hello. My name is STEVE. \r\n");
}

void loop() {
  if (Serial.available() > 0)
  {
    // Get data from the USART in register
    command_in[data_count] = Serial.read();
  
    // End of line!
    if (command_in[data_count] == '\r')
    {
      command_ready = true;
      // Reset to 0, ready to go again
      data_count = 0;
    }
    else
    {
      data_count++;
    }
  }
  
  if (command_ready == true)
  {
    //copy_command();
    process_command();
    
    command_ready = false;
  }
}

////////////////////////////////////////////////////////

/*
 * Functions
 * 
 * All of the functions are defined below.
 * 
 */

void process_command()
{
  switch (command_in[0])
  {
  case 'D':               // Drive command
    if (command_in[1] == '=')
    {
      motors_go_tank(command_in[2], command_in[3], command_in[4], command_in[5]);
    }
    else if (command_in[1] == '?')
    {
      // Do the query action for D
      Serial.print("Drive\r\n");
    }
    else if (command_in[1] == 'B')
    {
      delay(4000);
      motors_go_tank(FORWARD,LEFT,100,100);
    }
    break;
  case 'Q':               // Query command
    if (command_in[1] == '?')
    {
      if (command_in[2] == 'U')   // Ultrasonic range finder
      {
        uint16_t result = us_measure();
        Serial.print(String(result/58));
        Serial.print("\r\n");
      }
      else if (command_in[2] == 'M')  // Magnetometer
      {
        Serial.print("Trig Compass");
        MPU_read();
        Serial.print("Read Compass");
        Serial.print("Done");
      }
    }
    break;
  case 'A':               // Sample command
    if (command_in[1] == '?')
    {
      // Do the query action for R
      Serial.print("Name .:. A=\r\n");
    }
    else if (command_in[1] == '=')
    {
      // Do the set action for A
    }
    break;
  default:
    Serial.print("CMD Error\r\n");
    break;
  }
}

void us_init()
{
  pinMode(US_TRIG, OUTPUT);
  pinMode(US_ECHO, INPUT);
}

uint16_t us_measure()
{
  uint32_t i,result;

  //Send the trigger
  digitalWrite(US_TRIG, HIGH);
  delayMicroseconds(15);
  digitalWrite(US_TRIG, LOW);
  delayMicroseconds(20);

  //Wait for the rising edge
  for(i=0;i<600000;i++)
  {
    if(!digitalRead(US_ECHO)) continue; else break;
  }

  if(i==600000)
    return US_TIMEOUT;  //Indicates time out

  //High Edge Found

  //Setup Timer1
  TCCR1A=0X00;
  TCCR1B=(1<<CS11); //Prescaler = Fcpu/8
  TCNT1=0x00;     //Init counter

  //Now wait for the falling edge
  for(i=0;i<600000;i++)
  {
    if(digitalRead(US_ECHO))
    {
      if(TCNT1 > 60000) break; else continue;
    }
    else
      break;
  }

  if(i==600000)
    return US_TIMEOUT;  //Indicates time out

  //Falling edge found

  result=TCNT1;

  //Stop Timer
  TCCR1B=0x00;

  if(result > 60000)
    return US_NO_OBSTACLE;  //No obstacle
  else
    return (result>>1);
}

void motors_init()
{
  // Configure outputs
  pinMode(MOTOR_EN1, OUTPUT);
  pinMode(MOTOR_EN2, OUTPUT);
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);

  // Set all low
  digitalWrite(MOTOR_EN1, LOW);
  digitalWrite(MOTOR_EN2, LOW);
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B2, LOW);
}

void motors_go_tank(byte direction, byte heading, byte duty, double distance)
{
  // Todo: Not be lazy and actually implement PWM

  //Forward: MOTOR_A = HIGH, MOTOR_B = LOW
  //Reverse: MOTOR_A = LOW, MOTOR_B = HIGH
  //Brake: MOTOR_A = MOTOR_B

  byte left_duty = 128;
  byte right_duty = 128;

  double delay_on = ((double)duty / 100) * 500;     // Sets the on-time for the motor
  double delay_off = (500 - delay_on);              // Sets the off-time for the motor

  if (direction == FORWARD)
  {
    digitalWrite(MOTOR_A1, HIGH);
    digitalWrite(MOTOR_A2, HIGH);
  }
  else if (direction == REVERSE)
  {    
    digitalWrite(MOTOR_B1, HIGH);
    digitalWrite(MOTOR_B2, HIGH);
  }
  else if (direction == NEUTRAL)
  {
    // No forward, only pivot
  }
  else if (direction == BRAKE)
  {    
    digitalWrite(MOTOR_A1, HIGH);
    digitalWrite(MOTOR_A2, HIGH);
    digitalWrite(MOTOR_B1, HIGH);
    digitalWrite(MOTOR_B2, HIGH);
  }

  while (distance > 0)
  {
    analogWrite(MOTOR_EN1, 255);
    analogWrite(MOTOR_EN2, 255);
    distance--;
  }
}

// This function read Nbytes bytes from I2C device at address Address. 
// Put read bytes starting at register Register in the Data array. 
void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();
 
  // Read Nbytes
  Wire.requestFrom(Address, Nbytes); 
  uint8_t index=0;
  while (Wire.available())
    Data[index++]=Wire.read();
}
 
// Write a byte (Data) in device (Address) at register (Register)
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

void MPU_init()
{
  // Configure gyroscope range
  I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_2000_DPS);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_16_G);
  // Set by pass mode for the magnetometers
  I2CwriteByte(MPU9250_ADDRESS,0x37,0x02);
 
  // Request first magnetometer single measurement
  I2CwriteByte(MAG_ADDRESS,0x0A,0x01);
}

void MPU_read()
{
  // Read accelerometer and gyroscope
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS,0x3B,14,Buf);
 
  // Create 16 bits values from 8 bits data
  // Accelerometer
  int16_t ax=-(Buf[0]<<8 | Buf[1]);
  int16_t ay=-(Buf[2]<<8 | Buf[3]);
  int16_t az=Buf[4]<<8 | Buf[5];
 
  // Gyroscope
  int16_t gx=-(Buf[8]<<8 | Buf[9]);
  int16_t gy=-(Buf[10]<<8 | Buf[11]);
  int16_t gz=Buf[12]<<8 | Buf[13];
 
  // Display values 
  // Accelerometer
  Serial.print (ax,DEC); 
  Serial.print ("\t");
  Serial.print (ay,DEC);
  Serial.print ("\t");
  Serial.print (az,DEC);  
  Serial.print ("\t");
 
  // Gyroscope
  Serial.print (gx,DEC); 
  Serial.print ("\t");
  Serial.print (gy,DEC);
  Serial.print ("\t");
  Serial.print (gz,DEC);  
  Serial.print ("\t");

  // :::  Magnetometer ::: 
  // Read register Status 1 and wait for the DRDY: Data Ready
  uint8_t ST1;
  do
  {
    I2Cread(MAG_ADDRESS,0x02,1,&ST1);
  }
  while (!(ST1&0x01));
 
  // Read magnetometer data  
  uint8_t Mag[7];  
  I2Cread(MAG_ADDRESS,0x03,7,Mag);
  
  // Create 16 bits values from 8 bits data
  // Magnetometer
  int16_t mx=-(Mag[3]<<8 | Mag[2]);
  int16_t my=-(Mag[1]<<8 | Mag[0]);
  int16_t mz=-(Mag[5]<<8 | Mag[4]);
  
  // Magnetometer
  Serial.print (mx+200,DEC); 
  Serial.print ("\t");
  Serial.print (my-70,DEC);
  Serial.print ("\t");
  Serial.print (mz-700,DEC);  
  Serial.print ("\t");
  
  // End of line
  Serial.println("");
}
