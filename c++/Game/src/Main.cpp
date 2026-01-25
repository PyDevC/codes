#include <iostream>

struct Workers {
  enum {
    MAGE,
    ARCHER,
    RAWHAMMER,
  } type;
  union {
    struct {
      float power;
      float short_range_power;
      float long_range_power;
      float health;
      char *weapon;
      char *first_skill;
      char *power_skill;
      char *general_skill;
    } mage;

    struct {
      float power;
      float power_shot_range;
      float number_arrow;
      float shooting_range;
      char *first_skill;
      char *power_skill;
      char *general_skill;
    } archer;

    struct {
      float power;
      float meele_power;
      float weapon_efficiency;
      float number_arrow;
      float shooting_range;
      char *first_skill;
      char *power_skill;
      char *general_skill;
    } raw_hammer;
  } player;
};

int main(void) {
  Workers worker1 = {.type = Workers::MAGE, .player = {.mage = {}}};
  return 0;
}
