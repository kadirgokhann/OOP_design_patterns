
#include <iostream>
#include <memory>

// Prototype interface
class Shape {
public:
    virtual ~Shape() = default;
    
    // Method for cloning the object
    virtual std::unique_ptr<Shape> clone() const = 0;

    // Just a demo method to show the type of shape
    virtual void draw() const = 0;
};

// Concrete class for Circle
class Circle : public Shape {
private:
    int radius;

public:
    Circle(int r) : radius(r) {}

    // Clone method to return a copy of the Circle
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this); // Use copy constructor
    }

    void draw() const override {
        std::cout << "Drawing a Circle with radius " << radius << std::endl;
    }
};

// Concrete class for Rectangle
class Rectangle : public Shape {
private:
    int width, height;

public:
    Rectangle(int w, int h) : width(w), height(h) {}

    // Clone method to return a copy of the Rectangle
    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this); // Use copy constructor
    }

    void draw() const override {
        std::cout << "Drawing a Rectangle with width " << width 
                  << " and height " << height << std::endl;
    }
};

// Client code
int main() {
    // Create original shapes
    std::unique_ptr<Shape> originalCircle = std::make_unique<Circle>(10);
    std::unique_ptr<Shape> originalRectangle = std::make_unique<Rectangle>(5, 7);

    // Clone the shapes
    std::unique_ptr<Shape> clonedCircle = originalCircle->clone();
    std::unique_ptr<Shape> clonedRectangle = originalRectangle->clone();

    // Draw original and cloned shapes
    std::cout << "Original Shapes: " << std::endl;
    originalCircle->draw();
    originalRectangle->draw();

    std::cout << "\nCloned Shapes: " << std::endl;
    clonedCircle->draw();
    clonedRectangle->draw();

    return 0;
}
