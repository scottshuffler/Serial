/*
 * Serial.c
 *
 * Created: 2/5/2015 11:11:17 AM
 *  Author: shuffleres
 */ 


#include <avr/io.h>
#include <util/delay.h>

//Data bits / Parity / Stop bits
// 5 Data / No Parity / 1 Stop
#define SERIAL_5N1 0x00
#define SERIAL_6N1 0x01
#define SERIAL_7N1 0x02
#define SERIAL_8N1 0x03
#define SERIAL_5N2 0x08
#define SERIAL_6N2 0x09
#define SERIAL_7N2 0x0A
#define SERIAL_8N2 0x0B
#define SERIAL_5E1 0x20
#define SERIAL_6E1 0x21
#define SERIAL_7E1 0x22
#define SERIAL_8E1 0x23
#define SERIAL_5E2 0x28
#define SERIAL_6E2 0x29
#define SERIAL_7E2 0x2A
#define SERIAL_8E2 0x2B
#define SERIAL_5O1 0x30
#define SERIAL_6O1 0x31
#define SERIAL_7O1 0x32
#define SERIAL_8O1 0x33
#define SERIAL_5O2 0x38
#define SERIAL_6O2 0x39
#define SERIAL_7O2 0x3A
#define SERIAL_8O2 0x3B

//Prototypes
void serial_open(long speed, int config);
char serial_read();
void serial_write(unsigned char write);

int main(void)
{
	serial_open(9600, SERIAL_8N1);
    while(1)
    {
		serial_read();
		serial_write('b');
		_delay_ms(1000);
    }
}

//Serial open function
//Takes in the speed(baud) and the config (bit definitions)
void serial_open(long speed, int config)
{
	//INIT USART
	switch (speed)
	{
	case 2400:
		UBRR0 = 832;
		UCSR0A |= (1<<U2X0);
		break;
	case 4800:
		UBRR0 = 207;
		UCSR0A &= ~(1<<U2X0);
		break;
	case 9600:
		UBRR0 = 103;
		UCSR0A &= ~(1<<U2X0);
		break;
	case 14400:
		UBRR0 = 68;
		UCSR0A &= ~(1<<U2X0);
		break;
	case 19200:
		UBRR0 = 51;
		UCSR0A &= ~(1<<U2X0);
		break;
	case 28800:
		UBRR0 = 68;
		UCSR0A |= (1<<U2X0);
		break;
	case 38400:
		UBRR0 = 25;
		UCSR0A &= ~(1<<U2X0);
		break;
	case 57600:
		UBRR0 = 16;
		UCSR0A &= ~(1<<U2X0);
		break;
	case 76800:
		UBRR0 = 12;
		UCSR0A &= ~(1<<U2X0);
		break;
	case 115200:
		UBRR0 = 16;
		UCSR0A |= (1<<U2X0);
		break;
	case 230400:
		UBRR0 = 3;
		UCSR0A &= ~(1<<U2X0);
		break;
	case 250000:
		UBRR0 = 3;
		UCSR0A &= ~(1<<U2X0);
		break;
	default:
		return;
	}
	switch (config)
	{
		case SERIAL_5N1:
		case SERIAL_6N1:
		case SERIAL_7N1:
		case SERIAL_8N1:
		case SERIAL_5N2:
		case SERIAL_6N2:
		case SERIAL_7N2:
		case SERIAL_8N2:
		case SERIAL_5E1:
		case SERIAL_6E1:
		case SERIAL_7E1:
		case SERIAL_8E1:
		case SERIAL_5E2:
		case SERIAL_6E2:
		case SERIAL_7E2:
		case SERIAL_8E2:
		case SERIAL_5O1:
		case SERIAL_6O1:
		case SERIAL_7O1:
		case SERIAL_8O1:
		case SERIAL_5O2:
		case SERIAL_6O2:
		case SERIAL_7O2:
		case SERIAL_8O2:
		//UCSR0C &= 0;
		//UCSR0C = config;
		break;
		default:
			return;
	}
	//Set UBRRH to the sig bits
	UBRR0H = (UBRR0 >> 8);
	//Set UBRRL to the rest 
	UBRR0L =  UBRR0;
	//Enables TX and RX
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
	
}

char serial_read()
{
	while (!(UCSR0A & (1<<RXC0)))
	{
		return;
	}
	return UDR0;
}

void serial_write(unsigned char write)
{
	while((!UCSR0A) & (1<<UDRE0))
	{
		return;
	}
	UDR0 = write;
}