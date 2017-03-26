//servo library
#include <Servo.h>

//initialize all the servos
Servo right_ankle;
Servo left_ankle;
Servo right_hip;
Servo left_hip;
Servo right_shoulder;
Servo left_shoulder;
Servo right_arm;
Servo left_arm;
Servo waist;
Servo right_elbow;
Servo left_elbow;

//initial position
int right_ankle_pos = 67;
int left_ankle_pos = 121;
int right_hip_pos = 84;
int left_hip_pos = 78;
int right_shoulder_pos = 130;
int left_shoulder_pos = 65;
int right_arm_pos = 0;
int left_arm_pos = 175;
int waist_pos = 75;
int right_elbow_pos = 87;
int left_elbow_pos = 65;

//configurations
int x = 12;//18        //forward walk step length
int walk_delay = 18;   //forward walk speed (high->slow)
int y = 15;            //sideways move config
int dance_delay = 10;  //sideways move speed
int z = 20;            //punch config
int punch_delay = 7;   //punch speed
int p = 79;            //get up config
int b_x = 12;          //backward walk step length
int b_walk_delay =18;  //backwards walk speed (high->slow)
int turn_delay = 18;   //turning speed

char byterebut=0;
bool b_end_right;
bool right_front=false;

void setup()
{
  //servo attachments
  right_ankle.attach(A0);
  left_ankle.attach(A1);
  right_hip.attach(A2);
  left_hip.attach(A3);
  right_shoulder.attach(11);
  left_shoulder.attach(10);
  right_arm.attach(12);
  left_arm.attach(3);
  waist.attach(A4);
  right_elbow.attach(13);
  left_elbow.attach(2);

  //movw servos to initial position
  move_servos();

  //Bluetooth setup
  Serial.begin(9600);
  delay(1000);

}

void loop()
{
  waist_pos = 75; //waist pos correction
  while (Serial.available() <= 0);  
  byterebut=Serial.read();
  switch (byterebut) {          
     case 50: //walk
         walk();         
         break;      
     case 51: //move left
         while (byterebut != 61){
            if (Serial.available() > 0) {
            byterebut=Serial.read();
            }
            go_left();
         }
         break;      
     case 52: //move right
         while (byterebut != 62){
            if (Serial.available() > 0) {
            byterebut=Serial.read();
            }
            go_right();
         }
         break;         
     case 53: //move backwards
         walk_backwards();
         break;        
     case 54: //right turn
         while (byterebut != 64){
            if (Serial.available() > 0) {
            byterebut=Serial.read();
            }
            turn_right();
         }
         break;    
     case 55: //left turn
         while (byterebut != 65){
            if (Serial.available() > 0) {
            byterebut=Serial.read();
            }
            turn_left();
         }
         break;     
     case 56:
         right_punch();
         break;
     
     case 57:
         left_punch();
         break;

     case 58:
         right_swing();
         break;

     case 59:
         left_swing();
         break;

     case 66:
         get_up();
         break;

     case 67:
         //front_get_up();();
         break;
  }
}

void walk(void) {
  if (right_front) {
    half_step_left_leg();
    right_front=false;
  } else {
    half_step_right_leg();
    right_front=true;
  }
  if (Serial.available() > 0) {
        byterebut=Serial.read();
  }
  while (byterebut != 60){
    if (right_front) {
      if (Serial.available() > 0) {
        byterebut=Serial.read();
      }
      step_left_leg();
      right_front = false;
    } else {
      if (Serial.available() > 0) {
        byterebut=Serial.read();
      }
      step_right_leg();
      right_front = true;
    }
  }
}

