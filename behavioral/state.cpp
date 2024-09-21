#include <iostream>
#include <memory>
#include <string>

// Step 1: Define the State interface
class MediaPlayerState {
public:
    virtual ~MediaPlayerState() = default;
    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
};

// Step 2: Create concrete states
class PlayingState : public MediaPlayerState {
public:
    void play() override {
        std::cout << "Already playing!" << std::endl;
    }

    void pause() override {
        std::cout << "Pausing the player." << std::endl;
    }

    void stop() override {
        std::cout << "Stopping the player." << std::endl;
    }
};

class PausedState : public MediaPlayerState {
public:
    void play() override {
        std::cout << "Resuming the player." << std::endl;
    }

    void pause() override {
        std::cout << "Already paused!" << std::endl;
    }

    void stop() override {
        std::cout << "Stopping the player from paused state." << std::endl;
    }
};

class StoppedState : public MediaPlayerState {
public:
    void play() override {
        std::cout << "Starting the player." << std::endl;
    }

    void pause() override {
        std::cout << "Cannot pause. The player is stopped." << std::endl;
    }

    void stop() override {
        std::cout << "Already stopped!" << std::endl;
    }
};

// Step 3: Create the MediaPlayer context class
class MediaPlayer {
private:
    std::shared_ptr<MediaPlayerState> currentState;

public:
    MediaPlayer() : currentState(std::make_shared<StoppedState>()) {}

    void setState(std::shared_ptr<MediaPlayerState> newState) {
        currentState = newState;
    }

    void play() {
        currentState->play();
        setState(std::make_shared<PlayingState>());
    }

    void pause() {
        currentState->pause();
        setState(std::make_shared<PausedState>());
    }

    void stop() {
        currentState->stop();
        setState(std::make_shared<StoppedState>());
    }
};

// Step 4: Use the State pattern in the client code
int main() {
    MediaPlayer player;

    std::cout << "Initial State: Stopped" << std::endl;

    // Start playing
    player.play();  // Output: Starting the player.

    // Pause the player
    player.pause();  // Output: Pausing the player.

    // Try to play again
    player.play();   // Output: Resuming the player.

    // Stop the player
    player.stop();   // Output: Stopping the player.

    // Try to pause while stopped
    player.pause();  // Output: Cannot pause. The player is stopped.

    return 0;
}

// How it works:
// The MediaPlayerState interface defines methods (play, pause, stop) that all states must implement.
// PlayingState, PausedState, and StoppedState are concrete implementations of these methods. Each state class defines how the media player should behave when it's in that state.
// The MediaPlayer class acts as the context. It holds a reference to the current state and delegates actions to the state. It can switch between states dynamically based on the user’s commands.
// Advantages:
// Cleaner code: Instead of one large class handling all the logic for every state, the logic is distributed across multiple state classes, each focusing on its own state.
// Open-Closed Principle: You can add new states without modifying existing code.
// Behavior change: The behavior of the object (media player) changes dynamically as its state changes.
