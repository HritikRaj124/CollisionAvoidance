#include "uart.h"

// Base Addresses
#define RCC_BASE    0x40023800UL
#define GPIOA_BASE  0x40020000UL
#define USART2_BASE 0x40004400UL

// RCC Registers
#define RCC_AHB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR (*(volatile uint32_t *)(RCC_BASE + 0x40))


// GPIOA Registers
#define GPIOA_MODER   (*(volatile uint32_t *)(GPIOA_BASE + 0x00))
#define GPIOA_AFRL    (*(volatile uint32_t *)(GPIOA_BASE + 0x20))

// UART2 Registers
#define USART2_SR     (*(volatile uint32_t *)(USART2_BASE + 0x00))
#define USART2_DR     (*(volatile uint32_t *)(USART2_BASE + 0x04))
#define USART2_BRR    (*(volatile uint32_t *)(USART2_BASE + 0x08))
#define USART2_CR1    (*(volatile uint32_t *)(USART2_BASE + 0x0C))

// Bit Masks
#define RCC_AHB1ENR_GPIOAEN   (1U << 0)
#define RCC_APB1ENR_USART2EN  (1U << 17)

#define USART2_SR_TXE         (1U << 7)
#define USART2_CR1_TE         (1U << 3)
#define USART2_CR1_UE         (1U << 13)
#define USART2_CR1_RE         (1U << 2)


// Initialization
void uart_init(void)
{
	RCC_AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC_APB1ENR |= RCC_APB1ENR_USART2EN;

	GPIOA_MODER &= ~(3U << (2 * 2));
	GPIOA_MODER |=  (2U << (2 * 2));

	GPIOA_AFRL &= ~(0xF << (4 * 2));
	GPIOA_AFRL |=  (7U << (4 * 2));

	USART2_BRR = 0x0683; //Baud

	USART2_CR1 |= USART2_CR1_TE;
	USART2_CR1 |= USART2_CR1_UE;
	USART2_CR1 |= USART2_CR1_RE;

}

// Transmission
void uart_send_char(char c)
{
	while (!(USART2_SR & USART2_SR_TXE));
	USART2_DR = c;
}

// String Transmission
void uart_send_string(const char *str)
{
	while (*str != '\0')
	{
		uart_send_char(*str);
		str++;
	}

	//while (*str)
	//{
		//uart_send_char(*str++);
	//}
}

void uart_send_int(int value)
{
	char buffer[10];
	int i = 0;

	if(value == 0)
	{
		uart_send_char ('0');
		return;
	}



	while (value > 0)
	{
        buffer[i++] = (value % 10) + '0';
        value /= 10;
	}

	while (i--)
	{
		uart_send_char(buffer[i]);
	}
}


