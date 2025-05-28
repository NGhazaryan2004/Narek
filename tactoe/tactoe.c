#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>

#define SHM_NAME "/ttt_shared"
#define SEM_NAME "/ttt_semaphore"
#define BOARD_SIZE 3

typedef struct {
    char board[BOARD_SIZE][BOARD_SIZE];
    int turn;          
    int game_over;     
    int winner;        
} GameState;


void print_board(GameState *state) {
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            char cell = state->board[i][j];
            printf(" %c ", (cell == '\0') ? '.' : cell);
            if (j < BOARD_SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < BOARD_SIZE - 1) printf("---+---+---\n");
    }
    printf("\n");
}

int check_winner(GameState *state, char symbol) {
    char (*b)[BOARD_SIZE] = state->board;
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (b[i][0] == symbol && b[i][1] == symbol && b[i][2] == symbol) return 1;
        if (b[0][i] == symbol && b[1][i] == symbol && b[2][i] == symbol) return 1;
    }
    if (b[0][0] == symbol && b[1][1] == symbol && b[2][2] == symbol) return 1;
    if (b[0][2] == symbol && b[1][1] == symbol && b[2][0] == symbol) return 1;
    return 0;
}


int check_draw(GameState *state) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            if (state->board[i][j] == '\0') return 0;
    return 1;
}


void cleanup(int is_player1) {
    if (is_player1) {
        shm_unlink(SHM_NAME);
        sem_unlink(SEM_NAME);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2 || (strcmp(argv[1], "player1") != 0 && strcmp(argv[1], "player2") != 0)) {
        fprintf(stderr, "using: %s player1|player2\n", argv[0]);
        exit(1);
    }

    int is_player1 = strcmp(argv[1], "player1") == 0;
    char symbol = is_player1 ? 'X' : 'O';
    int my_turn = is_player1 ? 1 : 2;

    
    int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (fd < 0) {
        perror("shm_open");
        exit(1);
    }

    ftruncate(fd, sizeof(GameState));
    GameState *state = mmap(NULL, sizeof(GameState), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (state == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    
    sem_t *sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    }

    
    if (is_player1) {
        sem_wait(sem);
        memset(state, 0, sizeof(GameState));
        state->turn = 1;
        sem_post(sem);
    }
    while (1) {
        sem_wait(sem);

        if (state->game_over) {
            sem_post(sem);
            break;
        }

        if (state->turn != my_turn) {
            sem_post(sem);
            sleep(1);
            continue;
        }

        print_board(state);

        int row, col;
        while (1) {
            printf("player %d (%c), make move ", my_turn, symbol);
            scanf("%d %d", &row, &col);
            if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && state->board[row][col] == '\0') {
                state->board[row][col] = symbol;
                break;
            } else {
                printf("ilegal move try again\n");
            }
        }

        if (check_winner(state, symbol)) {
            state->game_over = 1;
            state->winner = my_turn;
        } else if (check_draw(state)) {
            state->game_over = 2;
        } else {
            state->turn = 3 - my_turn;
        }

        sem_post(sem);
        sleep(1);
    }
    
    sem_wait(sem);
    print_board(state);
    if (state->game_over == 1) {
        printf("winner %d (%c)!\n", state->winner, (state->winner == 1 ? 'X' : 'O'));
    } else {
        printf("draw!\n");
    }
    sem_post(sem);

    cleanup(is_player1);
    sem_close(sem);
    munmap(state, sizeof(GameState));
    close(fd);

    return 0;
}