void turn_right(void) {
    for (int pos = 1; pos < 10; pos++) { 
    right_ankle_pos++;
    left_ankle_pos += 2;
    right_hip_pos --;
    left_hip_pos --;
    waist_pos ++;
    move_servos();
    delay(turn_delay);
  }
  delay(80);
  for (int pos = 1; pos < 10; pos++) { 
    right_ankle_pos--;
    left_ankle_pos -= 2;
    waist_pos --;
    move_servos();
    delay(turn_delay);
  }
  delay(80);
  for (int pos = 1; pos < 10; pos++) { 
    right_ankle_pos -=2;
    left_ankle_pos --;
    right_hip_pos ++;
    left_hip_pos --;
    move_servos();
    delay(turn_delay);
  }
  delay(80);
  for (int pos = 1; pos < 10; pos++) { 
    right_ankle_pos +=2;
    left_ankle_pos ++;
    move_servos();
    delay(turn_delay);
  }
  for (int pos = 1; pos < 10; pos++) {
    right_ankle_pos ++;
    left_ankle_pos +=2;
    left_hip_pos ++;
    move_servos();
    delay(turn_delay);
  }
  for (int pos = 1; pos < 10; pos++) { 
    right_ankle_pos --;
    left_ankle_pos -=2;
    left_hip_pos ++;
    move_servos();
    delay(turn_delay);
  }
  if (Serial.available() > 0) {
    byterebut=Serial.read();
  }
}

void turn_left(void) {
    for (int pos = 1; pos < 9; pos++) {
    right_ankle_pos -=2;
    left_ankle_pos --;
    right_hip_pos ++;
    left_hip_pos ++;
    waist_pos ++;
    move_servos();
    delay(turn_delay);
  }
  delay(80);
  for (int pos = 1; pos < 9; pos++) { 
    right_ankle_pos +=2;
    left_ankle_pos ++;
    waist_pos --;
    move_servos();
    delay(turn_delay);
  }
  delay(80);
  for (int pos = 1; pos < 9; pos++) { 
    right_ankle_pos ++;
    left_ankle_pos +=2;
    right_hip_pos ++;
    left_hip_pos --;
    move_servos();
    delay(turn_delay);
  }
  delay(80);
  for (int pos = 1; pos < 9; pos++) { 
    right_ankle_pos --;
    left_ankle_pos -=2;
    move_servos();
    delay(turn_delay);
  }
  for (int pos = 1; pos < 9; pos++) {
    right_ankle_pos -=2;
    left_ankle_pos --;
    right_hip_pos --;
    move_servos();
    delay(turn_delay);
  }
  for (int pos = 1; pos < 9; pos++) { 
    right_ankle_pos +=2;
    left_ankle_pos ++;
    right_hip_pos --;
    move_servos();
    delay(turn_delay);
  }
  if (Serial.available() > 0) {
    byterebut=Serial.read();
  }
}

void right_swing (void) {
  for (int pos = 1; pos < 20; pos++) {
    right_arm_pos +=8;
    left_arm_pos -=5;
    right_ankle_pos ++;
    left_ankle_pos +=2;
    move_servos();
    delay(15);
  }
  delay(200);
  for (int pos = 1; pos < 20; pos++) {
    right_arm_pos -=8;
    left_arm_pos +=5;
    right_ankle_pos --;
    left_ankle_pos -=2;
    move_servos();
    delay(25);
  }
}

void left_swing (void) {
  for (int pos = 1; pos < 20; pos++) {
    left_arm_pos -=8;
    right_arm_pos +=5;
    right_ankle_pos -=2;
    left_ankle_pos --;
    move_servos();
    delay(15);
  }
  delay(200);
  for (int pos = 1; pos < 20; pos++) {
    left_arm_pos +=8;
    right_arm_pos -=5;
    right_ankle_pos +=2;
    left_ankle_pos ++;
    move_servos();
    delay(25);
  }
}

