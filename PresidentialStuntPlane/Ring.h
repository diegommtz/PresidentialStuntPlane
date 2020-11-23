#pragma once
class Ring
{
public:
	/// <summary>
	/// current position
	/// </summary>
	float pos[3];

	/// <summary>
	/// radius of the ring
	/// </summary>
	float radius;

	/// <summary>
	/// thickiness of the ring
	/// </summary>
	float thick;

	Ring();
	bool CheckCollision(float planePos[3], float planeRadius);
	void SetRandPosition(float planePos[3]);
	void Draw();
	~Ring();
};

