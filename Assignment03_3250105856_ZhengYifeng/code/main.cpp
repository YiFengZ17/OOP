#include "Adventure.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// change the room's type into string
const char* roomName(RoomType type) {  
    switch (type) {
        case RoomType::Lobby:         return "lobby";
        case RoomType::Corridor:      return "corridor";
        case RoomType::Library:       return "library";
        case RoomType::DiningHall:    return "dining hall";
        case RoomType::Armory:        return "armory";
        case RoomType::Dungeon:       return "dungeon";
        case RoomType::Tower:         return "tower";
        case RoomType::SecretChamber: return "secret chamber";
    }
    return "No such room";
}

void describeRoom(const Room& room) {
    const auto& exits = room.getExits();
    std::cout << "\nWelcome to the " << roomName(room.getType())
              << ". There are " << exits.size() << " exits: ";
    const std::string directions[] = {
        "east", "west", "north", "south", "up", "down"
    };
    size_t printed = 0;// counter to control the output
    for (const std::string& direction : directions) {
        if (exits.find(direction) == exits.end()) { // unable to find this direction
            continue;
        }
        if (printed > 0) { // find this direction and not the first direction
            std::cout << (printed + 1 == exits.size() ? " and " : ", ");
        }
        std::cout << direction; // find this direction and is the first direction
        ++printed;
    }
    std::cout << ".\n";
}


int main() {
    Castle castle;
    Knight knight;

    std::cout << "Find the princess and bring her back to the lobby.\n"
              << "Avoid the monster! Use 'go <direction>' to move.\n ";
              

    while (true) {
        const Room& room = castle.getRoom(knight.getCurrentRoom());
        describeRoom(room);
        //Meet the monster, game over
        if (room.getOccupant() == Occupant::Monster) {
            std::cout << "A monster attacks you! Game over.\n";
            break;
        }

        // Meet the princess for the first time, bring her
        if (room.getOccupant() == Occupant::Princess && !knight.hasPrincess()) {
            std::cout << "Princess: My Knight! Help me!\n"
                      << "Knight: My Princess, please follow me. I will take you out of here.\n"
                      << "The princess is now following you.\n";
            knight.rescuePrincess();
        }
        // bring princess and get to the lobby, win the game
        if (room.getType() == RoomType::Lobby && knight.hasPrincess()) {
            std::cout << "You and the princess leave the castle. Win!\n";
            break;
        }

        // Stay in this room until a valid move is entered.
        while (true) {
            std::cout << "Enter your command:\n";
            std::string line;
            if (!std::getline(std::cin, line)) {
                std::cout << "Input ended. Goodbye!\n";
                return 0;
            }

            std::istringstream input(line);
            std::string command, direction, extra; // split the input into 3 parts
            input >> command;

            // check if the command format is valid
            // we want 'go' and a direction without extra words
            if (command != "go" || !(input >> direction) || (input >> extra)) {
                std::cout << "Invalid command. Use 'go <direction>'\n";
                continue;
            }

            // check if the direction is valid 
            const auto& exits = room.getExits();
            if (exits.find(direction) == exits.end()) {
                std::cout << "There is no exit in that direction.\n";
                continue;
            }

            //If the direction is valid, go to the next room using HashMap
            knight.moveTo(exits.find(direction)->second);
            break;
        }
    }
    return 0;
}