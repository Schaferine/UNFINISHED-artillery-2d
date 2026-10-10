#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

struct projectileMotion {
	double initialVelocity;
	double verticalInitialVelocity;
	double horizontalInitialVelocity;
	double finalVelocity;
	double time;
	double range;
	double height;
	double angle;
};
class physicsBody {
public:
	double mass;
	double velocity;
	double acceleration;
private:

};

#endif