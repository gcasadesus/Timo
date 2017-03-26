#include <Servo.h>


Servo right_ankle;
Servo left_ankle;
Servo right_hip;
Servo left_hip;
Servo right_shoulder;
Servo left_shoulder;
Servo right_arm;
Servo left_arm;
Servo waist;

int right_ankle_pos = 101;
int left_ankle_pos = 102;
int right_hip_pos = 80;
int left_hip_pos = 90;
int right_shoulder_pos = 85;
int left_shoulder_pos = 85;
int right_arm_pos = 15;
int left_arm_pos = 180;
int waist_pos = 77;
int x = 16;//18
int walk_delay = 13;
int y = 20;
int dance_delay = 8;
int z = 20;
int punch_delay = 1;
int p = 79;
int b_x = 16;
int b_walk_delay =13;
int turn_delay = 13;

char byterebut=0;
bool b_end_right;
bool right_front=false;

void setup()
{
  right_ankle.attach(A3);
  left_ankle.attach(A4);
  right_hip.attach(A1);
  left_hip.attach(A2);
  right_shoulder.attach(12);
  left_shoulder.attach(11);
  right_arm.attach(13);
  left_arm.attach(2);
  waist.attach(10);
  move_servos();
  Serial.begin(9600);
  delay(1000);
  //ip 98:D3:31:80:A5:53
}

