#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include <list>
#include "Texture.h"
#include "ShaderProgram.h"
#include <map>


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

private:
	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	~TileMap();

	void render() const;
	void free();
	
	int getTileSize() const { return tileSize; }

	vector<pair<int,list<std::map<string, int>>>> getEnemies(int tileMapColumn);

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size) const;
	bool collision(const glm::ivec2& pos, const glm::ivec2& mov, const glm::ivec2& size) const;

	bool getShowCollisionBlock();
	void setShowCollisionBlock(bool newShowCollisionBlock);
	void resetSpawnedEnemies();

private:
	bool loadLevel(const string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);

private:
	GLuint vaoCollisionBlocks, vaoScenario;
	GLuint vboCollisionBlocks, vboScenario;
	GLint posLocationCollisionBlocks, texCoordLocationCollisionBlocks, posLocationScenario, texCoordLocationScenario;
	int nTiles;
	glm::ivec2 mapSize;
	int tileSize;
	Texture background, scenario, collisionBlock;
	int* map;
	// 2D Matrix. In each cell of it, it has a list of enemies.
	// Enemies are represented as maps with the following keys:
	//  * enemyType: number that represent each enemy type
	//  * extraInfo: optional parameter/offset for enemies
	//  * powerUp: whether drops or not a power up when dies
	vector<vector<list<std::map<string, int>>>> mapEnemies;
	vector<bool> spawnedColumns;
	bool showCollisionBlock;
};


#endif // _TILE_MAP_INCLUDE


