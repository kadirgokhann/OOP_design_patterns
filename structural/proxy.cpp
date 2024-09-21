#include <iostream>
#include <string>

// Subject: Defines the interface for real objects and proxy objects.
class Image {
public:
    virtual void display() const = 0;
    virtual ~Image() = default;
};

// Real Subject: The actual image that is expensive to load.
class RealImage : public Image {
private:
    std::string fileName;

    void loadFromDisk() const {
        std::cout << "Loading image from disk: " << fileName << std::endl;
    }

public:
    RealImage(const std::string& fileName) : fileName(fileName) {
        loadFromDisk();  // Simulate expensive loading operation.
    }

    void display() const override {
        std::cout << "Displaying image: " << fileName << std::endl;
    }
};

// Proxy: Controls access to the RealImage.
class ImageProxy : public Image {
private:
    std::string fileName;
    mutable RealImage* realImage;  // Lazy initialization.

public:
    ImageProxy(const std::string& fileName) : fileName(fileName), realImage(nullptr) {}

    void display() const override {
        if (!realImage) {
            std::cout << "ImageProxy: Loading the real image for the first time.\n";
            realImage = new RealImage(fileName);  // Load the image only when needed.
        }
        realImage->display();
    }

    ~ImageProxy() {
        delete realImage;
    }
};

int main() {
    // Client code uses the proxy instead of directly using RealImage.
    Image* image1 = new ImageProxy("high_resolution_image_1.jpg");
    Image* image2 = new ImageProxy("high_resolution_image_2.jpg");

    // Display the images (real images will be loaded only when needed).
    std::cout << "Displaying image1 for the first time:\n";
    image1->display();  // Image is loaded and displayed.

    std::cout << "\nDisplaying image1 again:\n";
    image1->display();  // Image is already loaded, no need to load again.

    std::cout << "\nDisplaying image2 for the first time:\n";
    image2->display();  // Image is loaded and displayed.

    // Cleanup.
    delete image1;
    delete image2;

    return 0;
}
