#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

// Define the Player struct
typedef struct {
    int hp;
    int maxHp;
    int gold;
    int exp;
    int level;
    int potions;  // Inventory: number of potions
    int elixirs;  // Inventory: number of elixirs
} Player;

// Function prototypes
void saveGame(Player *player);
int loadGame(Player *player);
void townHub(Player *player);
void generalStore(Player *player);
void inn(Player *player);
void dungeon(Player *player);
void levelUp(Player *player);
int puzzleLevel1();
int puzzleLevel2();
int puzzleLevel3();
int puzzleLevel4();
int puzzleLevel5();
void displayStats(Player *player);

int main() {
    Player player;
    srand(time(NULL));  // Seed random number generator

    // Try to load game, if not, start new
    if (!loadGame(&player)) {
        player.hp = 100;
        player.maxHp = 100;
        player.gold = 50;
        player.exp = 0;
        player.level = 1;
        player.potions = 0;
        player.elixirs = 0;
        printf("Welcome to The Alchemist’s Trade & Trials! Starting a new game.\n");
    } else {
        printf("Game loaded successfully!\n");
    }

    int choice;
    while (1) {
        displayStats(&player);
        printf("\nMain Menu:\n");
        printf("1. Visit Town Hub\n");
        printf("2. Enter Dungeon\n");
        printf("3. Save Game\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                townHub(&player);
                break;
            case 2:
                dungeon(&player);
                break;
            case 3:
                saveGame(&player);
                printf("Game saved!\n");
                break;
            case 4:
                printf("Exiting game. Goodbye!\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

// Display player stats
void displayStats(Player *player) {
    printf("\n--- Player Stats ---\n");
    printf("HP: %d/%d\n", player->hp, player->maxHp);
    printf("Gold: %d\n", player->gold);
    printf("EXP: %d\n", player->exp);
    printf("Level: %d\n", player->level);
    printf("Potions: %d\n", player->potions);
    printf("Elixirs: %d\n", player->elixirs);
}

// Save game to file
void saveGame(Player *player) {
    FILE *file = fopen("save.txt", "w");
    if (file == NULL) {
        printf("Error saving game.\n");
        return;
    }
    fprintf(file, "%d %d %d %d %d %d %d\n", player->hp, player->maxHp, player->gold, player->exp, player->level, player->potions, player->elixirs);
    fclose(file);
}

// Load game from file, return 1 if successful, 0 otherwise
int loadGame(Player *player) {
    FILE *file = fopen("save.txt", "r");
    if (file == NULL) {
        return 0;
    }
    fscanf(file, "%d %d %d %d %d %d %d", &player->hp, &player->maxHp, &player->gold, &player->exp, &player->level, &player->potions, &player->elixirs);
    fclose(file);
    return 1;
}

// Town Hub menu
void townHub(Player *player) {
    int choice;
    while (1) {
        printf("\n--- Town Hub ---\n");
        printf("1. General Store\n");
        printf("2. Inn\n");
        printf("3. Back to Main Menu\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                generalStore(player);
                break;
            case 2:
                inn(player);
                break;
            case 3:
                return;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

// General Store: Buy/Sell items
void generalStore(Player *player) {
    int choice, quantity;
    printf("\n--- General Store ---\n");
    printf("Prices: Potion (20 gold, restores 50 HP), Elixir (50 gold, restores full HP)\n");
    printf("You can also sell: Potion (10 gold), Elixir (25 gold)\n");
    while (1) {
        printf("\n1. Buy Potion\n");
        printf("2. Buy Elixir\n");
        printf("3. Sell Potion\n");
        printf("4. Sell Elixir\n");
        printf("5. Back\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:  // Buy Potion
                printf("How many? ");
                scanf("%d", &quantity);
                if (quantity * 20 <= player->gold && quantity > 0) {
                    player->gold -= quantity * 20;
                    player->potions += quantity;
                    printf("Bought %d potions.\n", quantity);
                } else {
                    printf("Not enough gold or invalid quantity.\n");
                }
                break;
            case 2:  // Buy Elixir
                printf("How many? ");
                scanf("%d", &quantity);
                if (quantity * 50 <= player->gold && quantity > 0) {
                    player->gold -= quantity * 50;
                    player->elixirs += quantity;
                    printf("Bought %d elixirs.\n", quantity);
                } else {
                    printf("Not enough gold or invalid quantity.\n");
                }
                break;
            case 3:  // Sell Potion
                printf("How many? ");
                scanf("%d", &quantity);
                if (quantity <= player->potions && quantity > 0) {
                    player->potions -= quantity;
                    player->gold += quantity * 10;
                    printf("Sold %d potions.\n", quantity);
                } else {
                    printf("Not enough potions or invalid quantity.\n");
                }
                break;
            case 4:  // Sell Elixir
                printf("How many? ");
                scanf("%d", &quantity);
                if (quantity <= player->elixirs && quantity > 0) {
                    player->elixirs -= quantity;
                    player->gold += quantity * 25;
                    printf("Sold %d elixirs.\n", quantity);
                } else {
                    printf("Not enough elixirs or invalid quantity.\n");
                }
                break;
            case 5:
                return;
            default:
                printf("Invalid choice.\n");
        }
    }
}

// Inn: Restore HP for gold
void inn(Player *player) {
    int choice;
    printf("\n--- Inn ---\n");
    printf("Rest for 30 gold to restore full HP.\n");
    printf("1. Rest\n");
    printf("2. Back\n");
    printf("Choose: ");
    scanf("%d", &choice);
    if (choice == 1) {
        if (player->gold >= 30) {
            player->gold -= 30;
            player->hp = player->maxHp;
            printf("You rested and restored full HP.\n");
        } else {
            printf("Not enough gold.\n");
        }
    }
}

// Dungeon: 5 levels of puzzles
void dungeon(Player *player) {
    int level = 1;
    while (level <= 5) {
        printf("\n--- Dungeon Level %d ---\n", level);
        int success = 0;
        switch (level) {
            case 1:
                success = puzzleLevel1();
                break;
            case 2:
                success = puzzleLevel2();
                break;
            case 3:
                success = puzzleLevel3();
                break;
            case 4:
                success = puzzleLevel4();
                break;
            case 5:
                success = puzzleLevel5();
                break;
        }
        if (success) {
            player->gold += 10;
            player->exp += 20;
            printf("Correct! Gained 10 gold and 20 EXP.\n");
            levelUp(player);  // Check for level up
            level++;
        } else {
            player->hp -= 10;
            printf("Wrong! Lost 10 HP.\n");
            if (player->hp <= 0) {
                printf("You died! Returning to town.\n");
                player->hp = player->maxHp / 2;  // Revive with half HP
                return;
            }
        }
    }
    printf("Congratulations! You completed the dungeon.\n");
}

// Level up check
void levelUp(Player *player) {
    int threshold = player->level * 100;
    if (player->exp >= threshold) {
        player->level++;
        player->maxHp += 10;
        player->hp = player->maxHp;
        printf("Level up! Level %d. HP restored and max HP increased.\n", player->level);
    }
}

// Puzzle Level 1: Area and Perimeter of Rectangle
int puzzleLevel1() {
    int length = rand() % 10 + 1;
    int width = rand() % 10 + 1;
    int area, perimeter;
    printf("A rectangle has length %d and width %d.\n", length, width);
    printf("What is the area? ");
    scanf("%d", &area);
    printf("What is the perimeter? ");
    scanf("%d", &perimeter);
    return (area == length * width && perimeter == 2 * (length + width));
}

// Puzzle Level 2: Time = Distance / Velocity
int puzzleLevel2() {
    int distance = rand() % 100 + 10;
    int velocity = rand() % 10 + 1;
    float time;
    printf("Distance: %d units, Velocity: %d units/time.\n", distance, velocity);
    printf("What is the time? (float) ");
    scanf("%f", &time);
    return (fabs(time - (float)distance / velocity) < 0.01);
}

// Puzzle Level 3: Pythagoras
int puzzleLevel3() {
    int a = rand() % 10 + 1;
    int b = rand() % 10 + 1;
    float c;
    printf("Right triangle with legs a=%d, b=%d.\n", a, b);
    printf("What is the hypotenuse c? (float) ");
    scanf("%f", &c);
    return (fabs(c - sqrt(a*a + b*b)) < 0.01);
}

// Puzzle Level 4: Acceleration = Force / Mass
int puzzleLevel4() {
    int force = rand() % 100 + 10;
    int mass = rand() % 10 + 1;
    float accel;
    printf("Force: %d N, Mass: %d kg.\n", force, mass);
    printf("What is the acceleration? (float) ");
    scanf("%f", &accel);
    return (fabs(accel - (float)force / mass) < 0.01);
}

// Puzzle Level 5: Fibonacci next number
int puzzleLevel5() {
    int fib[5] = {1, 1, 2, 3, 5};
    int next;
    printf("Fibonacci sequence: 1, 1, 2, 3, 5\n");
    printf("What is the next number? ");
    scanf("%d", &next);
    return (next == 8);
}
