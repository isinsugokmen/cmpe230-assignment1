#ifndef ALCHEMY_H
#define ALCHEMY_H

typedef struct PotionFormula {
    char potion_name[64];
    char ingredients[5][32];
    int quantities[5];
    int ingredient_count;
    struct PotionFormula *next;
} PotionFormula;

extern PotionFormula *alchemy_head;

void init_alchemy();
void learn_potion_formula(const char *potion_name, const char ingredients[][32], const int *quantities, int ingredient_count);
int brew_potion(const char *potion_name);
void print_potion_formula(const char *potion_name);

#endif // ALCHEMY_H
