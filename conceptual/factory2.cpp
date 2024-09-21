
#include <iostream>
#include <memory>

// Step 1: Create an interface for the product
class Button {
public:
    virtual void render() = 0; // Pure virtual function
    virtual ~Button() = default;
};

// Step 2: Implement concrete products
class WindowsButton : public Button {
public:
    void render() override {
        std::cout << "Rendering a Windows button." << std::endl;
    }
};

class LinuxButton : public Button {
public:
    void render() override {
        std::cout << "Rendering a Linux button." << std::endl;
    }
};

// Step 3: Create a factory interface
class Dialog {
public:
    // Factory method to be overridden by subclasses
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual ~Dialog() = default;

    // Common functionality that uses the product
    void renderButton() {
        // Create a product and use it
        auto button = createButton();
        button->render();
    }
};

// Step 4: Implement concrete factories
class WindowsDialog : public Dialog {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }
};

class LinuxDialog : public Dialog {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<LinuxButton>();
    }
};

// Client code
int main() {
    // Dynamically select factory based on the platform
    std::unique_ptr<Dialog> dialog;

#if defined(_WIN32)
    dialog = std::make_unique<WindowsDialog>();
#else
    dialog = std::make_unique<LinuxDialog>();
#endif

    // Render the button created by the specific factory
    dialog->renderButton();

    return 0;
}