void get_up(void) {
  for (int i=0; i<120; i++) {  
    right_arm_pos ++;
    left_arm_pos --;
    if(i<13)
    right_elbow_pos -=3;
    if(i<13)
    left_elbow_pos +=2;
    move_servos();
    delay(1);
  }
  for (int i=0; i<120; i++) { 
    right_shoulder_pos --;
    left_shoulder_pos ++;
    move_servos();
    delay(1);
  }
  for (int i=0; i<80; i++)  { 
    right_ankle_pos ++;
    left_ankle_pos --;
    move_servos();
    delay(1);
  } // right_ankle +80 // left_ankle -80
  for (int i=0; i<85; i++) {  
    right_hip_pos ++;
    if (i<45)
      left_hip_pos ++;
    move_servos();
    delay(1);
  }
    for (int i=0; i<120; i++) { 
    right_arm_pos --;
    left_arm_pos ++;
    move_servos();
    delay(10);
  } 
  for (int i=0; i<60; i++) { 
    right_shoulder_pos ++;
    left_shoulder_pos --;
    move_servos();
    delay(10);
  }
  for (int i=0; i<30; i++) {
    right_ankle_pos --;
    move_servos();
    delay(10);
  }
  for (int i=0; i<70; i++) {
    right_shoulder_pos +=2;
    if (i>50)
     right_ankle_pos --;
    waist_pos +=2;
    if(i<50)  
     left_elbow_pos --;
    if(i>10)
     left_arm_pos -=2;
    left_shoulder_pos +=1;
    move_servos();
    delay(8);
  }
  delay(2000);
  for (int i=0; i<50; i++) {
    if(i>15)
      left_elbow_pos +=2;
    left_shoulder_pos -=3;
  // left_arm_pos -=2;
    move_servos();
    delay(10);
  }
  for (int i=0; i<70; i++) {
    left_arm_pos +=1;  
    move_servos();
    delay(10);
  }
  delay(200);
  for (int i=0; i<85; i++) {
    if(i>25)
    right_ankle_pos --; 
    if(i<80)
    left_ankle_pos ++; 
    right_hip_pos --;
    if(i>40)
    left_hip_pos --;
    move_servos();
    delay(15);
  }
  right_ankle_pos = 67;
 left_ankle_pos = 121;
 right_hip_pos = 84;
 left_hip_pos = 78;
 right_shoulder_pos = 130;
 left_shoulder_pos = 65;
 right_arm_pos = 0;
 left_arm_pos = 175;
 waist_pos = 75;
 right_elbow_pos = 87;
 left_elbow_pos = 65;
 move_servos();
}


void walk_backwards(void) {
  if (right_front) {
    b_half_step_right_leg();
    right_front = false;
  } else {
    b_half_step_left_leg();
    right_front=true;
  }
  if (Serial.available() > 0) {
      byterebut=Serial.read();
      }
  while (byterebut != 63){
    if (right_front) {
      if (Serial.available() > 0) {
      byterebut=Serial.read();
      }
      b_step_right_leg();
      right_front=false;
    } else {
      if (Serial.available() > 0) {
      byterebut=Serial.read();
      }
      b_step_left_leg();
      right_front=true;
    }  
  }
}

void right_punch(void) {
  for (int i=0; i<z; i++) {
    waist_pos --;
    move_servos();
    delay(punch_delay);
  }
  for (int i=0; i<z+10; i++) {
    waist_pos +=7;
    right_shoulder_pos +=5;
    if (i>5)
      right_arm_pos +=5;
    right_elbow_pos --;
    move_servos();
    delay(punch_delay);
  }
  delay(300);
  for (int i=0; i<z+10; i++) {
    if (i<27)
      waist_pos -=7;
    right_shoulder_pos -=5;
    if (i>5)
      right_arm_pos -=5;
    right_elbow_pos ++;
    move_servos();
    delay(punch_delay);
  }
  waist_pos -=1;
  move_servos();
}

void left_punch(void) {
  for (int i=0; i<z; i++) {
    waist_pos ++;
    move_servos();
    delay(punch_delay);
  }
  for (int i=0; i<z+10; i++) {
    waist_pos -=7;
    left_shoulder_pos -=5;
    if(i>=10)
      left_arm_pos -=5;
    move_servos();
    delay(punch_delay);
  }
  delay(300);
  for (int i=0; i<z+10; i++) {
    if (i<27)
      waist_pos +=7;
    left_shoulder_pos +=5;
    if(i<20)
      left_arm_pos +=5;
    move_servos();
    delay(punch_delay);
  }
  waist_pos +=1;
  move_servos();
}

void go_left(void) {
  for (int i=0; i<y; i++) {
    right_ankle_pos --;
    move_servos();
    delay(dance_delay);
  }
  for (int i=0; i<y; i++) {
    right_ankle_pos --;
    left_ankle_pos ++;
    move_servos();
    delay(dance_delay);
  }
  for (int i=0; i<y; i++) {
    right_ankle_pos ++;
    left_ankle_pos ++;
    move_servos();
    delay(dance_delay);
  }
  for (int i=0; i<y; i++) {
    right_ankle_pos ++;
    left_ankle_pos --;
    move_servos();
    delay(dance_delay);
  }
  for (int i=0; i<y; i++) {
    left_ankle_pos --;
    move_servos();
    delay(dance_delay);
  }
  if (Serial.available() > 0) {
    byterebut=Serial.read();
  }
}

