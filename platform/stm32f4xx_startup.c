//
// Created by tomly on 08/09/2026.
//

#include <stdint.h>

#define WEAK_HANDLER(handler) void handler(void) __attribute__((weak, alias("Default_Handler")))

int main(void);
void Default_Handler(void);
void Reset_Handler(void);

WEAK_HANDLER(NMI_Handler);
WEAK_HANDLER(HardFault_Handler);
WEAK_HANDLER(MMFault_Handler);
WEAK_HANDLER(BusFault_Handler);
WEAK_HANDLER(UsageFault_Handler);
WEAK_HANDLER(SVCall_Handler);
WEAK_HANDLER(DebugMon_Handler);
WEAK_HANDLER(PendSV_Handler);
WEAK_HANDLER(SysTick_Handler);

extern uint32_t _stack_top[];
extern uint32_t _data_loadaddr[];

extern uint32_t _data[];
extern uint32_t _edata[];
extern uint32_t _bss[];
extern uint32_t _ebss[];

__attribute__((section(".isr_vector")))
__attribute__ ((used)) // Force emission of this object despite not being used in this file
const uint32_t isr_vector[] = 
{
	(uint32_t)_stack_top,
	(uint32_t)Reset_Handler,
	(uint32_t)NMI_Handler,
	(uint32_t)HardFault_Handler,
	(uint32_t)MMFault_Handler,
	(uint32_t)BusFault_Handler,
	(uint32_t)UsageFault_Handler,
	(uint32_t)0, // Reserved
	(uint32_t)0, // Reserved
	(uint32_t)0, // Reserved
	(uint32_t)0, // Reserved
	(uint32_t)SVCall_Handler,
	(uint32_t)DebugMon_Handler,
	(uint32_t)0, // Reserved
	(uint32_t)PendSV_Handler,
	(uint32_t)SysTick_Handler,
	
	// Add IRQ Handlers as required
};

void Reset_Handler(void)
{
	uint32_t num_words = _edata - _data;
	for (int i = 0; i < num_words; i++)
	{
		_data[i] = _data_loadaddr[i];
	}

	num_words = _ebss - _bss;
	for (int i = 0; i < num_words; i++)
	{
		_bss[i] = 0;
	}

	main();

	while (1);
}

void Default_Handler(void)
{
	while (1);
}
