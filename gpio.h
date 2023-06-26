#ifndef GPIO_H
#define GPIO_H

#define _SFR_16(mem_addr)           (*(volatile unsigned short *)(mem_addr))
#define GPIO_PORT_0_BASE_ADDRESS    0x10080000UL
#define GPIO_PORT_0_DDR_ADDRESS     0x100C0000UL
#define GPIO_PORT_0_DDR             _SFR_16(GPIO_PORT_0_DDR_ADDRESS)
#define GPIO_PORT_0_IO(io_num)      _SFR_16(GPIO_PORT_0_BASE_ADDRESS | (1 << (io_num + 2)))

#define GPIO_PORT_1_BASE_ADDRESS    0x10180000UL
#define GPIO_PORT_1_DDR_ADDRESS     0x101C0000UL
#define GPIO_PORT_1_DDR             _SFR_16(GPIO_PORT_1_DDR_ADDRESS)
#define GPIO_PORT_1_IO(io_num)      _SFR_16(GPIO_PORT_1_BASE_ADDRESS | (1 << (io_num + 2)))

#endif // GPIO_H