void go_right(void) {
  for (int i=0; i<y; i++) {
    left_ankle_pos ++;
    move_servos();
    delay(dance_delay);
  }
  for (int i=0; i<y; i++) {
    right_ankle_pos --;
    left_ankle_pos ++;
    move_servos();
    delay(dance_delay);
  }
  for (int i=0; i<y; i++) {
    right_ankle_pos --;
    left_ankle_pos --;
    move_servos();
    delay(dance_delay);
  }
  for (int i=0; i<y; i++) {
    right_ankle_pos ++;
    left_ankle_pos --;
    move_servos();
    delay(dance_delay);
  }
  for (int i=0; i<y; i++) {
    right_ankle_pos ++;
    move_servos();
    delay(dance_delay);
  }
  if (Serial.available() > 0) {
    byterebut=Serial.read();
  }
}

void move_servos(void) {
  right_ankle.write(right_ankle_pos);
  left_ankle.write(left_ankle_pos);
  right_hip.write(right_hip_pos);
  left_hip.write(left_hip_pos);
  right_shoulder.write(right_shoulder_pos);
  left_shoulder.write(left_shoulder_pos);
  right_arm.write(right_arm_pos);
  left_arm.write(left_arm_pos);
  waist.write(waist_pos);
  right_elbow.write(right_elbow_pos);
  left_elbow.write(left_elbow_pos);
}

//***********************************************************************************************
//******  WALK  *********************************************************************************
//***********************************************************************************************
void half_step_left_leg(void){
  for (int pos = 1; pos < x; pos++) { 
    right_ankle_pos++;
    left_ankle_pos += 2;
    right_hip_pos -=2;//--;
    left_hip_pos -=2;//--;
    waist_pos ++;
    right_shoulder_pos ++;
    left_shoulder_pos ++;
    move_servos();
    delay(walk_delay);
  }
  for (int pos = 1; pos < x; pos++) { 
    right_ankle_pos--;
    left_ankle_pos -= 2;
    waist_pos --;
    right_shoulder_pos --;
    left_shoulder_pos --;
    move_servos();
    delay(walk_delay);
  }
}


void half_step_right_leg(void){
  for (int pos = 1; pos < x; pos++) { 
    right_ankle_pos-=2;
    left_ankle_pos --;
    right_hip_pos +=2;//++;
    left_hip_pos +=2;//++;
    waist_pos --;
    right_shoulder_pos --;
    left_shoulder_pos --;
    move_servos();
    delay(walk_delay);
  }
  for (int pos = 1; pos < x; pos++) { 
    right_ankle_pos+=2;
    left_ankle_pos ++;
    waist_pos ++;
    right_shoulder_pos ++;
    left_shoulder_pos ++;
    move_servos();
    delay(walk_delay);
  }
}

void step_right_leg(void){
  for (int pos = 1; pos < x; pos++) { 
    right_ankle_pos -= 2;
    left_ankle_pos --;
    right_hip_pos +=2;//++;
    left_hip_pos +=2;//++;
    waist_pos --;
    left_shoulder_pos -=1;
    right_shoulder_pos -=1;
    move_servos();
    delay(walk_delay);
  }
  for (int pos = 1; pos < x; pos++) {
    right_hip_pos +=2;//++;
    left_hip_pos +=2;//++;
    if(pos < (x/2)) {
      waist_pos --;
      left_shoulder_pos -=1;
      right_shoulder_pos -=1;
    } else {
      waist_pos ++;
      left_shoulder_pos +=1;
      right_shoulder_pos +=1;
    }
    move_servos();
    delay(walk_delay);
  }
  for (int pos = 1; pos < x; pos++) { 
    right_ankle_pos += 2;
    left_ankle_pos ++;
    waist_pos ++;
    left_shoulder_pos +=1;
    right_shoulder_pos +=1;
    move_servos();
    delay(walk_delay);
  }
}

