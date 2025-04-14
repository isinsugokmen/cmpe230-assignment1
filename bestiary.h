#ifndef BESTIARY_H
#define BESTIARY_H

void init_bestiary();
void learn_effectiveness(const char *monster, const char *item, int is_sign);
int has_effective_item(const char *monster);
void get_effective_potions(const char *monster, char items[][64], int *count);

#endif // BESTIARY_H
