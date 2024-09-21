#include <iostream>

// Implementation interface: Renderer defines how the drawing will be implemented.
class Renderer {
public:
    virtual void renderCircle(float radius) const = 0;
    virtual ~Renderer() = default;
};

// Concrete Implementations: Different rendering systems.
class OpenGLRenderer : public Renderer {
public:
    void renderCircle(float radius) const override {
        std::cout << "OpenGLRenderer: Rendering circle with radius " << radius << std::endl;
    }
};

class DirectXRenderer : public Renderer {
public:
    void renderCircle(float radius) const override {
        std::cout << "DirectXRenderer: Rendering circle with radius " << radius << std::endl;
    }
};

// Abstraction: Shape defines the high-level interface.
class Shape {
protected:
    Renderer* renderer;  // Bridge to the implementation.
    
public:
    Shape(Renderer* rendererObj) : renderer(rendererObj) {}
    virtual void draw() const = 0;  // High-level operation.
    virtual ~Shape() = default;
};

// Refined Abstraction: Circle is a concrete shape.
class Circle : public Shape {
private:
    float radius;
    
public:
    Circle(float r, Renderer* rendererObj) : Shape(rendererObj), radius(r) {}

    // Uses the renderer to perform the actual rendering.
    void draw() const override {
        renderer->renderCircle(radius);
    }
};

int main() {
    // Client uses the abstraction (Shape) and provides the implementation (Renderer).

    // Circle using OpenGL rendering.
    Renderer* openGLRenderer = new OpenGLRenderer();
    Shape* circle1 = new Circle(5.0f, openGLRenderer);
    circle1->draw();

    // Circle using DirectX rendering.
    Renderer* directXRenderer = new DirectXRenderer();
    Shape* circle2 = new Circle(10.0f, directXRenderer);
    circle2->draw();

    // Cleanup.
    delete circle1;
    delete openGLRenderer;
    delete circle2;
    delete directXRenderer;

    return 0;
}

//  Explanation:
//  Renderer Interface (Implementation): Defines how the drawing is performed. In this case, we have two implementations: OpenGLRenderer and DirectXRenderer.
//  Shape (Abstraction): Represents the abstraction for different shapes. The abstraction uses composition to store a reference to the Renderer implementation.
//  Circle (Refined Abstraction): A concrete shape class that uses the Renderer to draw itself.
//  Use Case:
//  You would use the Bridge Pattern when:
//  
//  You have multiple dimensions of variability that could lead to a large number of subclasses (e.g., different shapes and rendering systems).
//  You want to vary these dimensions independently (e.g., adding new shapes without modifying the renderer or adding new renderers without changing the shape classes).
//  Advantages:
//  Reduced Class Explosion: By decoupling abstraction from implementation, you avoid a combinatorial explosion of classes.
//  Increased Flexibility: Both the abstraction and implementation can be extended independently.
//  Improved Maintainability: Changes in one dimension of variability (e.g., adding a new renderer) don't affect other dimensions (e.g., shapes).
