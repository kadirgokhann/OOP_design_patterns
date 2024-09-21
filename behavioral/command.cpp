#include <iostream>
#include <stack>
#include <string>

// Step 1: Define the Command interface
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

// Step 2: Create the Receiver (Text Editor)
class TextEditor {
private:
    std::string text;

public:
    void type(const std::string& newText) {
        text += newText;
        std::cout << "Current text: " << text << std::endl;
    }

    void erase(size_t count) {
        if (count > text.size()) {
            count = text.size();
        }
        text.erase(text.size() - count, count);
        std::cout << "Current text: " << text << std::endl;
    }

    std::string getText() const {
        return text;
    }
};

// Step 3: Create concrete commands
class TypeCommand : public Command {
private:
    TextEditor& editor;
    std::string textToType;

public:
    TypeCommand(TextEditor& editor, const std::string& text)
        : editor(editor), textToType(text) {}

    void execute() override {
        editor.type(textToType);
    }

    void undo() override {
        editor.erase(textToType.size());
    }
};

class DeleteCommand : public Command {
private:
    TextEditor& editor;
    size_t count;

public:
    DeleteCommand(TextEditor& editor, size_t count)
        : editor(editor), count(count) {}

    void execute() override {
        editor.erase(count);
    }

    void undo() override {
        // Undoing delete is a bit tricky without storing state, 
        // so we assume we cannot undo deletes without additional logic.
        std::cout << "Cannot undo delete in this simple example." << std::endl;
    }
};

// Step 4: Create the Invoker to execute and store commands
class CommandInvoker {
private:
    std::stack<std::unique_ptr<Command>> commandHistory;

public:
    void executeCommand(std::unique_ptr<Command> command) {
        command->execute();
        commandHistory.push(std::move(command));
    }

    void undoLastCommand() {
        if (!commandHistory.empty()) {
            commandHistory.top()->undo();
            commandHistory.pop();
        } else {
            std::cout << "No commands to undo!" << std::endl;
        }
    }
};

// Step 5: Use the Command pattern in client code
int main() {
    TextEditor editor;
    CommandInvoker invoker;

    // User types some text
    invoker.executeCommand(std::make_unique<TypeCommand>(editor, "Hello, "));
    invoker.executeCommand(std::make_unique<TypeCommand>(editor, "World!"));

    // User decides to undo the last action (typing "World!")
    invoker.undoLastCommand(); // Output: Current text: Hello,

    // User types more text
    invoker.executeCommand(std::make_unique<TypeCommand>(editor, "there."));

    // User deletes the last 5 characters ("there")
    invoker.executeCommand(std::make_unique<DeleteCommand>(editor, 5));

    return 0;
}
