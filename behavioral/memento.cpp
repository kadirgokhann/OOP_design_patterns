
#include <iostream>
#include <string>
#include <stack>

// Step 1: Create the Memento class to store the state
class EditorMemento {
private:
    std::string state;

public:
    explicit EditorMemento(const std::string& state) : state(state) {}

    std::string getState() const {
        return state;
    }
};

// Step 2: Create the Originator class (the text editor)
class TextEditor {
private:
    std::string content;

public:
    void type(const std::string& words) {
        content += words;
    }

    std::string getContent() const {
        return content;
    }

    // Save the current state to a memento
    std::unique_ptr<EditorMemento> save() const {
        return std::make_unique<EditorMemento>(content);
    }

    // Restore the state from a memento
    void restore(const EditorMemento& memento) {
        content = memento.getState();
    }
};

// Step 3: Create the Caretaker class to manage mementos (undo/redo functionality)
class EditorHistory {
private:
    std::stack<std::unique_ptr<EditorMemento>> history;

public:
    void save(std::unique_ptr<EditorMemento> memento) {
        history.push(std::move(memento));
    }

    std::unique_ptr<EditorMemento> undo() {
        if (history.empty()) {
            std::cout << "No states to undo!" << std::endl;
            return nullptr;
        }

        auto lastState = std::move(history.top());
        history.pop();
        return lastState;
    }
};

// Step 4: Use the Memento pattern in client code
int main() {
    TextEditor editor;
    EditorHistory history;

    // Type some content and save states
    editor.type("Hello, ");
    history.save(editor.save());

    editor.type("World!");
    history.save(editor.save());

    std::cout << "Current content: " << editor.getContent() << std::endl;  // Output: Hello, World!

    // Undo the last typing
    if (auto memento = history.undo()) {
        editor.restore(*memento);
    }
    std::cout << "After undo: " << editor.getContent() << std::endl;  // Output: Hello,

    // Undo another step
    if (auto memento = history.undo()) {
        editor.restore(*memento);
    }
    std::cout << "After second undo: " << editor.getContent() << std::endl;  // Output: (empty)

    return 0;
}
