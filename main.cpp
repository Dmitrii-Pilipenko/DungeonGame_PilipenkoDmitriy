#include <iostream>

class Fighter {
    private:
        const char* name;
        int health;
        int maxHealth;
        int damage;

    public:
        Fighter(const char* name, int health, int damage) : name(name), health(health), maxHealth(health), damage(damage) {}
        void TakeDamage(int amount) {
            health -= amount;

            if (health < 0) {
                health = 0;
            }
        }
        void Attack(Fighter& target) const {
            target.TakeDamage(damage);
        }
        bool IsAlive() const {
            return health > 0;
        }
        void PrintStatus() const {
            std::cout << name << ": " << health << " хп" << std::endl;
        }
        int GetDamage() const {
            return damage;
        }
};

void PrintFighter(const Fighter& fighter) {
    fighter.PrintStatus();
}

class Game {
    private:
        Fighter player;
        Fighter enemies[3];
        Fighter* currentTarget = nullptr;

    public:
    Game() : player("Hero", 30, 8), enemies{{"Enemy 1", 12, 3}, {"Enemy 2", 18, 4}, {"Enemy 3", 24, 5}} {}

        bool TrySelectTarget(int number, Fighter*& target) {
        target = nullptr;

        if (number < 1 || number > 3) {
            return false;
        }

        if (!enemies[number - 1].IsAlive()) {
            return false;
        }

        target = &enemies[number - 1];
        return true;
    }

    bool AllEnemiesDefeated() const {
        for (int i = 0; i < 3; i++) {
            if (enemies[i].IsAlive()) {
                return false;
            }
        }
        return true;
    }
        void Run() {
            int command;
            int number;

            while (player.IsAlive() && !AllEnemiesDefeated()) {
                PrintFighter(player);
                for (int i = 0; i < 3; i++) {
                    PrintFighter(enemies[i]);
                }
                if (currentTarget != nullptr) {
                    std::cout << "Текущая цель: ";
                    currentTarget->PrintStatus();
                }
                else {
                    std::cout << "Цель не выбрана" << std::endl;
                }
                std::cout << "1 - выбрать цель, 2 - сразиться, 0 - выход: ";
                std::cin >> command;

                if (command == 0) {
                    return;
                }

                if (command == 1) {
                    std::cout << "Выбери врага: ";
                    std::cin >> number;

                    if (TrySelectTarget(number, currentTarget)) {
                        std::cout << "Вы выбрали цель" << std::endl;
                    }
                    else {
                        std::cout << "Нельзя выбрать этого врага" << std::endl;
                    }
                }

                else if (command == 2) {
                    if (currentTarget == nullptr) {
                        std::cout << "Сперва выбери цель" << std::endl;
                    }
                    else {
                        player.Attack(*currentTarget);
                        std::cout << "Ты нанес: " << player.GetDamage() << std::endl;

                        if (AllEnemiesDefeated()) {
                            std::cout << "Ты всех победил" << std::endl;
                            return;
                        }

                       if (currentTarget->IsAlive()) {
                            currentTarget->Attack(player);

                            std::cout << "Тебе нанесли: " << currentTarget->GetDamage() << std::endl;
                           if (!player.IsAlive()) {
                               std::cout << "Ты умер" << std::endl;
                               return;
                           }
                        }
                       else {
                           std::cout << "Враг побежден!" << std::endl;
                           currentTarget = nullptr;
                       }

                    }

                }
                else {
                    std::cout << "Неверная команда" << std::endl;
                }
            }
        }
};

int main() {
    Game game;
    game.Run();

    return 0;
}