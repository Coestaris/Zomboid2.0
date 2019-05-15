//
// Created by maxim on 5/13/19.
//

#ifndef ZOMBOID2_SCORE_H
#define ZOMBOID2_SCORE_H

#define MAX_LEVELS 13
#define MAX_ENEMIES 6
#define COMPLETED 0.9

typedef struct _gameMobData {
    int wave;
    int killed[MAX_ENEMIES];

} gameMobData_t;

int mobCount(int level);
void recieveScore(int level, int id);

#endif //ZOMBOID2_SCORE_H
