#include <iostream>
#include <string>

namespace GameUnits {
    class Position {
    public:
        int x;
        int y;

        Position(int x = 0, int y = 0) : x(x), y(y) {}
    };

    class Weapon {
    private:
        std::string name;
        int damage;

    public:
        Weapon(std::string name = "Fist", int damage = 1) : name(name), damage(damage) {}

        int GetDamage() const { return damage; }

        void Print() const {
            std::cout << "Weapon: " << name << ", Damage: " << damage << std::endl;
        }
    };

    class Unit {
    private:
        std::string name;
        int health;
        Position position;
        Weapon weapon;

    public:
        Unit(std::string name, int health, const Position& pos, const Weapon& wp)
            : name(name), health(health), position(pos), weapon(wp) {}

        void Print() const {
            std::cout << "Unit: " << name << ", Health: " << health
                << ", Position: (" << position.x << ", " << position.y << ")" << std::endl;
            weapon.Print();
        }

        void TakeDamage(int damage) {
            health -= damage;
            if (health < 0) health = 0;
        }
    };
}

namespace GameBattle {
    using namespace GameUnits;

    class Team {
    private:
        Unit** members;
        size_t count;
        size_t capacity;

        void Resize() {
            size_t newCapacity = capacity * 2;
            Unit** newMembers = new Unit * [newCapacity];
            for (size_t i = 0; i < count; i++) {
                newMembers[i] = members[i];
            }
            delete[] members;
            members = newMembers;
            capacity = newCapacity;
        }

    public:
        Team(size_t initialCapacity = 2) : count(0), capacity(initialCapacity) {
            members = new Unit * [capacity];
        }

        ~Team() {
            for (size_t i = 0; i < count; i++) {
                delete members[i];
            }
            delete[] members;
        }

        void AddMember(const Unit& unit) {
            if (count == capacity) {
                Resize();
            }
            members[count++] = new Unit(unit);
        }

        void PrintTeam() const {
            std::cout << "Team members:" << std::endl;
            for (size_t i = 0; i < count; i++) {
                members[i]->Print();
                std::cout << "-------------------------------------------" << std::endl;
            }
        }
    };
}

namespace Utility {
    class IPrint {
    public:
        virtual void Print() const = 0;
    };

    template <typename T>
    class Array {
    private:
        T* data;
        size_t size;

    public:
        Array(size_t size) : size(size) {
            data = new T[size];
        }

        ~Array() {
            delete[] data;
        }

        T& operator[](size_t index) {
            return data[index];
        }

        const T& operator[](size_t index) const {
            return data[index];
        }

        size_t GetSize() const {
            return size;
        }

        void Print() const {
            for (size_t i = 0; i < size; i++) {
                std::cout << data[i] << " ";
            }
            std::cout << std::endl;
        }
    };
}

int main() {
    using namespace GameUnits;
    using namespace GameBattle;

    Weapon sword("Sword", 10);
    Unit knight("Knight", 100, Position(2, 3), sword);

    Weapon bow("Bow", 5);
    Unit archer("Archer", 80, Position(1, 1), bow);

    Team team;
    team.AddMember(knight);
    team.AddMember(archer);

    team.PrintTeam();

    Utility::Array<int> arr(5);
    for (size_t i = 0; i < arr.GetSize(); i++) {
        arr[i] = i * 10;
    }

    std::cout << "Array contents: ";
    arr.Print();
}
