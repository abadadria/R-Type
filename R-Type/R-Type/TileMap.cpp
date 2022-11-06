#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "TileMap.h"


using namespace std;


TileMap *TileMap::createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	TileMap *map = new TileMap(levelFile, minCoords, program);
	
	return map;
}


TileMap::TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
	showCollisionBlock = false;
}

TileMap::~TileMap()
{
	if(map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);

	//Render scenario
	scenario.use();
	glBindVertexArray(vaoScenario);
	glEnableVertexAttribArray(posLocationScenario);
	glEnableVertexAttribArray(texCoordLocationScenario);
	glDrawArrays(GL_TRIANGLES, 0, 6);

	if (showCollisionBlock) {
		// Render collision blocks
		collisionBlock.use();
		glBindVertexArray(vaoCollisionBlocks);
		glEnableVertexAttribArray(posLocationCollisionBlocks);
		glEnableVertexAttribArray(texCoordLocationCollisionBlocks);
		glDrawArrays(GL_TRIANGLES, 0, 6 * nTiles);
	}
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vboCollisionBlocks);
}

bool TileMap::loadLevel(const string &levelFile)
{
	ifstream fin;
	string line, scenarioFile;
	stringstream sstream;
	char tile;
	
	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize;
	tileSize *= 2;
	getline(fin, line);
	sstream.str(line);
	sstream >> scenarioFile;

	// Load scenario texture
	scenario.loadFromFile(scenarioFile, TEXTURE_PIXEL_FORMAT_RGBA);
	scenario.setWrapS(GL_CLAMP_TO_EDGE);
	scenario.setWrapT(GL_CLAMP_TO_EDGE);
	scenario.setMinFilter(GL_NEAREST);
	scenario.setMagFilter(GL_NEAREST);

	// Load enemy definitions
	// char is ID, first int is enemyType, second int is extraInfo
	std::map<char, vector<pair<int, int>>> enemyDefs;
	int nDefs, nEnemies, enemyType, extraInfo;
	char letter;
	getline(fin, line);
	if (line.compare(0, 9, "ENEMY_DEF") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> nDefs;
	// Get all enemy definitions
	for (int i = 0; i < nDefs; ++i) {
		getline(fin, line);
		sstream.str(line);
		sstream >> letter;
		sstream >> nEnemies;
		for (int j = 0; j < nEnemies; ++j) {
			sstream >> enemyType >> extraInfo;
			enemyDefs[letter].push_back(make_pair(enemyType, extraInfo));
		}
	}

	// Load level map
	map = new int[mapSize.x * mapSize.y];
	spawnedColumns = vector<bool>(mapSize.x, false);
	mapEnemies = vector<vector<list<pair<int,int>>>>(mapSize.y, vector<list<pair<int,int>>>(mapSize.x));
	for (int j = 0; j < mapSize.y; j++) {
		for (int i = 0; i < mapSize.x; i++) {
			fin.get(tile);
			if (tile == ' ')
				map[j * mapSize.x + i] = 0;
			else if (tile == '1')
				map[j * mapSize.x + i] = 1;
			else if (tile >= '2' && tile <= '9') { // Single enemy
				mapEnemies[j][i].push_back(make_pair(tile - '0', 0));
			}
			else if (tile >= 'A' && tile <= 'Z') // Enemy definition
				if (enemyDefs.find(tile) == enemyDefs.end())
					return false;
				for (pair<int,int> p : enemyDefs[tile])
					mapEnemies[j][i].push_back(p);
		}
		fin.get(tile);
#ifndef _WIN32
		fin.get(tile);
#endif
	}

	fin.close();
	return true;
}

void TileMap::prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program)
{
	
	
	// Prepare scenario arrays
	glm::vec2 quadSize = mapSize * tileSize;
	//							   geomCoords				texCoords
	float verticesScenario[24] = { 0.f, 0.f,				0.f, 0.f,
								   quadSize.x, 0.f,			1.f, 0.f,
								   quadSize.x, quadSize.y,	1.f, 1.f,

								   0.f, 0.f,				0.f, 0.f,
								   quadSize.x, quadSize.y,	1.f, 1.f,
								   0.f, quadSize.y,			0.f, 1.f };

	glGenVertexArrays(1, &vaoScenario);
	glBindVertexArray(vaoScenario);
	glGenBuffers(1, &vboScenario);
	glBindBuffer(GL_ARRAY_BUFFER, vboScenario);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), verticesScenario, GL_STATIC_DRAW);
	posLocationScenario = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocationScenario = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));

	// Load collision block texture
	collisionBlock.loadFromFile("images/collision_block.png", TEXTURE_PIXEL_FORMAT_RGBA);
	collisionBlock.setWrapS(GL_CLAMP_TO_EDGE);
	collisionBlock.setWrapT(GL_CLAMP_TO_EDGE);
	collisionBlock.setMinFilter(GL_NEAREST);
	collisionBlock.setMagFilter(GL_NEAREST);

	int tile;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> verticesCollisionBlock;

	nTiles = 0;
	texCoordTile[0] = glm::vec2(0.0f, 0.0f);
	texCoordTile[1] = glm::vec2(1.0f, 1.0f);
	for (int j = 0; j < mapSize.y; j++) {
		for (int i = 0; i < mapSize.x; i++) {
			tile = map[j * mapSize.x + i];
			if (tile == 1) {
				// Collision tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				// First triangle
				verticesCollisionBlock.push_back(posTile.x); verticesCollisionBlock.push_back(posTile.y);
				verticesCollisionBlock.push_back(texCoordTile[0].x); verticesCollisionBlock.push_back(texCoordTile[0].y);
				verticesCollisionBlock.push_back(posTile.x + tileSize); verticesCollisionBlock.push_back(posTile.y);
				verticesCollisionBlock.push_back(texCoordTile[1].x); verticesCollisionBlock.push_back(texCoordTile[0].y);
				verticesCollisionBlock.push_back(posTile.x + tileSize); verticesCollisionBlock.push_back(posTile.y + tileSize);
				verticesCollisionBlock.push_back(texCoordTile[1].x); verticesCollisionBlock.push_back(texCoordTile[1].y);
				// Second triangle
				verticesCollisionBlock.push_back(posTile.x); verticesCollisionBlock.push_back(posTile.y);
				verticesCollisionBlock.push_back(texCoordTile[0].x); verticesCollisionBlock.push_back(texCoordTile[0].y);
				verticesCollisionBlock.push_back(posTile.x + tileSize); verticesCollisionBlock.push_back(posTile.y + tileSize);
				verticesCollisionBlock.push_back(texCoordTile[1].x); verticesCollisionBlock.push_back(texCoordTile[1].y);
				verticesCollisionBlock.push_back(posTile.x); verticesCollisionBlock.push_back(posTile.y + tileSize);
				verticesCollisionBlock.push_back(texCoordTile[0].x); verticesCollisionBlock.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vaoCollisionBlocks);
	glBindVertexArray(vaoCollisionBlocks);
	glGenBuffers(1, &vboCollisionBlocks);
	glBindBuffer(GL_ARRAY_BUFFER, vboCollisionBlocks);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &verticesCollisionBlock[0], GL_STATIC_DRAW);
	posLocationCollisionBlocks = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocationCollisionBlocks = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

vector<pair<int, list<pair<int,int>>>> TileMap::getEnemies(int tileMapColumn) { 
	if (spawnedColumns[tileMapColumn])
		return vector<pair<int, list<pair<int, int>>>>(0);
	vector<pair<int, list<pair<int, int>>>> enemies;
	for (int j = 0; j < mapSize.y; ++j) {
		list<pair<int, int>> aux = mapEnemies[j][tileMapColumn];
		enemies.push_back(make_pair(j, aux));
	}
	spawnedColumns[tileMapColumn] = true;
	return enemies;
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
		if(map[y*mapSize.x+x] == 1)
			return true;
	
	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x, y0, y1;
	
	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for(int y=y0; y<=y1; y++)
		if(map[y*mapSize.x+x] == 1)
			return true;
	
	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size) const
{
	int x0, x1, y;
	
	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for(int x=x0; x<=x1; x++)
		if(map[y*mapSize.x+x] == 1)
				return true;
	
	return false;
}

bool TileMap::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = pos.y / tileSize;
	for (int x = x0; x <= x1; x++)
		if (map[y * mapSize.x + x] == 1)
				return true;

	return false;
}

bool TileMap::collision(const glm::ivec2& pos, const glm::ivec2& mov, const glm::ivec2& size) const
{
	glm::ivec2 newpos = pos + mov;
	return mov.x > 0 && collisionMoveRight(newpos, size) || mov.x < 0 && collisionMoveLeft(newpos, size) ||
		   mov.y > 0 && collisionMoveDown(newpos, size)  || mov.y < 0 && collisionMoveUp(newpos, size);
}



bool TileMap::getShowCollisionBlock()
{
	return showCollisionBlock;
}

void TileMap::setShowCollisionBlock(bool newShowCollisionBlock)
{
	showCollisionBlock = newShowCollisionBlock;
}

void TileMap::resetSpawnedEnemies()
{
	spawnedColumns = vector<bool>(mapSize.x, false);
}
