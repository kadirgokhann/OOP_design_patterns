// Let’s create a system that displays characters in a text editor, where characters can share formatting data (intrinsic state), and their positions in the text (extrinsic state) are passed when needed.

// Flyweight (Character): The shared, reusable object.
// Flyweight Factory: Manages the pool of flyweights to ensure reuse.
// Client: Uses the flyweights but passes the extrinsic state (e.g., position) when needed.
#include <iostream>
#include <unordered_map>
#include <string>

// Flyweight: Stores the intrinsic state (shared state).
class Character {
private:
    char symbol;         // Intrinsic state (shared)
    std::string font;    // Intrinsic state (shared)
    int size;            // Intrinsic state (shared)

public:
    Character(char symbol, const std::string& font, int size) 
        : symbol(symbol), font(font), size(size) {}

    void display(int x, int y) const {  // x and y are extrinsic (context-specific) state
        std::cout << "Displaying '" << symbol << "' at (" << x << ", " << y
                  << ") with font: " << font << " and size: " << size << std::endl;
    }
};

// Flyweight Factory: Manages the flyweight pool.
class CharacterFactory {
private:
    std::unordered_map<char, Character*> flyweights;

public:
    Character* getCharacter(char symbol, const std::string& font, int size) {
        if (flyweights.find(symbol) == flyweights.end()) {
            // Create a new flyweight if it doesn't exist.
            flyweights[symbol] = new Character(symbol, font, size);
            std::cout << "Creating new flyweight for character: '" << symbol << "'\n";
        }
        return flyweights[symbol];
    }

    ~CharacterFactory() {
        // Cleanup flyweights.
        for (auto& pair : flyweights) {
            delete pair.second;
        }
    }
};

// Client code that uses the Flyweight.
int main() {
    CharacterFactory* factory = new CharacterFactory();

    // Use the flyweight factory to get characters.
    Character* charA = factory->getCharacter('A', "Arial", 12);
    Character* charB = factory->getCharacter('B', "Arial", 12);
    Character* charA2 = factory->getCharacter('A', "Arial", 12);  // Reuses 'A'

    // Display characters with different extrinsic states (position).
    charA->display(10, 20);
    charB->display(30, 40);
    charA2->display(50, 60);  // Reuses the same 'A' object.

    // Cleanup.
    delete factory;

    return 0;
}


// Explanation:
// Character (Flyweight): This class stores intrinsic state (the character's symbol, font, and size) that is shared across multiple instances. The extrinsic state (the position where the character is displayed) is passed when needed.
// CharacterFactory (Flyweight Factory): Manages a pool of Character flyweights. It ensures that if a character with the same intrinsic state (e.g., same symbol, font, and size) is requested, an existing flyweight is reused instead of creating a new one.
// Client: The client requests flyweights from the factory and supplies extrinsic state (position) when displaying characters.
// Use Case:
// You would use the Flyweight Pattern when:
// 
// You need to create a large number of similar objects (e.g., characters in a document, graphical objects in a game).
// You want to reduce memory usage by sharing common data between objects.
// You can separate the object's intrinsic state (shared data) from its extrinsic state (context-specific data).
// Advantages:
// Memory Efficiency: The flyweight pattern reduces memory usage by sharing objects that have common intrinsic state.
// Performance: It can improve performance in systems that would otherwise create a large number of similar objects.
// Extensibility: You can easily add new flyweights or change their extrinsic state without modifying the shared objects.
// Disadvantages:
// Complexity: Introducing shared objects and separating intrinsic/extrinsic state can make the code more complicated.
// Synchronization Issues: In multithreaded environments, managing shared flyweights might require synchronization to ensure thread safety.
