#include <iostream>
#include <string>
#include <map>

class Animal {
public:
    static int totalCount;// Статичне поле для підрахунку загальної кількості об'єктів класу.
    Animal() {
        totalCount++;
    }
    virtual ~Animal() {
        totalCount--;
    }
    virtual void makeSound() = 0;// Чистий віртуальний метод, який вимагає визначення у похідних класах.

    //typedef void (*PrintCountFunc)();
    using PrintCountFunc = void (*)();
    static std::map<std::string, PrintCountFunc> printCountFuncs;
    // Статичне поле "map" для зберігання вказівників на функції.

    static void registerPrintCountFunc(const std::string& className, PrintCountFunc func) {
        printCountFuncs[className] = func;
    }
    // Статичний метод для реєстрації функцій друку кількості.
    static void printTotalCount() {
        std::cout << "Total Animals: " << totalCount << std::endl;
        for (const auto& it : printCountFuncs) {
            it.second();
        }
    }
    // Статичний метод для виведення загальної кількості об'єктів і здійснення друку кількості об’єктів окремих.
};
// Ініціалізація статичного поля "totalCount" для класу "Тварина".
int Animal::totalCount = 0;
std::map<std::string, Animal::PrintCountFunc> Animal::printCountFuncs;
// Ініціалізація статичного поля "printCountFuncs" для класу "Тварина".
class Dog : public Animal {
public:
    static int dogCount;
    Dog() {
        dogCount++;
    }
    ~Dog() {
        dogCount--;
    }
    void makeSound() override {
        std::cout << "Woof!" << std::endl;
    }
    static void printDogCount() {
        std::cout << "Total Dogs: " << dogCount << std::endl;
    }
    static void registerPrintDogCountFunc() {
        Animal::registerPrintCountFunc("Dog", printDogCount);
    }
};

class Cat : public Animal {
public:
    static int catCount;
    Cat() {
        catCount++;
    }
    ~Cat() {
        catCount--;
    }
    void makeSound() override {
        std::cout << "Meow!" << std::endl;
    }
    static void printCatCount() {
        std::cout << "Total Cats: " << catCount << std::endl;
    }
    static void registerPrintCatCountFunc() {
        Animal::registerPrintCountFunc("Cat", printCatCount);
    }
};
int Dog::dogCount = 0;
int Cat::catCount = 0;

int main() {
    Dog::registerPrintDogCountFunc();
    Cat::registerPrintCatCountFunc();
    Animal::printTotalCount();
    Animal* dog  = new Dog();
    Animal* cat1 = new Cat();
    Animal* cat2 = new Cat();

    Animal::printTotalCount();

    delete dog;
    delete cat1;
    delete cat2;
    Animal::printTotalCount();
    return 0;
}
