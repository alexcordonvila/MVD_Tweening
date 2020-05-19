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
	TweeningSystem();
	//~AnimationSystem();
	//void init();
	//void lateInit();*/
	void update(float dt);
	Options resolveOption(std::string input);
	void Translation(lm::vec3 start, lm::vec3 end, GLuint numframes, int easing, std::string  target_ent);
	void Rotation(lm::vec3 start, lm::vec3 end, GLuint numframes, std::string easing, std::string  target_ent);

	 bool linear(lm::vec3 start, lm::vec3 end, GLuint numframes, std::string  target_ent);
	 bool cubic(lm::vec3 start, lm::vec3 end, GLuint numframes, std::string  target_ent);
	 void linearRotation();
	 float lerp(float a, float b, float f);
	 float cubicInterpolation(float a, float b, float f);
	 float easeOutSine(float a, float b, float f);
	 
};