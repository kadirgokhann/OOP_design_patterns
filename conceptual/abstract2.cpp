
#include <iostream>
#include <memory>

// Step 1: Create interfaces for product families

// Abstract Button
class Button {
public:
    virtual void render() = 0;
    virtual ~Button() = default;
};

// Abstract Checkbox
class Checkbox {
public:
    virtual void toggle() = 0;
    virtual ~Checkbox() = default;
};

// Step 2: Create concrete products for Windows

class WindowsButton : public Button {
public:
    void render() override {
        std::cout << "Rendering a Windows button." << std::endl;
    }
};

class WindowsCheckbox : public Checkbox {
public:
    void toggle() override {
        std::cout << "Toggling a Windows checkbox." << std::endl;
    }
};

// Step 3: Create concrete products for Linux

class LinuxButton : public Button {
public:
    void render() override {
        std::cout << "Rendering a Linux button." << std::endl;
    }
};

class LinuxCheckbox : public Checkbox {
public:
    void toggle() override {
        std::cout << "Toggling a Linux checkbox." << std::endl;
    }
};

// Step 4: Define an abstract factory

class GUIFactory {
public:
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
    virtual ~GUIFactory() = default;
};

// Step 5: Implement concrete factories

class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<WindowsCheckbox>();
    }
};

class LinuxFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<LinuxButton>();
    }
    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<LinuxCheckbox>();
    }
};

// Step 6: Client code that works with abstract factories

void renderUI(std::unique_ptr<GUIFactory> factory) {
    auto button = factory->createButton();
    auto checkbox = factory->createCheckbox();

    button->render();
    checkbox->toggle();
}

int main() {
    std::unique_ptr<GUIFactory> factory;

    // Choose the factory based on platform
#if defined(_WIN32)
    factory = std::make_unique<WindowsFactory>();
#else
    factory = std::make_unique<LinuxFactory>();
#endif

    // Render the UI using the abstract factory
    renderUI(std::move(factory));

    return 0;
}
