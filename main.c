#include "config.h"
#include "display.h"
#include "timer.h"
#include "gpio.h"

int p1x;
int p1y;

int p2x;
int p2y;

int p1s;
int p2s;

int bx;
int by;

int bxc;
int byc;

int status;

#define PAUSED      0
#define RUNNING     1
#define END         2

int last_winner;

void reset_game()
{
    display_clear();

    p1x = PLAYER_1_START_X;
    p1y = PLAYER_1_START_Y;

    p2x = PLAYER_2_START_X;
    p2y = PLAYER_2_START_Y;

    bx = DISPLAY_WIDTH / 2;
    by = DISPLAY_HEIGHT / 2;

    display_put_player(p1x, p1y, PLAYER_1);
    display_put_player(p2x, p2y, PLAYER_2);

    bxc = (last_winner == PLAYER_2) ? -1 : 1;
    byc = 0;

    display_put_border();
    display_put_scores(p1s, p2s);

    status = PAUSED;
    display_set_render_type(RENDER_ALL);
    display_render();
}

void end_game()
{
    if (p1s == CHARACTER_WIN)
        p2s = CHARACTER_LOSE;
    else
        p1s = CHARACTER_LOSE;

    display_put_scores(p1s, p2s);

    status = END;
    display_set_render_type(RENDER_ALL);
    display_render();

    p1s = 0;
    p2s = 0;
}

int main()
{
    GPIO_PORT_0_DDR = 0;
    GPIO_PORT_1_DDR = 0;

    display_init();
    display_clear();
    display_switch_on();

    p1s = 0;
    p2s = 0;

    reset_game();

    display_render();

    int erase_old_ball = 1;

    for(;;)
    {
        TIMER_setup_delay(0, DELAY);

        if (GPIO_PORT_0_IO(PLAYER_1_BUTTON_UP) || GPIO_PORT_0_IO(PLAYER_1_BUTTON_DOWN) ||
                GPIO_PORT_0_IO(PLAYER_2_BUTTON_UP) || GPIO_PORT_0_IO(PLAYER_2_BUTTON_DOWN))
        {
            if (status == END)
            {
                reset_game();
            }
            else
            {
                status = RUNNING;
            }
        }

        // Player 1
        if (GPIO_PORT_0_IO(PLAYER_1_BUTTON_UP))
        {
            if (p1y > 0)
            {
                display_move_player(p1x, p1y, PLAYER_1, DIRECTION_UP);
                p1y--;
            }
        }
        else if (GPIO_PORT_0_IO(PLAYER_1_BUTTON_DOWN))
        {
            if (p1y + PLAYER_LENGTH < DISPLAY_HEIGHT - 1)
            {
                display_move_player(p1x, p1y, PLAYER_1, DIRECTION_DOWN);
                p1y++;
            }
        }

        // Player 2
        if (GPIO_PORT_0_IO(PLAYER_2_BUTTON_UP))
        {
            if (p2y > 0)
            {
                display_move_player(p2x, p2y, PLAYER_2, DIRECTION_UP);
                p2y--;
            }
        }
        else if (GPIO_PORT_0_IO(PLAYER_2_BUTTON_DOWN))
        {
            if (p2y + PLAYER_LENGTH < DISPLAY_HEIGHT - 1)
            {
                display_move_player(p2x, p2y, PLAYER_2, DIRECTION_DOWN);
                p2y++;
            }
        }

        if (status != RUNNING) continue;

        if (bx == p2x)
        {
            int ydiff = by - p2y;

            if (ydiff >= 0 && ydiff <= PLAYER_LENGTH)
            {
                erase_old_ball = 0;
                bxc = -1;

                if (ydiff < PLAYER_LENGTH / 2)
                {
                    byc = -1;
                }
                else if (ydiff > PLAYER_LENGTH / 2)
                {
                    byc = 1;
                }
                else
                {
                    byc = 0;
                }
            }
        }
        else if (bx >= (DISPLAY_WIDTH - 1))
        {
            last_winner = PLAYER_1;
            (++p1s == 10) ? end_game() : reset_game();
            continue;
        }
        else if (bx == p1x)
        {
            int ydiff = by - p1y;

            if (ydiff >= 0 && ydiff <= PLAYER_LENGTH)
            {
                erase_old_ball = 0;
                bxc = 1;

                if (ydiff < PLAYER_LENGTH / 2)
                {
                    byc = -1;
                }
                else if (ydiff > PLAYER_LENGTH / 2)
                {
                    byc = 1;
                }
                else
                {
                    byc = 0;
                }
            }
        }
        else if (bx <= 0)
        {
            last_winner = PLAYER_2;
            (++p2s == 10) ? end_game() : reset_game();
            continue;
        }
        else if (by < 0 || by >= DISPLAY_HEIGHT - 1)
        {
            if (byc == -1)
            {
                byc = 1;
            }
            else
            {
                byc = -1;
            }
        }

        if (erase_old_ball && !(bx == (DISPLAY_WIDTH / 2) && (by % DISPLAY_PAGE_HEIGHT < 4)))
        {
            display_put_pixel(bx, by, 0);
        }

        if (by <= 8)
        {
            display_put_scores(p1s, p2s);
        }


        bx += bxc;
        by += byc;
        display_put_pixel(bx, by, 1);

        erase_old_ball = 1;

        display_render();

    }
}

