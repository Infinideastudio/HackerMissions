#include "Hitbox.h"

void AABB::init(double xi, double xa, double yi, double ya){
	xmin = xi; xmax = xa;
	ymin = yi; ymax = ya;
	return;
}

AABB AABB::expand(double xa, double ya, double za){
	AABB ret = *this;
	if (xa > 0.0)ret.xmax += xa; else ret.xmin += xa;
	if (ya > 0.0)ret.ymax += ya; else ret.ymin += ya;
	return ret;
}

void AABB::move(double xa, double ya, double za){
	xmax += xa; xmin += xa;
	ymax += ya; ymin += ya;
}

bool AABB::inXclip(AABB target){
	if (xmin>target.xmin && xmin<target.xmax || xmax>target.xmin && xmax<target.xmax)return true;
	if (target.xmin>xmin && target.xmin<xmax || target.xmax>xmin && target.xmax<xmax)return true;
}

bool AABB::inYclip(AABB target){
	if (ymin>target.ymin && ymin<target.ymax || ymax>target.ymin && ymax<target.ymax)return true;
	if (target.ymin>ymin && target.ymin<ymax || target.ymax>ymin && target.ymax<ymax)return true;
}

bool AABB::hitWith(AABB target){
	return inXclip(target) && inYclip(target);
}

double AABB::maxMoveOnXclip(AABB target,double dist){
	if (!inYclip(target))return dist;
	if (xmin>=target.xmax && dist<0.0)return std::min(target.xmax - xmin, dist);
	if (xmax<=target.xmin && dist>0.0)return std::min(target.xmin - xmax, dist);
	return dist;
}

double AABB::maxMoveOnYclip(AABB target, double dist){
	if (!inXclip(target))return dist;
	if (ymin >= target.ymax && dist<0.0)return std::min(target.ymax - ymin, dist);
	if (ymax <= target.ymin && dist>0.0)return std::min(target.ymin - ymax, dist);
	return dist;
}