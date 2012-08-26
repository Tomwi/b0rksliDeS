#ifndef T_INPUT_H
#define T_INPUT_H

extern int keysHold, keysPres, keysReleased;

unsigned int bork_speed=1;

void readInput(void);
void parseInput(int* dx, int* dy);

#endif /* T_INPUT_H */
