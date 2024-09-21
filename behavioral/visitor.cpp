#include <iostream>
#include <memory>
#include <vector>

// Step 1: Create the Element interface (File interface)
class FileVisitor;  // Forward declaration

class File {
public:
    virtual ~File() = default;
    virtual void accept(FileVisitor& visitor) = 0;  // Accept visitor
};

// Step 2: Create concrete element classes (TextFile, ImageFile, AudioFile)
class TextFile : public File {
public:
    void accept(FileVisitor& visitor) override;
};

class ImageFile : public File {
public:
    void accept(FileVisitor& visitor) override;
};

class AudioFile : public File {
public:
    void accept(FileVisitor& visitor) override;
};

// Step 3: Create the Visitor interface
class FileVisitor {
public:
    virtual ~FileVisitor() = default;

    // Visit methods for each file type
    virtual void visit(TextFile& file) = 0;
    virtual void visit(ImageFile& file) = 0;
    virtual void visit(AudioFile& file) = 0;
};

// Step 4: Implement concrete visitors (e.g., Compression, VirusScan)
class CompressionVisitor : public FileVisitor {
public:
    void visit(TextFile& file) override {
        std::cout << "Compressing text file..." << std::endl;
    }

    void visit(ImageFile& file) override {
        std::cout << "Compressing image file..." << std::endl;
    }

    void visit(AudioFile& file) override {
        std::cout << "Compressing audio file..." << std::endl;
    }
};

class VirusScanVisitor : public FileVisitor {
public:
    void visit(TextFile& file) override {
        std::cout << "Scanning text file for viruses..." << std::endl;
    }

    void visit(ImageFile& file) override {
        std::cout << "Scanning image file for viruses..." << std::endl;
    }

    void visit(AudioFile& file) override {
        std::cout << "Scanning audio file for viruses..." << std::endl;
    }
};

// Step 5: Define the `accept` methods for each file type
void TextFile::accept(FileVisitor& visitor) {
    visitor.visit(*this);
}

void ImageFile::accept(FileVisitor& visitor) {
    visitor.visit(*this);
}

void AudioFile::accept(FileVisitor& visitor) {
    visitor.visit(*this);
}

// Step 6: Use the Visitor pattern in the client code
int main() {
    // Create a collection of files
    std::vector<std::unique_ptr<File>> files;
    files.push_back(std::make_unique<TextFile>());
    files.push_back(std::make_unique<ImageFile>());
    files.push_back(std::make_unique<AudioFile>());

    // Create visitors
    CompressionVisitor compression;
    VirusScanVisitor virusScan;

    // Apply compression to all files
    std::cout << "Applying CompressionVisitor:" << std::endl;
    for (auto& file : files) {
        file->accept(compression);
    }

    // Apply virus scanning to all files
    std::cout << "\nApplying VirusScanVisitor:" << std::endl;
    for (auto& file : files) {
        file->accept(virusScan);
    }

    return 0;
}
