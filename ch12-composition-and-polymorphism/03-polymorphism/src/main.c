#include <stdio.h>

typedef struct Animal Animal;

struct Animal {
    void (*sound)(const Animal *self);
};

void base_sound(const Animal *self) {
    (void)self;
    printf("The animal makes a sound...\n");
}

void pig_sound(const Animal *self) {
    (void)self;
    printf("The pig says: oink oink!\n");
}

void dog_sound(const Animal *self) {
    (void)self;
    printf("The dog says: bow wow!\n");
}

void make_sound(const Animal *animal) {
    animal->sound(animal);
}

int main(void) {
    Animal base = {base_sound};
    Animal pig = {pig_sound};
    Animal dog = {dog_sound};

    make_sound(&base);
    make_sound(&pig);
    make_sound(&dog);

    // Try: set pig to {base_sound}, and predict the second line of output before you press Run.
    return 0;
}
