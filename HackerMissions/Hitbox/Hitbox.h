#pragma once
#include "..\StdInclude.h"

class AABB{
private:
	
public:
	AABB expand(double xa, double ya);
	void move(double xa, double ya);
	bool inXclip(AABB target);
	bool inYclip(AABB target);
	bool hitWith(AABB target);
	double maxMoveOnXclip(AABB target, double dist);
	double maxMoveOnYclip(AABB target, double dist);
	void init(double xi, double xa, double yi, double ya);
	AABB() :xmin(0), ymin(0), xmax(0), ymax(0) {};
	AABB(double xm,double ym,double xa,double ya) :xmin(xm), ymin(ym), xmax(xa), ymax(ya) {};
	double xmin, ymin, xmax, ymax;

};