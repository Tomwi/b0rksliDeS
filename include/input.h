#ifndef T_INPUT_H
#define T_INPUT_H

extern int keysHold, keysPres, keysReleased;

void readInput(void);
void parseInput(int* dx, int* dy);

#endif /* T_INPUT_H */
