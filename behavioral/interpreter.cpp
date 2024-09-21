
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// Step 1: Define the Abstract Expression class
class Expression {
public:
    virtual ~Expression() = default;
    virtual int interpret() const = 0;
};

// Step 2: Create concrete classes for Number and Operations
class Number : public Expression {
private:
    int value;

public:
    explicit Number(int value) : value(value) {}

    int interpret() const override {
        return value;
    }
};

class Add : public Expression {
private:
    std::shared_ptr<Expression> left, right;

public:
    Add(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left(left), right(right) {}

    int interpret() const override {
        return left->interpret() + right->interpret();
    }
};

class Subtract : public Expression {
private:
    std::shared_ptr<Expression> left, right;

public:
    Subtract(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left(left), right(right) {}

    int interpret() const override {
        return left->interpret() - right->interpret();
    }
};

// Step 3: Extend with more operations (e.g., Multiplication)
class Multiply : public Expression {
private:
    std::shared_ptr<Expression> left, right;

public:
    Multiply(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left(left), right(right) {}

    int interpret() const override {
        return left->interpret() * right->interpret();
    }
};

// Step 4: Client code to interpret expressions
int main() {
    // Example: (5 + 3) - 2
    std::shared_ptr<Expression> expression = std::make_shared<Subtract>(
        std::make_shared<Add>(
            std::make_shared<Number>(5),
            std::make_shared<Number>(3)),
        std::make_shared<Number>(2));

    std::cout << "Result of (5 + 3) - 2: " << expression->interpret() << std::endl;  // Output: 6

    // Example: 2 * (3 + 4)
    std::shared_ptr<Expression> expression2 = std::make_shared<Multiply>(
        std::make_shared<Number>(2),
        std::make_shared<Add>(
            std::make_shared<Number>(3),
            std::make_shared<Number>(4)));

    std::cout << "Result of 2 * (3 + 4): " << expression2->interpret() << std::endl;  // Output: 14

    return 0;
}
