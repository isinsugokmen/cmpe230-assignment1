#ifndef INVENTORY_H
#define INVENTORY_H

void inventory_add(const char *item_name, int count);


void init_inventory();

void add_ingredient(const char *name, int quantity);
void print_ingredients();
int get_ingredient_quantity(const char *name);
void remove_ingredient(const char *name, int quantity);

void add_potion(const char *name);
void remove_potion(const char *name);
int get_potion_quantity(const char *name);
void print_potions();

void add_trophy(const char *monster);
int has_trophies(const char *monster, int quantity);
void remove_trophy(const char *monster, int quantity);
void print_trophies();

#endif // INVENTORY_H
