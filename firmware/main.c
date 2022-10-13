#include <avr/io.h>
#include <avr/interrupt.h>

#define LED 0
#define BUTTON 2

volatile uint8_t state;
volatile uint8_t timeout;

int main(void)
{
	uint8_t sequence = 0;

	RSTFLR = 0x00; // Clear reset flags
	CCP = 0xD8; // Enable watchdog modification
	WDTCSR = 0x00; // Disable watchdog

	DDRB = 1 << LED; // Set led as output
	PUEB = 1 << BUTTON; // Enable pullup for button

	CCP = 0xD8; // Enable clock modification
	CLKMSR = 0x01; // Use slow ass clock
	CCP = 0xD8; // Enable clock modification... again
	CLKPSR = 0x02; // Divide clock by 4

	TCCR0A = 0x81; // Set output mode to non-inverting and begin setting fast PWM mode
	TCCR0B = 0x09; // Complete setting fast PWM mode and enable clock

	PCMSK = 1 << BUTTON; // Enable pin change interrupt for button
	PCICR = 0x01; // Enable pin change interrupts

	__asm__("sei"); // Enable global interrupts

	SMCR = 0x05; // Set sleep mode to power-down and enable

	__asm__("sleep"); // Enter sleep
	
	while (1)
	{
		switch (state)
		{
			case 1:
				OCR0A = 0x20;
				break;

			case 2:
				OCR0A = 0xFF;
				break;

			case 3:
				if (sequence == 0x00)
				{
					OCR0A = 0x00;
				}

				if (sequence == 0x80)
				{
					OCR0A = 0xFF;
				}

				++sequence;
				break;

			default:
				OCR0A = 0x00;
				WDTCSR = 0x08; // Enable watchdog
				while (1); // Wait for watchdog reset
		}

		for (uint8_t delay = 0x10; delay; --delay)
		{
			__asm__("nop");
		}

		if (timeout)
		{
			timeout--;
		}
	}
}

ISR(PCINT0_vect)
{
	if (timeout || PINB & (1 << BUTTON))
	{
		return;
	}

	++state;
	timeout = 0x20;
}