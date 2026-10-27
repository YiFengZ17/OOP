
#ifndef ADVENTURE_H
#define ADVENTURE_H

#include <string>
#include <unordered_map>
#include <vector>

//Different Room types
enum class RoomType {
    Lobby,
    Corridor,
    Library,
    DiningHall,
    Armory,
    Dungeon,
    Tower,
    SecretChamber
};
// Random assign the occupant
enum class Occupant {
    None,
    Princess,
    Monster
};

class Room {
private:
    //Informations about a room,including id, type(name),floor,Occupant,exits
    int id;
    RoomType type;
    int floor;
    Occupant occupant = Occupant::None;
    std::unordered_map<std::string, int> exits;

public:
    // constructor function
    Room(int id, RoomType type, int floor);
    // get the information about the room,only read
    int getId() const;
    RoomType getType() const;
    int getFloor() const;
    Occupant getOccupant() const;
    const std::unordered_map<std::string, int>& getExits() const;
    
    // change the information of room
    void setOccupant(Occupant occupant);
    void addExit(const std::string& direction, int roomId);

};
    

class Knight {
private:
    // Information about Knight
    int currentRoom;
    bool princessFollowing = false;
    std::vector<int> path;
public:
    Knight(int currentRoom = 0);

    // get information about the Knight,only read
    int getCurrentRoom() const;
    bool hasPrincess() const;
    const std::vector<int>& getPath() const;

    // Record successful moves only. The path also includes the start room.
    void moveTo(int roomId);
    void rescuePrincess();

};

class Castle {
public:
    Castle();
    int getRoomCount() const;
    const Room& getRoom(int roomId) const;// help outside get one room
private:
    // Room IDs match their indices in this vector: 0 through size() - 1
    std::vector<Room> rooms;
    // Build a connected map with room 0 as the lobby
    void buildMap();

    // Add a bidirectional edge.
    void connectRooms(int from, const std::string& direction, int to);

    // Assign the princess and monster's position
    void placeOccupantsRandomly();
};
#endif