void loop()
{
  while(1) {
  //waist_pos = 77;
  while (Serial.available() <= 0);
  byterebut=Serial.read();
  switch (byterebut) {          
     case 50:
         walk();         
         break;
         
     case 51:
         while (byterebut != 61){
            if (Serial.available() > 0) {
            byterebut=Serial.read();
            }
            go_left();
         }
         break;
         
     case 52:
         while (byterebut != 62){
            if (Serial.available() > 0) {
            byterebut=Serial.read();
            }
            go_right();
         }
         break;
         
     case 53:
         walk_backwards();
         break;
         
     case 54:
         while (byterebut != 64){
            if (Serial.available() > 0) {
            byterebut=Serial.read();
            }
            turn_right();
         }
         break;
     
     case 55:
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
    for (int pos = 1; pos < 20; pos++) { //aixeca peu esquerra i move_servos cama esquerra endavant
    right_ankle_pos++;
    left_ankle_pos += 2;
    right_hip_pos --;
    left_hip_pos --;
    waist_pos ++;
    move_servos();
    delay(turn_delay);
  }
  delay(80);
  for (int pos = 1; pos < 20; pos++) { // baixa peus sense move_servos caderes
    right_ankle_pos--;
    left_ankle_pos -= 2;
    waist_pos --;
    move_servos();
    delay(turn_delay);
  }
  delay(80);
  for (int pos = 1; pos < 20; pos++) { // baixa peus sense move_servos caderes
    right_ankle_pos -=2;
    left_ankle_pos --;
    right_hip_pos ++;
    left_hip_pos --;
    move_servos();
    delay(turn_delay);
  }
  delay(80);
  for (int pos = 1; pos < 20; pos++) { // baixa peus sense move_servos caderes
    right_ankle_pos +=2;
    left_ankle_pos ++;
    move_servos();
    delay(turn_delay);
  }
  for (int pos = 1; pos < 20; pos++) { // baixa peus sense move_servos caderes
    right_ankle_pos ++;
    left_ankle_pos +=2;
    left_hip_pos ++;
    move_servos();
    delay(turn_delay);
  }
  for (int pos = 1; pos < 20; pos++) { // baixa peus sense move_servos caderes
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
    for (int pos = 1; pos < 17; pos++) { //aixeca peu esquerra i move_servos cama esquerra endavant
    right_ankle_pos -=2;
    left_ankle_pos --;
    right_hip_pos ++;
    left_hip_pos ++;
    waist_pos ++;
    move_servos();
    delay(turn_delay);
  }
  delay(80);
  for (int pos = 1; pos < 17; pos++) { // baixa peus sense move_servos caderes
    right_ankle_pos +=2;
    left_ankle_pos ++;
    waist_pos --;
    move_servos();
    delay(turn_delay);
  }
  delay(80);
  for (int pos = 1; pos < 17; pos++) { // baixa peus sense move_servos caderes
    right_ankle_pos ++;
    left_ankle_pos +=2;
    right_hip_pos ++;
    left_hip_pos --;
    move_servos();
    delay(turn_delay);
  }
  delay(80);
  for (int pos = 1; pos < 17; pos++) { // baixa peus sense move_servos caderes
    right_ankle_pos --;
    left_ankle_pos -=2;
    move_servos();
    delay(turn_delay);
  }
  for (int pos = 1; pos < 17; pos++) { // baixa peus sense move_servos caderes
    right_ankle_pos -=2;
    left_ankle_pos --;
    right_hip_pos --;
    move_servos();
    delay(turn_delay);
  }
  for (int pos = 1; pos < 17; pos++) { // baixa peus sense move_servos caderes
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
    right_arm_pos +=7;
    right_ankle_pos ++;
    left_ankle_pos +=2;
    move_servos();
    delay(4);
  }
  delay(200);
  for (int pos = 1; pos < 20; pos++) {
    right_arm_pos -=7;
    right_ankle_pos --;
    left_ankle_pos -=2;
    move_servos();
    delay(4);
  }
}

void left_swing (void) {
  for (int pos = 1; pos < 20; pos++) {
    left_arm_pos -=7;
    right_ankle_pos -=2;
    left_ankle_pos --;
    move_servos();
    delay(4);
  }
  delay(200);
  for (int pos = 1; pos < 20; pos++) {
    left_arm_pos +=7;
    right_ankle_pos +=2;
    left_ankle_pos ++;
    move_servos();
    delay(4);
  }
}

void get_up(void) {
  for (int i=0; i<85; i++)  { //pugem peus
    if (i<70)
      right_ankle_pos ++;
    left_ankle_pos --;
    move_servos();
    delay(1);
  } // right_ankle +70 // left_ankle -85
  for (int i=0; i<85; i++) {  //girem caderes
    right_hip_pos ++;
    if (i<40)
      left_hip_pos ++;
    move_servos();
    delay(5);
  } // right_hip +85 // left_hip +40
  for (int i=0; i<85; i++) {  //pugem braços
    right_arm_pos ++;
    left_arm_pos --;
    move_servos();
    delay(5);
  } // right_arm +85 // left_arm -85
  for (int i=0; i<80; i++) { //aixequem una mica el cos
    left_arm_pos --;
    left_shoulder_pos --;
    if (i>60)
      waist_pos ++;
    right_shoulder_pos ++;
    move_servos();
    delay(2);
  } // right_arm +85 // left_arm -165 // left_shoulder -80 // waist +20 // right_shoulder +80
  for (int i=0; i<70; i++)  {
    right_arm_pos --;
    waist_pos ++;
    if (i>15) {
      left_arm_pos ++;
    }
    if (i>20) {
      right_ankle_pos --;
    }
    move_servos();
    delay(5);
  } // right_arm -15 // waist +90 // left_arm -110 // right_ankle +20
  delay(600);
  for (int i=0; i<80; i++)  {
    left_shoulder_pos ++;
    if (i>0)
      left_arm_pos ++;
    move_servos();
    delay(5);
  } // left_shoulder 0 // left arm -85 
  delay(200);
  for (int i=0; i<85; i++)  {
    if ((i>40)&&(i<80))
      left_hip_pos --;
    
    if ((i>60)&&(i<80)) 
      right_ankle_pos --;
    
    right_hip_pos --;
    left_ankle_pos ++;
    move_servos();
    delay(2);
  } // left_hip 0 // right_ankle 0 // right_hip 0 // left_ankle 0
  for (int i=0; i<90; i++)  {
    if (i<85)
      left_arm_pos ++;
    if (i<15)
      right_arm_pos --;
    if (i<80)
      right_shoulder_pos --;
    waist_pos --;
    move_servos();
    delay(8);
  } //left_arm 0 // left_shoulder 0 // right_arm 0 // right_shoulder 0 // waist 0
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
    waist_pos +=3;
    right_shoulder_pos +=3;
    if(i>=15)
      right_arm_pos +=4;
    right_hip_pos ++;
    left_hip_pos ++;
    move_servos();
    delay(punch_delay);
  }
  delay(300);
  for (int i=0; i<z+10; i++) {
    if (i<23)
      waist_pos -=3;
    right_shoulder_pos -=3;
    if(i<15)
      right_arm_pos -=4;
    right_hip_pos --;
    left_hip_pos --;
    move_servos();
    delay(punch_delay);
  }
  waist_pos --;
  move_servos();
}

void left_punch(void) {
  for (int i=0; i<z; i++) {
    waist_pos ++;
    move_servos();
    delay(punch_delay);
  }
  for (int i=0; i<z+10; i++) {
    waist_pos -=3;
    left_shoulder_pos -=3;
    if(i>=15)
      left_arm_pos -=4;
    right_hip_pos --;
    left_hip_pos --;
    move_servos();
    delay(punch_delay);
  }
  delay(300);
  for (int i=0; i<z+10; i++) {
    if (i<23)
      waist_pos +=3;
    left_shoulder_pos +=3;
    if(i<15)
      left_arm_pos +=4;
    right_hip_pos ++;
    left_hip_pos ++;
    move_servos();
    delay(punch_delay);
  }
  waist_pos ++;
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
}

//***********************************************************************************************
//******  WALK  *********************************************************************************
//***********************************************************************************************
void half_step_left_leg(void){
  for (int pos = 1; pos < x; pos++) { //aixeca peu esquerra i move_servos cama esquerra endavant
    right_ankle_pos++;
    left_ankle_pos += 2;
    right_hip_pos --;
    left_hip_pos --;
    waist_pos ++;
    right_shoulder_pos ++;
    left_shoulder_pos ++;
    move_servos();
    delay(walk_delay);
  }
  for (int pos = 1; pos < x; pos++) { // baixa peus sense move_servosre caderes
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
  for (int pos = 1; pos < x; pos++) { //aixeca peu esquerra i move_servos cama esquerra endavant
    right_ankle_pos-=2;
    left_ankle_pos --;
    right_hip_pos ++;
    left_hip_pos ++;
    waist_pos --;
    right_shoulder_pos --;
    left_shoulder_pos --;
    move_servos();
    delay(walk_delay);
  }
  for (int pos = 1; pos < x; pos++) { // baixa peus sense move_servosre caderes
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
  for (int pos = 1; pos < x; pos++) { //aixeca peu dret i cama dreta endavant
    right_ankle_pos -= 2;
    left_ankle_pos --;
    right_hip_pos ++;
    left_hip_pos ++;
    waist_pos --;
    left_shoulder_pos -=2;
    right_shoulder_pos -=2;
    move_servos();
    delay(walk_delay);
  }
  for (int pos = 1; pos < x; pos++) { //seguim move_servosnt cama dreta
    right_hip_pos ++;
    left_hip_pos ++;
    if(pos < (x/2)) {
      waist_pos --;
      left_shoulder_pos -=2;
      right_shoulder_pos -=2;
    } else {
      waist_pos ++;
      left_shoulder_pos +=2;
      right_shoulder_pos +=2;
    }
    move_servos();
    delay(walk_delay);
  }
  for (int pos = 1; pos < x; pos++) { //baixem peus
    right_ankle_pos += 2;
    left_ankle_pos ++;
    waist_pos ++;
    left_shoulder_pos +=2;
    right_shoulder_pos +=2;
    move_servos();
    delay(walk_delay);
  }
}

void step_left_leg(void){
  for (int pos = 1; pos < x; pos++) { //aixeca peu dret i cama dreta endavant
    right_ankle_pos ++;
    left_ankle_pos +=2;
    right_hip_pos --;
    left_hip_pos --;
    waist_pos ++;
    right_shoulder_pos +=2;
    left_shoulder_pos +=2;
    move_servos();
    delay(walk_delay);
  }
  for (int pos = 1; pos < x; pos++) { //seguim move_servosnt cama dreta
    right_hip_pos --;
    left_hip_pos --;
    if(pos < (x/2)) {
      waist_pos ++;
      right_shoulder_pos +=2;
      left_shoulder_pos +=2;
    } else {
      waist_pos --;
      right_shoulder_pos -=2;
      left_shoulder_pos -=2;
    }
    move_servos();
    delay(walk_delay);
  }
  for (int pos = 1; pos < x; pos++) { //baixem peus
    right_ankle_pos --;
    left_ankle_pos -=2;
    waist_pos --;
    right_shoulder_pos -=2;
    left_shoulder_pos -=2;
    move_servos();
    delay(walk_delay);
  }
}
//***********************************************************************************************
//******  BACKWARDS WALK  ***********************************************************************
//***********************************************************************************************
void b_half_step_left_leg(void){
  for (int pos = 1; pos < b_x; pos++) { //aixeca peu esquerra i move_servos cama esquerra endavant
    right_ankle_pos++;
    left_ankle_pos += 2;
    right_hip_pos ++;
    left_hip_pos ++;
    waist_pos ++;
    right_shoulder_pos -=2;
    left_shoulder_pos -=2;
    move_servos();
    delay(b_walk_delay);
  }
  for (int pos = 1; pos < b_x; pos++) { // baixa peus sense move_servosre caderes
    right_ankle_pos --;
    left_ankle_pos -=2;
    waist_pos --;
    right_shoulder_pos +=2;
    left_shoulder_pos +=2;
    move_servos();
    delay(b_walk_delay);
  }
}


void b_half_step_right_leg(void){
  for (int pos = 1; pos < b_x; pos++) { //aixeca peu esquerra i move_servos cama esquerra endavant
    right_ankle_pos-=2;
    left_ankle_pos --;
    right_hip_pos --;
    left_hip_pos --;
    waist_pos ++;
    right_shoulder_pos +=2;
    left_shoulder_pos +=2;
    move_servos();
    delay(b_walk_delay);
  }
  for (int pos = 1; pos < b_x; pos++) { // baixa peus sense move_servosre caderes
    right_ankle_pos+=2;
    left_ankle_pos ++;
    waist_pos --;
    right_shoulder_pos -=2;
    left_shoulder_pos -=2;
    move_servos();
    delay(b_walk_delay);
  }
}

void b_step_right_leg(void){
  for (int pos = 1; pos < b_x; pos++) { //aixeca peu dret i cama dreta endavant
    right_ankle_pos -=2;
    left_ankle_pos --;
    right_hip_pos --;
    left_hip_pos --;
    waist_pos ++;
    left_shoulder_pos +=2;
    right_shoulder_pos +=2;
    move_servos();
    delay(b_walk_delay);
  }
  for (int pos = 1; pos < b_x; pos++) { //seguim move_servosnt cama dreta
    right_hip_pos --;
    left_hip_pos --;
    if(pos < (x/2)) {
      waist_pos ++;
      left_shoulder_pos +=2;
      right_shoulder_pos +=2;
    } else {
      waist_pos --;
      left_shoulder_pos -=2;
      right_shoulder_pos -=2;
    }
    move_servos();
    delay(b_walk_delay);
  }
  for (int pos = 1; pos < b_x; pos++) { //baixem peus
    right_ankle_pos += 2;
    left_ankle_pos ++;
    waist_pos --;
    left_shoulder_pos -=2;
    right_shoulder_pos -=2;
    move_servos();
    delay(b_walk_delay);
  }
}

void b_step_left_leg(void){
  for (int pos = 1; pos < b_x; pos++) { //aixeca peu dret i cama dreta endavant
    right_ankle_pos ++;
    left_ankle_pos +=2;
    right_hip_pos ++;
    left_hip_pos ++;
    waist_pos --;
    right_shoulder_pos -=2;
    left_shoulder_pos -=2;
    move_servos();
    delay(b_walk_delay);
  }
  for (int pos = 1; pos < b_x; pos++) { //seguim move_servosnt cama dreta
    right_hip_pos ++;
    left_hip_pos ++;
    if(pos < (x/2)) {
      waist_pos --;
      right_shoulder_pos -=2;
      left_shoulder_pos -=2;
    } else {
      waist_pos ++;
      right_shoulder_pos +=2;
      left_shoulder_pos +=2;
    }
    move_servos();
    delay(b_walk_delay);
  }
  for (int pos = 1; pos < b_x; pos++) { //baixem peus
    right_ankle_pos --;
    left_ankle_pos -=2;
    waist_pos ++;
    right_shoulder_pos +=2;
    left_shoulder_pos +=2;
    move_servos();
    delay(b_walk_delay);
  }
}
