/*
 * motordrive.h
 *
 * Created: 2014-02-02 19:42:23
 *  Author: Wim
 */ 


#ifndef MOTORDRIVE_H_
#define MOTORDRIVE_H_

#define L_DIR_PIN PB0
#define R_DIR_PIN PB1
#define L_MOTOR_PIN PB2
#define R_MOTOR_PIN PA7
#define MAXSPEED 255

void MOTORinit();
void MOTORleft(int);
void MOTORright(int);

#endif /* MOTORDRIVE_H_ */
