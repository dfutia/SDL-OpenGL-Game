#ifndef WORLD_H
#define WORLD_H

#include <unordered_map>

class WorldObject
{
};

class World
{
public:
	World() = default;
	~World() = default;
private:
	std::unordered_map<unsigned int, WorldObject> mObjects;
};

#endif // WORLD_H