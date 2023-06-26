#ifndef DISPLAY_H
#define DISPLAY_H

#define DISPLAY_COMMAND_MODE        0x0
#define DISPLAY_DATA_MODE           0x40

#define DISPLAY_PAGES               8
#define DISPLAY_PAGE_HEIGHT         8

typedef struct {
    volatile unsigned char I2C_CR;
    volatile unsigned char I2C_SR0;
    volatile unsigned char I2C_SR1;
    volatile unsigned char I2C_IER;
    volatile unsigned char I2C_TxFF;
    volatile unsigned char I2C_RxFF;
    volatile unsigned char I2C_CHL;
    volatile unsigned char I2C_CHH;
    volatile unsigned char I2C_CHHL;
    volatile unsigned char I2C_CHHH;
    volatile unsigned char I2C_TXCLR;
} I2C_REG_TYPE;

#define I2CReg(i) (*((volatile I2C_REG_TYPE *)(I2C_BASE_ADDR + (0x100 * i))))

#define I2C_BASE_ADDR				0x10000800
#define I2C_CLOCK                   400000
#define I2C_BUFFER_SIZE             16

#define I2C_CLEAR_BUFFER(i)         I2CReg(i).I2C_TXCLR = 0xff
#define I2C_START_BIT               0x01
#define I2C_STOP_BIT                0x02
#define I2C_IS_TXN_COMPLETE(i)      ((I2CReg(i).I2C_SR0 & 0x08) == 0x08)
#define I2C_IS_BUFFER_EMPTY(i)      ((I2CReg(i).I2C_SR0 & 0x10) == 0x10)
#define I2C_IS_BUFFER_FULL(i)       ((I2CReg(i).I2C_SR0 & 0x04) == 0x04)
#define I2C_IS_START(i)             ((I2CReg(i).I2C_SR0 & 0x01) == I2C_START_BIT)
#define I2C_IS_STOP(i)              ((I2CReg(i).I2C_SR0 & 0x02) == I2C_STOP_BIT)

#define I2C_IS_NACK(i)              ((I2CReg(i).I2C_SR1 & 0x01) == 0x01)


#define RENDER_OPTIMISED        1
#define RENDER_ALL              0

#define DIGIT_ROWS      7
#define DIGIT_COLUMNS   7

#define CHARACTER_WIN   10
#define CHARACTER_LOSE  11

int display_write(unsigned char* data, unsigned char data_length);
void display_init();
void display_switch_on();
void display_clear();
void display_set_render_type(int type);
void display_render();
void display_put_pixel(int x, int y, int status);
void display_put_border();
void display_put_player(int px, int py, int player_number);
void display_move_player(int px, int py, int player_number, int direction);
void display_put_character(int px, int py, int d);
void display_put_scores(int p1s, int p2s);

#endif // DISPLAY_H
