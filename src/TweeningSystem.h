#pragma once

#include "includes.h"
#include "Shader.h"
#include "Components.h"
//We use this enum to let users select the type of easing ny name

class TweeningSystem {
	
public:
	int type;
	TweeningSystem();

	void update(float dt);
	void Tween(lm::vec3 startT, lm::vec3 endT, GLuint numframes, int easingT, lm::vec3 startR, lm::vec3 endR, int easingR,  std::string  target_ent);
	 bool execute_(lm::vec3 startT, lm::vec3 endT, lm::vec3 startR, lm::vec3 endR, GLuint numframes, std::string  target_ent, int optionT, int optionR);

	 float lerp(float a, float b, float f);
	 float cubicInterpolation(float a, float b, float f);
	 float easeOutSine(float a, float b, float f);
	 float easeOutQuint(float a, float b, float f);
	 float easeOutBounce(float a, float b, float f);
};