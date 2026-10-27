#include "Adventure.h"

#include <algorithm>
#include <queue>
#include <random>

// Implement Room class function
Room::Room(int id, RoomType type, int floor)
    : id(id), type(type), floor(floor) {}
// Room's only-read function
int Room::getId() const {
    return id;
}
RoomType Room::getType() const {
    return type;
}
int Room::getFloor() const {
    return floor;
}
Occupant Room::getOccupant() const {
    return occupant;
}
const std::unordered_map<std::string, int>& Room::getExits() const {
    return exits;
}
// Room's edit function
void Room::setOccupant(Occupant occupant) {
    this->occupant = occupant;
}

void Room::addExit(const std::string& direction, int roomId) {
    exits[direction] = roomId;
}


// Implement Knight class function
Knight::Knight(int currentRoom)
    : currentRoom(currentRoom), path{currentRoom} {}
// Only-read function
int Knight::getCurrentRoom() const {
    return currentRoom;
}

bool Knight::hasPrincess() const {
    return princessFollowing;
}

const std::vector<int>& Knight::getPath() const {
    return path;
}
// Edit function
void Knight::moveTo(int roomId) {
    currentRoom = roomId;//Move to another room
    path.push_back(roomId);
}

void Knight::rescuePrincess() {
    princessFollowing = true;// Meet the princess
}

//Implement Castle class function
Castle::Castle() {
    buildMap();
    placeOccupantsRandomly();
}

int Castle::getRoomCount() const {
    return rooms.size();
}
//const Room& is only-read referrence,can't change the Room
const Room& Castle::getRoom(int roomId) const{
    return rooms[roomId];
}

void Castle::buildMap() {
    rooms.clear();
    rooms.emplace_back(0, RoomType::Lobby, 1);
    rooms.emplace_back(1, RoomType::Corridor, 1);
    rooms.emplace_back(2, RoomType::Library, 1);
    rooms.emplace_back(3, RoomType::DiningHall, 1);
    rooms.emplace_back(4, RoomType::Tower, 2);
    rooms.emplace_back(5, RoomType::Armory, 1);
    rooms.emplace_back(6, RoomType::Dungeon, -1);
    rooms.emplace_back(7, RoomType::SecretChamber, -1);
    rooms.emplace_back(8, RoomType::Corridor,-1);


    connectRooms(0, "east", 1);
    connectRooms(0, "north", 2);
    connectRooms(0, "west", 3);
    connectRooms(1, "north", 5);

    connectRooms(5, "up", 4);
    connectRooms(5, "down", 6);
    connectRooms(6, "east", 8);
    connectRooms(6, "west", 7);
    connectRooms(2, "down", 7);
}

void Castle::connectRooms(int from, const std::string& direction, int to) {
    /* Store opposite directions in a hash table
       to build a bidirectional edge. */
    std::unordered_map<std::string, std::string> opposite{
        {"east", "west"}, {"west", "east"},
        {"north", "south"}, {"south", "north"},
        {"up", "down"}, {"down", "up"}
    };
    // Build a bidirectional edge.
    Room& source = rooms[from];
    Room& destination = rooms[to];
    source.addExit(direction, to);
    destination.addExit(opposite[direction], from);
}

void Castle::placeOccupantsRandomly() {
    int n = getRoomCount();

    for (Room& room : rooms) {
        room.setOccupant(Occupant::None);
    }
    // use random number generator
    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> randomRoom(1, n - 1);

    // Room 0 is the lobby; keep it empty.Assign room for princess and monster
    int princess;
    princess = randomRoom(generator);
    int monster;
    while (true) {
        monster = randomRoom(generator);
        if (monster == princess) {
            continue;
        }

        // Search from the lobby without entering the monster's room.
        std::vector<bool> visited(n, false);
        std::queue<int> pending;
        visited[0] = true;
        pending.push(0);
        while (!pending.empty()) {
            int current = pending.front();
            pending.pop();
            for (const auto& exit : rooms[current].getExits()) {
                int next = exit.second;
                if (next != monster && !visited[next]) {
                    visited[next] = true;
                    pending.push(next);
                }
            }
        }

        // Bidirectional edges also guarantee a safe return along this route.
        if (visited[princess]) {
            break;
        }
    }

    rooms[princess].setOccupant(Occupant::Princess);
    rooms[monster].setOccupant(Occupant::Monster);
}
