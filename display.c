#include "config.h"
#include "display.h"

int render_type = RENDER_ALL;
unsigned char old_display_data[DISPLAY_PAGES][DISPLAY_WIDTH];
unsigned char display_data[DISPLAY_PAGES][DISPLAY_WIDTH];
unsigned char edges_to_render;

unsigned char display_characters[12][DIGIT_ROWS][DIGIT_COLUMNS] = {
    {   // 0
        {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1},
    },
    {   // 1
        {1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1}
    },
    {   // 2
        {1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1}
    },
    {   // 3
        {1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1}
    },
    {   // 4
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
    },
    {   // 5
        {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1}
    },
    {   // 6
        {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1},
    },
    {   // 7
        {1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
    },
    {   // 8
        {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1},
    },
    {   // 9
        {1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
    },
    {   // W
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 1},
        {1, 0, 0, 1, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1},
    },
    {   // L
        {1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1},
    }
};

void display_init()
{
    unsigned char b1[] = {
        DISPLAY_COMMAND_MODE,
        0xae,
        0xd5,
        0x80,
        0xa8,
        0x3f,
        0xd3,
        0x00,
        0x40,
        0xad,
        0x8b,
        0xa1,
        0xc8,
        0xda,
        0x12,
        0x81,
        0xff,
        0xd9,
        0x1f,
        0xdb,
        0x40,
        0x33,
        0xa6,
        0x20,
        0x10,
        0xa4
    };

    display_write(b1, 26);
}

int display_write(unsigned char* data, unsigned char data_length)
{
    I2C_CLEAR_BUFFER(DISPLAY_I2C_BUS);
    while (!I2C_IS_TXN_COMPLETE(DISPLAY_I2C_BUS) || !I2C_IS_BUFFER_EMPTY(DISPLAY_I2C_BUS));

    I2CReg(DISPLAY_I2C_BUS).I2C_CR = I2C_START_BIT;

    while (!I2C_IS_START(DISPLAY_I2C_BUS));

    I2CReg(DISPLAY_I2C_BUS).I2C_TxFF = DISPLAY_I2C_ADDRESS << 1;
    while (!I2C_IS_BUFFER_EMPTY(DISPLAY_I2C_BUS));

    if (I2C_IS_NACK(DISPLAY_I2C_BUS))
    {
        while (!I2C_IS_STOP(DISPLAY_I2C_BUS));
        return 2;
    }

    for (int i = 0; i < data_length; i++) {
        I2CReg(DISPLAY_I2C_BUS).I2C_TxFF = data[i];

        if ((i+1) % I2C_BUFFER_SIZE == 0)
            while (!I2C_IS_BUFFER_EMPTY(DISPLAY_I2C_BUS));
    }

    if (I2C_IS_NACK(DISPLAY_I2C_BUS))
    {
        while (!I2C_IS_STOP(DISPLAY_I2C_BUS));
        return 0;
    }

    I2CReg(DISPLAY_I2C_BUS).I2C_CR = I2C_STOP_BIT; //Set Stop bit;
    while (!I2C_IS_STOP(DISPLAY_I2C_BUS));
    return 1;
}

void display_switch_on()
{
    unsigned char buf[] = {
        DISPLAY_COMMAND_MODE,
        0xaf
    };

    display_write(buf, 2);
}

void display_clear()
{
    for (unsigned char page = 0; page < DISPLAY_PAGES; page++)
    {
        for (int column = 0; column < DISPLAY_WIDTH; column++)
        {
            display_data[page][column] = 0;
            old_display_data[page][column] = 0;
        }
    }

    render_type = RENDER_ALL;

    edges_to_render = 0xff;
}

void display_set_render_type(int type)
{
    render_type = type;
}

void display_render()
{
    if (render_type == RENDER_ALL)
    {
        for (unsigned char page = 0; page < DISPLAY_PAGES; page++)
        {
            unsigned char command[4] = {
                DISPLAY_COMMAND_MODE,
                (0xB0 | page),
                0x10, 0x2
            };

            display_write(command, 4);

            unsigned char data[DISPLAY_WIDTH + 1];
            data[0] = DISPLAY_DATA_MODE;
            for (int column = 0; column < DISPLAY_WIDTH; column++)
            {
                data[column + 1] = display_data[page][column];
                old_display_data[page][column] = display_data[page][column];
            }

            display_write(data, DISPLAY_WIDTH + 1);
        }

        render_type = RENDER_OPTIMISED;
    }
    else
    {
        for (unsigned char page = 0; page < DISPLAY_PAGES; page++)
        {
            if (!(edges_to_render & (1 << page))) continue;

            for (int column = 0; column < DISPLAY_WIDTH; column++)
            {
                if (old_display_data[page][column] != display_data[page][column])
                {
                    unsigned char command[4] = {
                        DISPLAY_COMMAND_MODE,
                        (0xB0 | page),
                        (0x10 | ((column+2) >> 4)), (0x0f & (column + 2))
                    };

                    display_write(command, 4);

                    unsigned char data[2] = {
                        DISPLAY_DATA_MODE,
                        display_data[page][column]
                    };

                    display_write(data, 2);

                    old_display_data[page][column] = display_data[page][column];
                }
            }
        }
    }

    edges_to_render = 0;
}

void display_put_pixel(int x, int y, int status)
{
    int page_number = y / DISPLAY_PAGES;

    if (status)
    {
        display_data[page_number][x] |=
                1 << (y - (page_number * DISPLAY_PAGE_HEIGHT));
    }
    else
    {
        display_data[page_number][x] &=
                ~(1 << (y - (page_number * DISPLAY_PAGE_HEIGHT)));
    }

    edges_to_render |= 1 << page_number;
}

void display_put_border()
{
    for(int i = 0; i < DISPLAY_PAGES; i++)
    {
        display_data[i][DISPLAY_WIDTH / 2] = 0x0f;
    }

    edges_to_render |= 0xff;
}

void display_put_player(int px, int py, int player_number)
{
    for(int y = 0; y < PLAYER_LENGTH; y++)
    {
        for(int x = 0; x < PLAYER_WIDTH; x++)
        {
            display_put_pixel((player_number == PLAYER_1) ? (px - x) : (px + x), py, 1);
        }
        py++;
    }
}

void display_move_player(int px, int py, int player_number, int direction)
{
    for(int x = 0; x < PLAYER_WIDTH; x++)
    {
        display_put_pixel((player_number == PLAYER_1) ? (px - x) : (px + x),
                          py, direction == DIRECTION_UP ? 1 : 0);
    }
    py++;

    py += PLAYER_LENGTH;

    for(int x = 0; x < PLAYER_WIDTH; x++)
    {
        display_put_pixel((player_number == PLAYER_1) ? (px - x) : (px + x),
                          py, direction == DIRECTION_DOWN ? 1 : 0);
    }
    py++;
}

void display_put_character(int px, int py, int d)
{
    int y;
    for(int x = 0; x < DIGIT_COLUMNS; x++)
    {
        for (y = 0; y < DIGIT_ROWS; y++)
        {
            display_put_pixel(px, py, display_characters[d][y][x]);
            py++;
        }
        py -= y;
        px++;
    }
}

void display_put_scores(int p1s, int p2s)
{
    display_put_character((DISPLAY_WIDTH / 4) - DIGIT_COLUMNS, 0, p1s);
    display_put_character((DISPLAY_WIDTH / 2) + (DISPLAY_WIDTH / 4) - DIGIT_COLUMNS, 0, p2s);
}
