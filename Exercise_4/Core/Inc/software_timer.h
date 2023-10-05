/*
 * software_timer.h
 *
 *  Created on: Oct 5, 2023
 *      Author: Hiepm
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_



#endif /* INC_SOFTWARE_TIMER_H_ */

extern int timer1_counter;
extern int timer1_flag;
extern int timer2_counter;
extern int timer2_flag;

void setTimer1(int duration);
void setTimer2(int duration);
void timerRun();
