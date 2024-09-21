#include <iostream>
#include <string>

// Subsystem 1: Audio system.
class AudioSystem {
public:
    void loadAudio(const std::string& fileName) const {
        std::cout << "Loading audio: " << fileName << std::endl;
    }

    void playAudio() const {
        std::cout << "Playing audio\n";
    }

    void stopAudio() const {
        std::cout << "Stopping audio\n";
    }
};

// Subsystem 2: Video system.
class VideoSystem {
public:
    void loadVideo(const std::string& fileName) const {
        std::cout << "Loading video: " << fileName << std::endl;
    }

    void playVideo() const {
        std::cout << "Playing video\n";
    }

    void stopVideo() const {
        std::cout << "Stopping video\n";
    }
};

// Subsystem 3: Storage system.
class StorageSystem {
public:
    void mountDrive(const std::string& driveName) const {
        std::cout << "Mounting drive: " << driveName << std::endl;
    }

    void loadMedia(const std::string& mediaFile) const {
        std::cout << "Loading media file: " << mediaFile << std::endl;
    }
};

// Facade: Simplifies interaction with subsystems.
class MediaFacade {
private:
    AudioSystem* audioSystem;
    VideoSystem* videoSystem;
    StorageSystem* storageSystem;
    
public:
    MediaFacade() {
        audioSystem = new AudioSystem();
        videoSystem = new VideoSystem();
        storageSystem = new StorageSystem();
    }

    void playMedia(const std::string& driveName, const std::string& mediaFile) {
        std::cout << "Facade: Simplifying media playback process\n";
        storageSystem->mountDrive(driveName);
        storageSystem->loadMedia(mediaFile);
        audioSystem->loadAudio(mediaFile);
        videoSystem->loadVideo(mediaFile);
        audioSystem->playAudio();
        videoSystem->playVideo();
    }

    void stopMedia() {
        std::cout << "Facade: Simplifying stopping process\n";
        audioSystem->stopAudio();
        videoSystem->stopVideo();
    }

    ~MediaFacade() {
        delete audioSystem;
        delete videoSystem;
        delete storageSystem;
    }
};

// Client code interacting with the Facade.
int main() {
    MediaFacade* mediaPlayer = new MediaFacade();

    mediaPlayer->playMedia("Drive1", "movie.mp4");
    std::cout << "...\n";
    mediaPlayer->stopMedia();

    delete mediaPlayer;

    return 0;
}

// Explanation:
// AudioSystem, VideoSystem, StorageSystem (Subsystems): These are the complex subsystems that handle different aspects of multimedia playback. They have their own specific interfaces that would normally require detailed knowledge to use.
// MediaFacade (Facade): The Facade class simplifies the interaction with the subsystems. It provides a single method to play media (playMedia) and stop it (stopMedia), hiding the complexity of mounting drives, loading files, and playing audio/video.
// Client: The client interacts only with the MediaFacade, without needing to know about the underlying systems.
// Use Case:
// You would use the Facade Pattern when:
// 
// You have a complex system with multiple subsystems that clients need to interact with.
// You want to provide a simpler, unified interface to reduce the complexity for clients.
// You want to decouple the client from the subsystems to allow future changes without affecting the client.
// Advantages:
// Simplifies Client Code: The client interacts with a simpler interface instead of dealing with multiple subsystems.
// Decouples Client from Subsystems: The client doesn't need to know how the subsystems work, making it easier to modify or replace them without impacting the client.
// Improves Code Readability: By hiding the complex interactions, it makes the code easier to read and maintain.
// Disadvantages:
// Limited Control: The facade may hide too much functionality, limiting the client’s control over the subsystems.
// Not for All Use Cases: If the client needs fine-grained control over the subsystems, the Facade Pattern might not be the best fit.
