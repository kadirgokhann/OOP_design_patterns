#include <iostream>
#include <algorithm>
#include <string>

// Example Scenario: Legacy Printer and Modern Interface
// Let's say you have an old LegacyPrinter class that prints text in uppercase only.
// Now, you want to use it in a modern system that requires normal-case text.

class LegacyPrinter {
public:
    void printUppercase(const std::string& text) {
        std::string uppercased = text;
        std::transform(uppercased.begin(), uppercased.end(), uppercased.begin(), ::toupper);
        std::cout << "Legacy Printer: " << uppercased << std::endl;
    }
};

// New interface
class ModernPrinter {
public:
    virtual void print(const std::string& text) = 0;  // Expected interface
    virtual ~ModernPrinter() = default;
};


// Adaptor clas
class PrinterAdapter : public ModernPrinter {
private:
    LegacyPrinter* legacyPrinter;

public:
    PrinterAdapter(LegacyPrinter* printer) : legacyPrinter(printer) {}

    void print(const std::string& text) override {
        legacyPrinter->printUppercase(text);  // Adapt the text for the old system
    }
};


int main() {
    LegacyPrinter legacyPrinter;
    ModernPrinter* printer = new PrinterAdapter(&legacyPrinter);

    std::string text = "Hello, Adapter Pattern!";
    printer->print(text);  // The Adapter translates the request

    delete printer;
    return 0;
}

// Advantages of Adapter Pattern:
// Reusability: 					You can reuse existing incompatible classes without modifying them.
// Single Responsibility Principle: The Adapter class is responsible for translating between interfaces,
//                                  keeping each class focused on its own responsibility.
// Loose Coupling: 					The client code doesn’t depend on the legacy class directly. It uses the
//                                  adapter to communicate with the legacy system.
// When to Use the Adapter Pattern:
// When you want to use an existing class but its interface doesn’t match the one you need.
// When you need to create a reusable library that can work with different systems.
