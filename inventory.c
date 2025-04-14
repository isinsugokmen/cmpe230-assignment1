#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"

// Envanterdeki malzemeleri temsil eden bağlı liste yapısı
typedef struct Ingredient {
    char name[32];
    int quantity;
    struct Ingredient *next;
} Ingredient;

// Envanterdeki iksirleri temsil eden bağlı liste yapısı
typedef struct Potion {
    char name[64];
    int quantity;
    struct Potion *next;
} Potion;

// Envanterdeki trophyleri temsil eden yapı
typedef struct Trophy {
    char monster[64];
    int quantity;
    struct Trophy *next;
} Trophy;

// Liste başları (global pointerlar)
static Ingredient *ingredient_head = NULL;
static Potion *potion_head = NULL;
static Trophy *trophy_head = NULL;

// Envanteri başlat (başlangıçta listeler boş)
void init_inventory() {
    ingredient_head = NULL;
    potion_head = NULL;
    trophy_head = NULL;
}

// Yeni malzeme ekle veya varsa miktarını artır
void add_ingredient(const char *name, int quantity) {
    Ingredient *current = ingredient_head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            current->quantity += quantity;
            return;
        }
        current = current->next;
    }

    Ingredient *new_ing = malloc(sizeof(Ingredient));
    strncpy(new_ing->name, name, sizeof(new_ing->name));
    new_ing->quantity = quantity;
    new_ing->next = ingredient_head;
    ingredient_head = new_ing;
}

// Tüm malzemeleri yazdırır
void print_ingredients() {
    if (!ingredient_head) {
        printf("None\n");
        return;
    }

    Ingredient *current = ingredient_head;
    while (current != NULL) {
        printf("%d %s", current->quantity, current->name);
        if (current->next) printf(", ");
        current = current->next;
    }
    printf("\n");
}

// Belirli bir malzemenin miktarını getirir
int get_ingredient_quantity(const char *name) {
    Ingredient *current = ingredient_head;
    while (current) {
        if (strcmp(current->name, name) == 0)
            return current->quantity;
        current = current->next;
    }
    return 0;
}

// Malzeme miktarını azalt (eksiltilmiş hali negatifse sıfıra çeker)
void remove_ingredient(const char *name, int quantity) {
    Ingredient *current = ingredient_head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            current->quantity -= quantity;
            if (current->quantity < 0) current->quantity = 0;
            return;
        }
        current = current->next;
    }
}

// Yeni iksir ekle veya varsa miktarını artırır
void add_potion(const char *name) {
    Potion *current = potion_head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            current->quantity++;
            return;
        }
        current = current->next;
    }

    Potion *new_potion = malloc(sizeof(Potion));
    strncpy(new_potion->name, name, sizeof(new_potion->name));
    new_potion->quantity = 1;
    new_potion->next = potion_head;
    potion_head = new_potion;
}

// İksirleri yazdırır
void print_potions() {
    if (!potion_head) {
        printf("None\n");
        return;
    }

    Potion *current = potion_head;
    while (current) {
        printf("%d %s", current->quantity, current->name);
        if (current->next) printf(", ");
        current = current->next;
    }
    printf("\n");
}

// Belirli bir iksirin sayısını getirir
int get_potion_quantity(const char *name) {
    Potion *current = potion_head;
    while (current) {
        if (strcmp(current->name, name) == 0)
            return current->quantity;
        current = current->next;
    }
    return 0;
}

// Bir iksir kullandıysa miktarını azaltır
void remove_potion(const char *name) {
    Potion *current = potion_head;
    while (current) {
        if (strcmp(current->name, name) == 0) {
            current->quantity--;
            if (current->quantity < 0) current->quantity = 0;
            return;
        }
        current = current->next;
    }
}

// trophy ekle veya varsa miktarını artırır
void add_trophy(const char *monster) {
    Trophy *current = trophy_head;
    while (current) {
        if (strcmp(current->monster, monster) == 0) {
            current->quantity++;
            return;
        }
        current = current->next;
    }

    Trophy *new_trophy = malloc(sizeof(Trophy));
    strncpy(new_trophy->monster, monster, sizeof(new_trophy->monster));
    new_trophy->quantity = 1;
    new_trophy->next = trophy_head;
    trophy_head = new_trophy;
}

// Belirli bir canavardan istenilen sayıda ganimet var mı kontrol eder
int has_trophies(const char *monster, int quantity) {
    Trophy *current = trophy_head;
    while (current) {
        if (strcmp(current->monster, monster) == 0) {
            return current->quantity >= quantity;
        }
        current = current->next;
    }
    return 0;
}

// Belirli sayıda ganimeti siler
void remove_trophy(const char *monster, int quantity) {
    Trophy *current = trophy_head;
    while (current) {
        if (strcmp(current->monster, monster) == 0) {
            current->quantity -= quantity;
            if (current->quantity < 0) current->quantity = 0;
            return;
        }
        current = current->next;
    }
}

// Ganimet listesini yazdırır
void print_trophies() {
    if (!trophy_head) {
        printf("None\n");
        return;
    }

    Trophy *current = trophy_head;
    while (current) {
        printf("%d %s", current->quantity, current->monster);
        if (current->next) printf(", ");
        current = current->next;
    }
    printf("\n");
}