void step_left_leg(void){
  for (int pos = 1; pos < x; pos++) { 
    right_ankle_pos ++;
    left_ankle_pos +=2;
    right_hip_pos -=2;//--;
    left_hip_pos -=2;//--;
    waist_pos ++;
    right_shoulder_pos +=1;
    left_shoulder_pos +=1;
    move_servos();
    delay(walk_delay);
  }
  for (int pos = 1; pos < x; pos++) {
    right_hip_pos -=2;//--;
    left_hip_pos -=2;//--;
    if(pos < (x/2)) {
      waist_pos ++;
      right_shoulder_pos +=1;
      left_shoulder_pos +=1;
    } else {
      waist_pos --;
      right_shoulder_pos -=1;
      left_shoulder_pos -=1;
    }
    move_servos();
    delay(walk_delay);
  }
  for (int pos = 1; pos < x; pos++) { 
    right_ankle_pos --;
    left_ankle_pos -=2;
    waist_pos --;
    right_shoulder_pos -=1;
    left_shoulder_pos -=1;
    move_servos();
    delay(walk_delay);
  }
}
//***********************************************************************************************
//******  BACKWARDS WALK  ***********************************************************************
//***********************************************************************************************
void b_half_step_left_leg(void){
  for (int pos = 1; pos < b_x; pos++) { 
    right_ankle_pos++;
    left_ankle_pos += 2;
    right_hip_pos ++;
    left_hip_pos ++;
    waist_pos ++;
    right_shoulder_pos -=1;
    left_shoulder_pos -=1;
    move_servos();
    delay(b_walk_delay);
  }
  for (int pos = 1; pos < b_x; pos++) { 
    right_ankle_pos --;
    left_ankle_pos -=2;
    waist_pos --;
    right_shoulder_pos +=1;
    left_shoulder_pos +=1;
    move_servos();
    delay(b_walk_delay);
  }
}


void b_half_step_right_leg(void){
  for (int pos = 1; pos < b_x; pos++) {
    right_ankle_pos-=2;
    left_ankle_pos --;
    right_hip_pos --;
    left_hip_pos --;
    waist_pos ++;
    right_shoulder_pos +=1;
    left_shoulder_pos +=1;
    move_servos();
    delay(b_walk_delay);
  }
  for (int pos = 1; pos < b_x; pos++) { 
    right_ankle_pos+=2;
    left_ankle_pos ++;
    waist_pos --;
    right_shoulder_pos -=1;
    left_shoulder_pos -=1;
    move_servos();
    delay(b_walk_delay);
  }
}

void b_step_right_leg(void){
  for (int pos = 1; pos < b_x; pos++) { 
    right_ankle_pos -=2;
    left_ankle_pos --;
    right_hip_pos --;
    left_hip_pos --;
    waist_pos ++;
    left_shoulder_pos +=1;
    right_shoulder_pos +=1;
    move_servos();
    delay(b_walk_delay);
  }
  for (int pos = 1; pos < b_x; pos++) { 
    right_hip_pos --;
    left_hip_pos --;
    if(pos < (x/2)) {
      waist_pos ++;
      left_shoulder_pos +=1;
      right_shoulder_pos +=1;
    } else {
      waist_pos --;
      left_shoulder_pos -=1;
      right_shoulder_pos -=1;
    }
    move_servos();
    delay(b_walk_delay);
  }
  for (int pos = 1; pos < b_x; pos++) { 
    right_ankle_pos += 2;
    left_ankle_pos ++;
    waist_pos --;
    left_shoulder_pos -=1;
    right_shoulder_pos -=1;
    move_servos();
    delay(b_walk_delay);
  }
}

void b_step_left_leg(void){
  for (int pos = 1; pos < b_x; pos++) { 
    right_ankle_pos ++;
    left_ankle_pos +=2;
    right_hip_pos ++;
    left_hip_pos ++;
    waist_pos --;
    right_shoulder_pos -=1;
    left_shoulder_pos -=1;
    move_servos();
    delay(b_walk_delay);
  }
  for (int pos = 1; pos < b_x; pos++) { 
    right_hip_pos ++;
    left_hip_pos ++;
    if(pos < (x/2)) {
      waist_pos --;
      right_shoulder_pos -=1;
      left_shoulder_pos -=1;
    } else {
      waist_pos ++;
      right_shoulder_pos +=1;
      left_shoulder_pos +=1;
    }
    move_servos();
    delay(b_walk_delay);
  }
  for (int pos = 1; pos < b_x; pos++) {
    right_ankle_pos --;
    left_ankle_pos -=2;
    waist_pos ++;
    right_shoulder_pos +=1;
    left_shoulder_pos +=1;
    move_servos();
    delay(b_walk_delay);
  }
}
