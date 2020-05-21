#pragma once

#include "includes.h"
#include "Shader.h"
#include "Components.h"
//We use this enum to let users select the type of easing ny name
enum Options {
	Option_Invalid,
	Option1,
	Option2,
	//others...
};
class TweeningSystem {
	
public:
	int type;
	TweeningSystem();
	//~AnimationSystem();
	//void init();
	//void lateInit();*/
	void update(float dt);
	Options resolveOption(std::string input);
	void Tween(lm::vec3 startT, lm::vec3 endT, GLuint numframes, int easingT, lm::vec3 startR, lm::vec3 endR, int easingR,  std::string  target_ent);
	void Rotation(lm::vec3 start, lm::vec3 end, GLuint numframes, int easing, std::string  target_ent);

	 bool execute(lm::vec3 startT, lm::vec3 endT, lm::vec3 startR, lm::vec3 endR, GLuint numframes, std::string  target_ent);
	 bool cubic(lm::vec3 startT, lm::vec3 endT, lm::vec3 startR, lm::vec3 endR, GLuint numframes, std::string  target_ent);
	 
	 float lerp(float a, float b, float f);
	 float cubicInterpolation(float a, float b, float f);
	 float easeOutSine(float a, float b, float f);
	 
};