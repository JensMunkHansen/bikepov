#include  <avr/io.h>
#include <util/delay.h>  

// Turns LED on and off
int main (void)
{
  DDRB |= ((1 << DDB5));
  while(1)
  {
    PORTB = ((0 << PB5));
    _delay_ms (3000L);
    PORTB = ((1 << PB5));
    _delay_ms (3000L);
  }
  return 0;
}
