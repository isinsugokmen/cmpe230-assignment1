#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bestiary.h"
#include "inventory.h"

typedef struct EffectNode {
    char item[64];
    int is_sign;
    struct EffectNode *next;
} EffectNode;

typedef struct MonsterEntry {
    char monster[64];
    EffectNode *effects;
    struct MonsterEntry *next;
} MonsterEntry;

static MonsterEntry *bestiary_head = NULL;

void init_bestiary() {
    bestiary_head = NULL;
}

void learn_effectiveness(const char *monster, const char *item, int is_sign) {
    MonsterEntry *current = bestiary_head;

    while (current) {
        if (strcmp(current->monster, monster) == 0) {
            EffectNode *e = current->effects;
            while (e) {
                if (strcmp(e->item, item) == 0 && e->is_sign == is_sign) {
                    printf("Already known effectiveness\n");
                    return;
                }
                e = e->next;
            }

            EffectNode *new_eff = malloc(sizeof(EffectNode));
            strncpy(new_eff->item, item, sizeof(new_eff->item));
            new_eff->is_sign = is_sign;
            new_eff->next = current->effects;
            current->effects = new_eff;

            printf("Bestiary entry updated: %s\n", monster);
            return;
        }
        current = current->next;
    }

    // Yeni monster entry
    MonsterEntry *new_monster = malloc(sizeof(MonsterEntry));
    strncpy(new_monster->monster, monster, sizeof(new_monster->monster));
    new_monster->effects = NULL;
    new_monster->next = bestiary_head;
    bestiary_head = new_monster;

    EffectNode *new_eff = malloc(sizeof(EffectNode));
    strncpy(new_eff->item, item, sizeof(new_eff->item));
    new_eff->is_sign = is_sign;
    new_eff->next = NULL;
    new_monster->effects = new_eff;

    printf("New bestiary entry added: %s\n", monster);
}

int has_effective_item(const char *monster) {
    MonsterEntry *m = bestiary_head;
    while (m) {
        if (strcmp(m->monster, monster) == 0) {
            EffectNode *e = m->effects;
            while (e) {
                if (e->is_sign) return 1;
                if (get_potion_quantity(e->item) > 0) return 1;
                e = e->next;
            }
            return 0;
        }
        m = m->next;
    }
    return 0;
}

void get_effective_potions(const char *monster, char items[][64], int *count) {
    *count = 0;
    MonsterEntry *m = bestiary_head;
    while (m) {
        if (strcmp(m->monster, monster) == 0) {
            EffectNode *e = m->effects;
            while (e) {
                if (!e->is_sign && get_potion_quantity(e->item) > 0) {
                    strncpy(items[*count], e->item, 64);
                    (*count)++;
                }
                e = e->next;
            }
            return;
        }
        m = m->next;
    }
}
