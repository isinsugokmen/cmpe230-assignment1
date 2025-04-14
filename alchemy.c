#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "alchemy.h"
#include "inventory.h"



PotionFormula *alchemy_head = NULL;


void init_alchemy() {
    alchemy_head = NULL;
}

/**
 * Yeni bir iksir tarifi öğrenir.
 * Aynı iksir daha önce öğrenildiyse uyarı verir.
 */
void learn_potion_formula(const char *potion_name, const char ingredients[][32], const int *quantities, int ingredient_count) {
    PotionFormula *current = alchemy_head;
// Daha önce bu iksir öğrenilmiş mi kontrolü
    while (current) {
        if (strcmp(current->potion_name, potion_name) == 0) {
            printf("Already known formula\n");
            return;
        }
        current = current->next;
    }
// Yeni formül oluşturuluyor
    PotionFormula *new_formula = malloc(sizeof(PotionFormula));
    strncpy(new_formula->potion_name, potion_name, sizeof(new_formula->potion_name));
    new_formula->ingredient_count = ingredient_count;

    for (int i = 0; i < ingredient_count; i++) {
        strncpy(new_formula->ingredients[i], ingredients[i], sizeof(new_formula->ingredients[i]));
        new_formula->quantities[i] = quantities[i];
    }
// Liste başına ekleniyor
    new_formula->next = alchemy_head;
    alchemy_head = new_formula;

    printf("New alchemy formula obtained: %s\n", potion_name);
}
/**
 * Belirtilen iksiri üretmeye çalışır.
 * Malzeme yeterliyse iksir oluşturulur ve stoklara eklenir.
 */
int brew_potion(const char *potion_name) {
    PotionFormula *current = alchemy_head;

    while (current) {
        if (strcmp(current->potion_name, potion_name) == 0) {
            // Malzemelerin yeterli olup olmadığı kontrol ediliyor
            for (int i = 0; i < current->ingredient_count; i++) {
                if (get_ingredient_quantity(current->ingredients[i]) < current->quantities[i]) {
                    printf("Not enough ingredients\n");
                    return 0;
                }
            }
// Malzemeler stoktan düşülüyor
            for (int i = 0; i < current->ingredient_count; i++) {
                remove_ingredient(current->ingredients[i], current->quantities[i]);
            }
// İksir başarıyla eklendi
            add_potion(potion_name);
            printf("Alchemy item created: %s\n", potion_name);
            return 1;
        }
        current = current->next;
    }
  // Formül bilinmiyorsa
    printf("No formula for %s\n", potion_name);
    return 0;
}
/**
 * Belirtilen iksirin formülünü ekrana yazdırır.
 * Malzemeler ve miktarları gösterilir.
 */
void print_potion_formula(const char *potion_name) {
    PotionFormula *current = alchemy_head;

    while (current) {
        if (strcmp(current->potion_name, potion_name) == 0) {
            for (int i = 0; i < current->ingredient_count; i++) {
                printf("%d %s", current->quantities[i], current->ingredients[i]);
                if (i < current->ingredient_count - 1) printf(", ");
            }
            printf("\n");
            return;
        }
        current = current->next;
    }

    printf("No formula for %s\n", potion_name);
}
