#ifndef TIMER_H
#define TIMER_H

typedef struct
{
    volatile unsigned int load_count;
    volatile unsigned int current_value;
    volatile unsigned int control;
    volatile unsigned int EOI;
    volatile unsigned int interrupt_status;
} TIMER_Type;

#define TIMER_BASE_ADDRESS 			0x10000A00UL
#define TIMER_INTR_STATUS_ADDRESS   0x10000AA8UL
#define _SFR_32(mem_addr)	(*(volatile unsigned long *)(mem_addr))
#define TIMER_INTR_STATUS           _SFR_32(TIMER_INTR_STATUS_ADDRESS)
#define TIMER_INTR_FLAG(timer_num)  (TIMER_INTR_STATUS & (1 << (timer_num)))

#define TIMER(n) (*((volatile TIMER_Type *)(TIMER_BASE_ADDRESS + (n * sizeof(TIMER_Type)))))

void TIMER_setup_delay(unsigned char timer, unsigned long clocks);


#endif // TIMER_H
