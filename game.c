#include "game.h"
#include "entity.h"
#include "map.h"
#include <curses.h>
#include <stdlib.h>


/* - FUNCTION PROTOTYPES - */
// Get player input
int get_input(int *);
// Update the game state
int update_game(int *, entity *);
// Draw the screen
int draw_screen(const entity *, const tile_map *);
// Temporary error output function
void print_error(const char *);


/* - FUNCTION DEFINITIONS - */
int game_loop(void) {
    int input = '\0';
    entity *player = make_entity(30, 15, '@');
    tile_map *map = make_tile_map();
    if (player == NULL || map == NULL) return 0;
    draw_screen(player, map);
    while (input != 'Q') {
        get_input(&input);
        update_game(&input, player);
        draw_screen(player, map);
    }
    return 1;
}


int get_input(int *input) {
    if (!input) return 0;
    napms(50);
    flushinp();
    *input = getch();
    return 1;
}


int update_game(int *input, entity *player) {
    if (!input || !player) return 0;
    int dx = 0;
    int dy = 0;
    switch(*input) {
        case KEY_LEFT:
        case 'a':
            dx = -1;
            break;
        case KEY_RIGHT:
        case 'd':
            dx = 1;
            break;
        case KEY_DOWN:
        case 's':
            dy = 1;
            break;
        case KEY_UP:
        case 'w':
            dy = -1;
            break;
        case 'q':
            *input = 'Q';
        case 'Q':
            return 0;
        default:
            break;
    }
    move_entity(player, dx, dy);
    return 1;
}


int draw_screen(const entity *player, const tile_map *map) {
    if (!player || !map) return 0;
    clear();
    draw_tile_map(map);
    draw_entity(player);
    refresh();
    return 1;
}


void print_error(const char *str) {
    clear();
    mvprintw(0, 0, str);
    refresh();
    getch();
}
