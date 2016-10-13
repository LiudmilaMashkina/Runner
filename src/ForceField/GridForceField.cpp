
#include "GridForceField.h"
#include "Utils/b2Vec2Operators.h"


GridForceField::GridForceField(const b2Vec2 &gridSize, float gridStep) :
_gridStep(gridStep)
{
	// ._._._.+_.
	int arraySizeX = gridSize.x / _gridStep + 2;
	int arraySizeY = gridSize.y / _gridStep + 2;

	_grid.resize(arraySizeX);
	for (int i = 0; i < arraySizeX; ++i)
	{
		_grid[i].resize(arraySizeY);
		for (int j = 0; j < arraySizeY; ++j)
		{
			_grid[i][j] = b2Vec2(0, 0);
 		}
	}
}

std::shared_ptr<GridForceField> GridForceField::create(const b2Vec2 &gridSize, float gridStep)
{
	std::shared_ptr<GridForceField> gridField(new GridForceField(gridSize, gridStep));
	return gridField;
}

void GridForceField::setStatic(const b2Vec2 &force)
{
	for (int i = 0; i < _grid.size(); ++i)
	{
		for (int j = 0; j < _grid[i].size(); ++j)
		{
			_grid[i][j].x = force.x;
			_grid[i][j].y = force.y;
		}
	}
}

void GridForceField::addWhirl(const WhirlDef &whirl)
{
	for (int i = 0; i < _grid.size(); ++i)
	{
		for (int j = 0; j < _grid[i].size(); ++j)
		{
			b2Vec2 point;
			point.x = i * _gridStep;
			point.y = j * _gridStep;
			
			float dist = getDist(point, whirl.center);
			if (dist > whirl.outer.radius || dist < whirl.inner.radius)
				continue;


			float difR = whirl.outer.radius - whirl.inner.radius;
			float multiplier = dist - whirl.inner.radius;

			b2Vec2 radialDir = point - whirl.center;
			radialDir.Normalize();
			float stepRadForce = (whirl.outer.radialForce - whirl.inner.radialForce) / difR;
			float radForce = whirl.inner.radialForce + stepRadForce * multiplier;
			b2Vec2 radForceVector = -radialDir * radForce;

			b2Vec2 tangDir;
			tangDir.x = radialDir.y;
			tangDir.y = -radialDir.x;
			float stepTangForce = (whirl.outer.tangentialForce - whirl.inner.tangentialForce) / difR;
			float tangForce = whirl.inner.tangentialForce + stepTangForce * multiplier;
			b2Vec2 tangForceVector = tangDir * tangForce;

			b2Vec2 sumForce = tangForceVector + radForceVector;
			
			_grid[i][j].x += sumForce.x;
			_grid[i][j].y += sumForce.y;
		}
	}
}

b2Vec2 GridForceField::getForce(const b2Vec2 &coordinate)
{
	int index1X = coordinate.x / _gridStep;
	int index1Y = coordinate.y / _gridStep;
	
	//getting two other neighbor dots
	int index2X = index1X + 1;
	int index2Y = index1Y + 1;
	
	b2Vec2 f1 = _grid[index1X][index1Y];
	b2Vec2 f2 = _grid[index1X][index2Y];
	b2Vec2 f3 = _grid[index2X][index1Y];
	b2Vec2 f4 = _grid[index2X][index2Y];

	b2Vec2 coord1;
	coord1.x = index1X * _gridStep;
	coord1.y = index1Y * _gridStep;

	b2Vec2 coord2;
	coord2.x = index1X * _gridStep;
	coord2.y = index2Y * _gridStep;

	b2Vec2 coord3;
	coord3.x = index2X * _gridStep;
	coord3.y = index1Y * _gridStep;

	b2Vec2 coord4;
	coord4.x = index2X * _gridStep;
	coord4.y = index2Y * _gridStep;

	float d1 = getDist(coord1, coordinate);
	float d2 = getDist(coord2, coordinate);
	float d3 = getDist(coord3, coordinate);
	float d4 = getDist(coord4, coordinate);

	float c1 = std::max(0.0f, _gridStep - d1);
	float c2 = std::max(0.0f, _gridStep - d2);
	float c3 = std::max(0.0f, _gridStep - d3);
	float c4 = std::max(0.0f, _gridStep - d4);

	b2Vec2 force = (c1 * f1 + c2 * f2 + c3 * f3 + c4 * f4) / _gridStep;

	return force;
}

float GridForceField::getDist(const b2Vec2 &a, const b2Vec2 &b)
{
	b2Vec2 cath = b - a;

	float dist = sqrt(cath.x * cath.x + cath.y * cath.y);

	return dist;
}
