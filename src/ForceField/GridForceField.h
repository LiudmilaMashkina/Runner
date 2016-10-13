#pragma once

#include<memory>
#include<vector>
#include "IForceField.h"

class GridForceField : public IForceField
{
public:
	struct WhirlDef
	{
		struct Edge
		{
			float radius;
			float radialForce;
			float tangentialForce;
		};

		b2Vec2 center;
		Edge inner;
		Edge outer;
	};

	~GridForceField() {};
	static std::shared_ptr<GridForceField> create(const b2Vec2 &gridSize, float gridStep);
	void setStatic(const b2Vec2 &force);
	void addWhirl(const WhirlDef &whirl );
	b2Vec2 getForce(const b2Vec2 &coordinates) override;

private:
	GridForceField(const b2Vec2 &gridSize, float gridStep);
	float getDist(const b2Vec2 &a, const b2Vec2 &b);

	std::vector<std::vector<b2Vec2>> _grid;
	float _gridStep;
};
