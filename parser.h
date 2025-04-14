#ifndef PARSER_H
#define PARSER_H
void handle_loot(const char *input);
void handle_brew(const char *input);
void handle_trade(const char *input);
void handle_learn_formula(const char *input);
void handle_learn_effectiveness(const char *input);
void handle_encounter(const char *input);
void handle_what_is_in(const char *input);
void handle_what_is_effective(const char *input);


void parse_and_execute(const char *input);

#endif // PARSER_H
