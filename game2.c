/* ============================================================
   CONSOLE CAR GAME
   A simple top-view (bird's-eye) driving game made with ASCII
   characters. Move the car between 3 lanes to catch falling
   stars (*) and increase your score!

   Controls:
     1 = move to LEFT lane
     2 = move to MIDDLE lane
     3 = move to RIGHT lane
     Q = quit the game

   Compile with GCC (Dev-C++ / Code::Blocks on Windows):
     gcc car_game.c -o car_game.exe
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>     /* kbhit(), getch() - non-blocking keyboard input */
#include <windows.h>   /* Sleep(), console cursor functions             */
#include <time.h>      /* time() - used to seed random numbers          */

/* ------------------------------------------------------------
   SCREEN / ROAD LAYOUT CONSTANTS
   These numbers control the size and shape of the game screen.
   ------------------------------------------------------------ */
#define COLS        32   /* width of the drawing buffer (characters)  */
#define ROWS        18   /* height of the drawing buffer (rows)       */

#define ROAD_LEFT    2   /* column of the LEFT border of the road     */
#define ROAD_RIGHT  30   /* column of the RIGHT border of the road    */

#define DIVIDER_1   12   /* column of the first lane divider  ( | )   */
#define DIVIDER_2   21   /* column of the second lane divider ( | )   */

#define CAR_WIDTH    7   /* width of the car ASCII art                */
#define CAR_HEIGHT   5   /* height of the car ASCII art                */
#define CAR_TOP     12   /* row where the top of the car is drawn     */
#define CAR_BOTTOM  (CAR_TOP + CAR_HEIGHT - 1)  /* bottom row of car  */

/* ------------------------------------------------------------
   GLOBAL VARIABLES
   Kept simple (no structs/pointers) so it stays beginner friendly.
   ------------------------------------------------------------ */
char screen[ROWS][COLS + 1]; /* the drawing buffer (+1 for '\0')      */

int carLane;        /* 0 = left, 1 = middle, 2 = right                */
int starLane;        /* which lane the falling star is in             */
int starRow;         /* current row (height) of the falling star      */
int score;            /* player's score                                */
int scrollOffset;     /* used to animate the scrolling lane dividers   */

/* Center column of each lane (used for both car and star placement) */
int laneCenter[3] = { 8, 17, 26 };

/* The car's ASCII art, 5 rows tall, 7 characters wide (see prompt) */
char carArt[CAR_HEIGHT][CAR_WIDTH + 1] = {
    "  /^^\\ ",
    " |[][]|",
    " |[][]|",
    " |____|",
    "  O  O "
};

/* ------------------------------------------------------------
   FUNCTION PROTOTYPES
   ------------------------------------------------------------ */
void gotoxy(int x, int y);
void hideCursor(void);
void clearBuffer(void);
void drawRoad(void);
void drawCar(void);
void drawStars(void);
void moveStars(void);
int  checkCollision(void);
void input(int *running);
void updateGame(void);
void spawnStar(void);
void render(void);

/* ============================================================
   MAIN FUNCTION - the game loop
   ============================================================ */
int main(void)
{
    int running = 1;

    srand((unsigned int) time(NULL));  /* seed random numbers          */
    hideCursor();
    system("cls");                     /* clear the console ONCE       */

    /* --- initialize game state --- */
    carLane = 1;      /* start in the middle lane */
    score = 0;
    scrollOffset = 0;
    spawnStar();       /* place the first star      */

    /* --- main game loop --- */
    while (running) {
        input(&running);     /* read keyboard (non-blocking)     */
        updateGame();         /* move star, check collision, etc. */
        render();              /* draw everything to the console   */

        Sleep(150);            /* controls the game speed          */
    }

    gotoxy(0, ROWS + 3);
    printf("\nGame Over! Final Score: %d\n", score);

    return 0;
}

/* ============================================================
   gotoxy - moves the console cursor to column x, row y
   (This lets us redraw without clearing the whole screen,
   which keeps the animation smooth and flicker-free.)
   ============================================================ */
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/* ============================================================
   hideCursor - hides the blinking text cursor for a cleaner look
   ============================================================ */
void hideCursor(void)
{
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}

/* ============================================================
   clearBuffer - fills the drawing buffer with blank spaces
   ============================================================ */
void clearBuffer(void)
{
    int r, c;
    for (r = 0; r < ROWS; r++) {
        for (c = 0; c < COLS; c++) {
            screen[r][c] = ' ';
        }
        screen[r][COLS] = '\0';   /* end each row as a proper string */
    }
}

