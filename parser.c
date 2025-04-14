#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "parser.h"
#include "inventory.h"
#include "alchemy.h"
#include "bestiary.h"

// Kullanıcıdan gelen komutu çözümleyip uygun işlemi başlatan fonksiyon
void parse_and_execute(const char *input) {
    printf("INPUT RECEIVED: %s\n", input);

    if (strstr(input, "Geralt loots") == input) {
        handle_loot(input);
    } else if (strstr(input, "Geralt brews") == input) {
        handle_brew(input);
    } else if (strstr(input, "Geralt trades") == input) {
        handle_trade(input);
    } else if (strstr(input, "Geralt learns") == input && strstr(input, "potion consists of")) {
        handle_learn_formula(input);
    } else if (strstr(input, "Geralt learns") == input && strstr(input, "is effective against")) {
        handle_learn_effectiveness(input);
    } else if (strstr(input, "Geralt encounters") == input) {
        handle_encounter(input);
    } else if (strstr(input, "Total ingredient") == input) {
        print_ingredients();
    } else if (strstr(input, "Total potion") == input) {
        print_potions();
    } else if (strstr(input, "Total trophy") == input) {
        print_trophies();
    } else if (strstr(input, "What is in") == input) {
        handle_what_is_in(input);
    } else if (strstr(input, "What is effective against") == input) {
        handle_what_is_effective(input);
    } else {
        printf("INVALID\n");
    }
}

// Geralt’ın topladığı malzemeleri envantere ekleyen fonksiyon
void handle_loot(const char *input) {
    const char *loot_str = strstr(input, "loots");
    if (!loot_str) return;

    loot_str += 6; // "loots " kelimesini atlıyoruz

    char buffer[256];
    strncpy(buffer, loot_str, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    char *token = strtok(buffer, ",");
    while (token != NULL) {
        int count;
        char name[64];

        if (sscanf(token, "%d %s", &count, name) == 2) {
            add_ingredient(name, count);

        }

        token = strtok(NULL, ",");
    }
}

// Geralt bir iksir üretmek istediğinde çağrılır
void handle_brew(const char *input) {
    char potion_name[64];
    sscanf(input, "Geralt brews %s", potion_name);

    brew_potion(potion_name); // Üretim fonksiyonunu çağır
}
// Geralt’ın bir eşyayı başka bir eşya ile takas ettiği kısım
void handle_trade(const char *input) {
    int give_count, get_count;
    char give_item[64], get_item[64];

    sscanf(input, "Geralt trades %d %s for %d %s", &give_count, give_item, &get_count, get_item);

    // Envanterde yeterli malzeme var mı kontrol eder
    if (get_ingredient_quantity(give_item) >= give_count) {
        remove_ingredient(give_item, give_count);
        add_ingredient(get_item, get_count);
        printf("Trade completed: %d %s -> %d %s\n", give_count, give_item, get_count, get_item);
    } else {
        printf("Not enough %s to trade\n", give_item);
    }
}
// Yeni bir iksir tarifi öğrenildiğinde çalışır
void handle_learn_formula(const char *input) {
    char potion_name[64];
    char ingredients[5][32];
    int quantities[5];
    int count = 0;

    // "Geralt learns Swallow potion consists of" kısmından potion_name'i al
    sscanf(input, "Geralt learns %s potion consists of", potion_name);

    // "consists of" ifadesinden sonrasını ayıkla
    const char *rest = strstr(input, "consists of");
    if (!rest) return;

    rest += strlen("consists of ");
    char buffer[256];
    strncpy(buffer, rest, sizeof(buffer));
    buffer[sizeof(buffer) - 1] = '\0';

    // Malzeme ve miktarları ayrıştırır
    char *token = strtok(buffer, ",");
    while (token && count < 5) {
        sscanf(token, "%d %s", &quantities[count], ingredients[count]);
        count++;
        token = strtok(NULL, ",");
    }

    // Formülü kaydeder
    learn_potion_formula(potion_name, ingredients, quantities, count);
}
// Geralt, bir canavara karşı hangi item'in etkili olduğunu öğrendiğinde çalışır
void handle_learn_effectiveness(const char *input) {
    char monster[64], item[64];
    sscanf(input, "Geralt learns %s is effective against %s", monster, item);
    int is_sign = 0;  

    learn_effectiveness(monster, item, is_sign);
}
// Karşılaşılan yaratığa karşı hazır olup olmadığını kontrol eder
void handle_encounter(const char *input) {
    char monster[64];
    sscanf(input, "Geralt encounters %s", monster);

    if (has_effective_item(monster)) {
        printf("Geralt is ready for the encounter\n");
    } else {
        printf("Geralt is NOT ready\n");
    }
}
// Bir iksirin içinde hangi malzemeler var, onu yazdırır
void handle_what_is_in(const char *input) {
    char potion_name[64];
    sscanf(input, "What is in %s", potion_name);
    print_potion_formula(potion_name);
}
// Bir yaratığa karşı etkili olan iksirleri listeler
void handle_what_is_effective(const char *input) {
    char monster[64];
    char effective_potions[32][64];
    int count = 0;

    sscanf(input, "What is effective against %s", monster);
    get_effective_potions(monster, effective_potions, &count);

    if (count == 0) {
        printf("None\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("%s", effective_potions[i]);
        if (i < count - 1)
            printf(", ");
    }
    printf("\n");
}



