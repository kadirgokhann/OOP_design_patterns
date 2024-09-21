
#include <iostream>

class Singleton {
private:
    // Private constructor to prevent instantiation
    Singleton() {
        std::cout << "Singleton created!" << std::endl;
    }

    // Static instance of the Singleton
    static Singleton* instance;

public:
    // Delete the copy constructor and assignment operator to prevent copies
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // Static method to provide access to the instance
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }

    void showMessage() {
        std::cout << "Hello from Singleton!" << std::endl;
    }
};

// Initialize the static member
Singleton* Singleton::instance = nullptr;

int main() {
    // Get the single instance and call a method
    Singleton* singleton = Singleton::getInstance();
    singleton->showMessage();

    // If we try to get another instance, it will return the same one
    Singleton* anotherSingleton = Singleton::getInstance();
    anotherSingleton->showMessage();

    return 0;
}