/* ============================================================
   drawRoad - draws the road borders and animated lane dividers
   ============================================================ */
void drawRoad(void)
{
    int r, c;

    /* top border row: +-----------------------------+ */
    for (c = ROAD_LEFT; c <= ROAD_RIGHT; c++) {
        screen[0][c] = '-';
    }
    screen[0][ROAD_LEFT]  = '+';
    screen[0][ROAD_RIGHT] = '+';

    /* bottom border row */
    for (c = ROAD_LEFT; c <= ROAD_RIGHT; c++) {
        screen[ROWS - 1][c] = '-';
    }
    screen[ROWS - 1][ROAD_LEFT]  = '+';
    screen[ROWS - 1][ROAD_RIGHT] = '+';

    /* side walls + animated dashed dividers for the interior rows */
    for (r = 1; r < ROWS - 1; r++) {
        screen[r][ROAD_LEFT]  = '|';
        screen[r][ROAD_RIGHT] = '|';

        /* the (row + scrollOffset) % 2 trick makes the dashes
           appear to move downward each frame */
        if ((r + scrollOffset) % 2 == 0) {
            screen[r][DIVIDER_1] = '|';
            screen[r][DIVIDER_2] = '|';
        }
    }
}

/* ============================================================
   drawCar - draws the car ASCII art at the player's current lane
   ============================================================ */
void drawCar(void)
{
    int i, j;
    int carLeft = laneCenter[carLane] - (CAR_WIDTH / 2);

    for (i = 0; i < CAR_HEIGHT; i++) {
        for (j = 0; j < CAR_WIDTH; j++) {
            screen[CAR_TOP + i][carLeft + j] = carArt[i][j];
        }
    }
}

/* ============================================================
   drawStars - draws the falling star onto the buffer
   ============================================================ */
void drawStars(void)
{
    if (starRow >= 1 && starRow <= ROWS - 2) {
        screen[starRow][laneCenter[starLane]] = '*';
    }
}

/* ============================================================
   spawnStar - creates a new star at the top, in a random lane
   ============================================================ */
void spawnStar(void)
{
    starLane = rand() % 3;   /* random lane: 0, 1, or 2 */
    starRow  = 1;              /* start just below the top border */
}

/* ============================================================
   moveStars - moves the falling star down by one row each tick.
   If it goes past the car without being caught, spawn a new one.
   ============================================================ */
void moveStars(void)
{
    starRow++;

    if (starRow > CAR_BOTTOM) {
        spawnStar();   /* star missed the car - start a new one */
    }
}

/* ============================================================
   checkCollision - checks if the car has caught the star.
   Returns 1 if caught, 0 otherwise.
   ============================================================ */
int checkCollision(void)
{
    if (starRow >= CAR_TOP && starRow <= CAR_BOTTOM && starLane == carLane) {
        score++;
        spawnStar();   /* star collected - start a new one */
        return 1;
    }
    return 0;
}

/* ============================================================
   input - reads keyboard input WITHOUT blocking the game loop.
   kbhit() checks if a key was pressed; if not, we just continue.
   ============================================================ */
void input(int *running)
{
    if (kbhit()) {
        char key = getch();

        switch (key) {
            case '1':
                carLane = 0;   /* left lane   */
                break;
            case '2':
                carLane = 1;   /* middle lane */
                break;
            case '3':
                carLane = 2;   /* right lane  */
                break;
            case 'q':
            case 'Q':
                *running = 0;  /* stop the game loop */
                break;
            default:
                /* ignore any other key */
                break;
        }
    }
}

/* ============================================================
   updateGame - updates all moving parts of the game each frame
   ============================================================ */
void updateGame(void)
{
    moveStars();
    checkCollision();
    scrollOffset++;   /* advances the divider scroll animation */
}

/* ============================================================
   render - builds the frame in the buffer and prints it
   ============================================================ */
void render(void)
{
    int r;

    clearBuffer();
    drawRoad();
    drawStars();
    drawCar();

    /* print the score and controls above the road */
    gotoxy(0, 0);
    printf("SCORE: %d      \n", score);
    printf("Controls: 1=Left  2=Middle  3=Right  Q=Quit      \n");

    /* print the road/car/star buffer below the score lines */
    for (r = 0; r < ROWS; r++) {
        gotoxy(0, r + 2);
        printf("%s", screen[r]);
    }
}