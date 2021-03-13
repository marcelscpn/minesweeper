#include "board.h"
#include "strategy.h"
#include "command.h"

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

struct result{
    int outcome; //win = 1; give up = 0; lose = -1;
    int steps;
};

typedef struct result result;

void print_stats(int games, result* stats){
    int win_min = INT_MAX;
    int win_max = 0;
    float win_avg = 0;
    int win_games = 0;
    
    int gu_min = INT_MAX;
    int gu_max = 0;
    float gu_avg = 0;
    int gu_games = 0;
    
    int lose_min = INT_MAX;
    int lose_max = 0;
    float lose_avg = 0;
    int lose_games = 0;
    for(int i = 0; i < games; i++){
        switch((stats + i)->outcome){
        case 1:
            if((stats + i)->steps < win_min){
                win_min = (stats+i)->steps;
            }
            if((stats + i)-> steps > win_max){
                win_max = (stats+i)->steps;
            }
            win_avg += (stats+i)->steps;
            win_games += 1;
            break;
        case 0:
            if((stats + i)->steps < gu_min){
                gu_min = (stats+i)->steps;
            }
            if((stats + i)-> steps > gu_max){
                gu_max = (stats+i)->steps;
            }
            gu_avg += (stats+i)->steps;
            gu_games += 1;
            break;
        case -1:
            if((stats + i)->steps < lose_min){
                lose_min = (stats+i)->steps;
            }
            if((stats + i)-> steps > lose_max){
                lose_max = (stats+i)->steps;
            }
            lose_avg += (stats+i)->steps;
            lose_games += 1;
            break;
        }
    }
    win_avg = (win_games > 0) ? (float)win_avg / win_games : 0; 
    gu_avg = (gu_games > 0) ? (float)gu_avg / gu_games : 0;
    lose_avg = (lose_games > 0) ? (float)lose_avg / lose_games : 0;
    win_min = (win_min == INT_MAX) ? 0 : win_min; 
    gu_min= (gu_min == INT_MAX) ? 0 : gu_min;
    lose_min = (lose_min == INT_MAX) ? 0 : lose_min;
    printf("Outcome \t|Min_steps \t|Max_steps \t|Avg_steps \t|Games \t\t|Percentage\n");
    printf("===========================================================================================\n");
    printf("Win \t\t|%d \t\t|%d \t\t|%f \t|%d \t\t|%f\n", win_min, win_max, win_avg, win_games, ((float)win_games / games)*100);
    printf("Give Up\t\t|%d \t\t|%d \t\t|%f \t|%d \t\t|%f\n", gu_min, gu_max, gu_avg, gu_games, ((float)gu_games / games)*100);
    printf("Lost \t\t|%d \t\t|%d \t\t|%f \t|%d \t\t|%f\n", lose_min, lose_max, lose_avg, lose_games, ((float)lose_games / games)*100);
}




int main(int argc, char* argv[]){
    srand((unsigned)time(NULL));
    if(argc != 6){
		printf("Please specify board size, number of mines and number of games\n");
        // ./stats <mode> <height> <width> <games>
		return 1;
	}	
	int mode, h, w, num, games;
	sscanf(argv[1], "%d", &mode);
	sscanf(argv[2], "%d", &h);
	sscanf(argv[3], "%d", &w);
	sscanf(argv[4], "%d", &num);
    sscanf(argv[5], "%d", &games);
    result* stats = (result*)malloc(games*sizeof(result)); 
    board* mines;
    board* layover;
    for(int i = 0; i < games; i++){
        mines = create_new_board(h, w, num);
        layover = create_layover(h, w, -1);
        int steps = 0;
        command* cmd;
        strategy_ptr strategy;
        if(mode){
            strategy = select_strategy(mode);
        }
        else{
            printf("No stats for manual mode.\n");
            return 1;
        }
        int done = 0;
        while(!done){
            cmd = strategy(layover, steps);
            switch(parse_command(layover, mines, cmd)){
                case 0:
                    break;
                case -1:
                    break;
                case -2:
                    break;
                case -3:
                    break;
                case 1:
                    (stats + i)->outcome = -1;
                    goto RET;
                case 3:
                    (stats + i)->outcome = 0;
                    goto RET;
            }
            if(check_covered(layover)){
                (stats + i)->outcome = 1;
                goto RET;
            }
            steps++;
        }
        RET:
        (stats + i)->steps = steps;
        free_board(mines);
        free_board(layover);
    }
    print_stats(games, stats);
    free(stats);
    return 0;
}
