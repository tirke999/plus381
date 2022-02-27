/*
 * timer.c
 *
 *  Created on: Feb 13, 2022
 *      Author: aleksa
 */


#include "timer.h"

static void
tim2_init (void);


static volatile uint32_t sys_time = 0;
static bool flag_timer = false;




void
timer_init (void)
{
  tim2_init ();

  //tim4_init ();
}

static void
tim2_init (void) //Inicijalizacija timera 2 i podesavanje registara
{
  RCC->APB1ENR |= (0b1 << 0);

  TIM2->CR1 &= ~(0xffff);
  TIM2->CR1 |= (0b1 << 2) | (0b1 << 7);

  TIM2->DIER |= (0b1 << 0); //dozvola TIM2 da generise prekid (na overflow)

  // trenutno: 84MHz - 1MHz - 1kHz
  // zeljeno: 1kHz - 1ms

  //PSC je delitelj frekvencije
  //ARR je maksimalna vrednost do koje mozemo da brojimo
  TIM2->PSC = (84 - 1);  //Dobija se 1 MHz-->>Preskaler (1M = 1000k)
  TIM2->ARR = (1000 - 1); //Auto Reload Registar (max vrednost brojanja)

  TIM2->EGR |= (0b1 << 0);

  TIM2->CR1 |= (0b1 << 0);

  NVIC->ISER[0] |= (0b1 << 28); //ISER je vektor od 8 registara, svaki po 32 bit-a
}





bool //funkcija koja se koristi za racunanje koliko je vremena proslo
is_time_passed (uint32_t ms)
{
  static uint32_t start_time;
  bool res = false;

  if (flag_timer == false)
    {
      start_time = sys_time;
      flag_timer = true;
    }

  if (ms <= (sys_time - start_time))
    {
      res = true;
      flag_timer = false;
    }

  return res;
}



void
TIM2_IRQHandler (void) //Merenje proteklog vremena u ms
{
  if (TIM2->SR & (0b1 << 0))     //Provera da li je TIM2 u statu registru dobio jedinicu, odnosno izbrojao do kraja vec jednom
    {
      TIM2->SR &= ~(0b1 << 0);  //resetovanje brojaca da broji ispocetka

      // Telo funkcije
      sys_time++;

      //Ocitavanje stanja robota
      //sens_robot();

      //Regulacija brzine
      //regulacija_brzine();

      if((sys_time % 10) == 0){
	  //Regulacija pozicije
      }
    }
}
