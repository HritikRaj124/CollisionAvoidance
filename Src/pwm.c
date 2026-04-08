#include "pwm.h"

// Base Addresses
#define RCC_BASE       0x40023800UL
#define GPIOD_BASE     0x40020C00UL
#define TIM4_BASE      0x40000800UL

// RCC Registers
#define RCC_AHB1ENR    (*(volatile uint32_t *)(RCC_BASE + 0x30))
#define RCC_APB1ENR    (*(volatile uint32_t *)(RCC_BASE + 0x40))

// GPIOD Registers
#define GPIOD_MODER    (*(volatile uint32_t *)(GPIOD_BASE + 0x00))
#define GPIOD_AFRH     (*(volatile uint32_t *)(GPIOD_BASE + 0x24))

// TIM4 Registers
#define TIM4_CR1       (*(volatile uint32_t *)(TIM4_BASE + 0x00))
#define TIM4_CCMR1     (*(volatile uint32_t *)(TIM4_BASE + 0x18))
#define TIM4_CCER      (*(volatile uint32_t *)(TIM4_BASE + 0x20))
#define TIM4_PSC       (*(volatile uint32_t *)(TIM4_BASE + 0x28))
#define TIM4_ARR       (*(volatile uint32_t *)(TIM4_BASE + 0x2C))
#define TIM4_CCR2      (*(volatile uint32_t *)(TIM4_BASE + 0x38))
#define TIM4_EGR       (*(volatile uint32_t *)(TIM4_BASE + 0x14))

// Bit Masks
#define RCC_AHB1ENR_GPIODEN   (1U << 3)
#define RCC_APB1ENR_TIM4EN    (1U << 2)

void pwm_init(void)
{
	RCC_AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	RCC_APB1ENR |= RCC_APB1ENR_TIM4EN;

	GPIOD_MODER &= ~(3U << (13 * 2));
	GPIOD_MODER |= (2U << (13 * 2));

	GPIOD_AFRH &= ~(0xF << ((13 - 8) * 4));
	GPIOD_AFRH |= (2U << ((13 - 8) * 4));


	TIM4_PSC = 16000 - 1;
	TIM4_ARR = 100 - 1;

	TIM4_CCMR1 &= ~(0xF << 12); // clear OC2M + OC2PE
	TIM4_CCMR1 |=  (6U << 12); // PWM mode 1 (no preload)

	TIM4_CCER |= (1U << 4);    // CC2E
	TIM4_EGR  |= 1;            // Update event
	TIM4_CR1  |= (1U << 0);    // CEN

	//TIM4_EGR |= 1;
}

void pwm_set_duty(uint8_t duty)
{
	if (duty > 100)
	{
		duty = 100;
	}

	TIM4_CCR2 = duty;
}



