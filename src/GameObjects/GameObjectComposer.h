#pragma once

#include <memory>
#pragma warning(push, 0)
#include <Box2d/Box2D.h>
#pragma warning(pop)
#include "IGameObject.h"

namespace cocos2d { class Node; }
class GameWorld;

class GameObjectComposer
{
public:
	struct LineDef
	{
		struct Block
		{
			Block(const std::string& texture, float width) : textureName(texture), width(width) {}
			std::string textureName;
			float width = 0;
		};

		std::vector<Block> blocks;
		b2Vec2 startPos;
		float length = 0;
		float maxOverlap = 0;
	};

	struct BridgeDef
	{
		b2Vec2 startPos;
		b2Vec2 direction;
		int linkCount = 0;
		b2Vec2 linkSize;
		float overlap = 0;
	};

	GameObjectComposer(GameWorld* world);

	void assembleLine(const LineDef& def);
	void assembleBridge(const BridgeDef& def);

private:
	GameWorld* _world = nullptr;
};

 