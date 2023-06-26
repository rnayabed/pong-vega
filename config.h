#ifndef CONFIG_H
#define CONFIG_H

#define DISPLAY_HEIGHT              64
#define DISPLAY_WIDTH               128

#define DISPLAY_I2C_ADDRESS         0x3c
#define DISPLAY_I2C_BUS             0

#define SYSTEM_FREQUENCY 			100000000
#define DELAY                       1500000

#define PLAYER_LENGTH               15
#define PLAYER_WIDTH                2

#define PLAYER_1_START_X            10
#define PLAYER_1_START_Y            (DISPLAY_HEIGHT / 2) - (PLAYER_LENGTH / 2)

#define PLAYER_2_START_X            118
#define PLAYER_2_START_Y            PLAYER_1_START_Y

#define PLAYER_1_BUTTON_UP          0
#define PLAYER_1_BUTTON_DOWN        1
#define PLAYER_2_BUTTON_UP          2
#define PLAYER_2_BUTTON_DOWN        3

#define PLAYER_1        1
#define PLAYER_2        2

#define DIRECTION_UP    1
#define DIRECTION_DOWN  0

#endif /* CONFIG_H */
