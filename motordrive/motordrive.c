/*
 * motordrive.c
 *
 * Created: 2012-04-11 16:10:02
 *  Author: Wim
 *
 *  This small testprogram can drive two dc-motors in pwm mode
 *  Motor A is controlled by PB0 (direction) and OC0A (speed, PB2)
 *  Motor B is controlled by PB1 (direction) and OC0B (speed, PA7)
 */ 

/*
 * Run internal clock at 1 MHz
 */
#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include "motordrive.h"


void MOTORinit()
{
   /*
   TCCR0A - Timer Counter Control Register A (TIMER0)
   -----------------------------------------------
   NO:   NAME   DESCRIPTION
   --------------------------
   BIT 7 : COM0A1  Compare Output Mode        [SET to 1]
   BIT 6 : COM0A0  Compare Output Mode        [SET to 0] non inverted mode
   BIT 5 : COM0B1  Compare Output Mode        [SET to 1] used with OC0B (pin 6)
   BIT 4 : COM0B0  Compare Output Mode        [SET to 0] used with OC0B (pin 6)
   BIT 3 : NOT USED
   BIT 2 : NOT USED
   BIT 1 : WGM01  Wave form generation mode [SET to 1]
   BIT 0 : WGM00  Wave form generation mode [SET to 1]
   
   
   TCCR0B - Timer Counter Control Register B (TIMER0)
   -----------------------------------------------
   NO:   NAME   DESCRIPTION
   --------------------------
   BIT 7 : FOC0A   Force Output Compare      [SET to X] not used
   BIT 6 : FOC0B   Force Output Compare      [SET to X] not used
   BIT 5 : NOT USED
   BIT 4 : NOT USED
   BIT 3 : WGM02  Wave form generation mode  [SET to 0]
   BIT 2 : CS02   Clock Select               [SET to 1]
   BIT 1 : CS01   Clock Select               [SET to 0]
   BIT 0 : CS00   Clock Select               [SET to 1] use internal clock

   The above settings are for
   --------------------------

   Timer Clock = CPU Clock (With prescaling)
   Mode        = Fast PWM
   PWM Output  = Non Inverted
   
   PRESCALING
   CS0     prescaling
     1     no prescaling
	 2     prescaling factor = 8
	 3     prescaling factor = 64
	 4     prescaling factor = 256
	 5     prescaling factor = 1024

   */


   TCCR0A|=(1<<WGM00)|(1<<WGM01)|(1<<COM0A1)|(1<<COM0B1);
   TCCR0B|=(0<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00);

   //Set OC0A PIN as pwm output. It is  PB2 on ATtiny44
   //Set OC0B PIN as pwm output. It is  PA7 on ATtiny44
   //Set PB0 and PB1 PINS as direction output for motor control
   

   DDRB|=(1<<L_MOTOR_PIN)|(1<<R_DIR_PIN)|(1<<L_DIR_PIN); //PB2 (pin 5) is pwm output, PB0 (pin 2), PB1 (pin 3) are direction outputs
   DDRA|=(1<<R_MOTOR_PIN);  //PA7 (pin 6) is pwm output OC0B
}

/******************************************************************
MOTORright(int speed)
INPUT
speed: 0 .. 255 sets dutycycle of pwm (0 .. 100 %)

This function will rotate motor A  at given speed, 
+ve speed is forward; -ve speed is backward
*********************************************************************/
void MOTORright(int speed)
{
	if (speed < 0)
	{
		speed = -speed;
		PORTB &= 0xFE;
	} 
	else
	{
		PORTB |=0x01;
	}
	if (speed > MAXSPEED)
	{
		speed = MAXSPEED;
	}
	OCR0A = speed;
}
/******************************************************************
MOTORleft(int speed)
INPUT
speed: 0 .. 255 sets dutycycle of pwm (0 .. 100 %)

This function will rotate motor B  at given speed,
+ve speed = forward; -ve speed is backward
*********************************************************************/
void MOTORleft(int speed)
{
	if (speed < 0)
	{
		speed = -speed;
		PORTB &= 0xFD;
	}
	else
	{
		PORTB |=0x02;
	}
	if (speed > MAXSPEED)
	{
		speed = MAXSPEED;
	}
	OCR0B = speed;
}
