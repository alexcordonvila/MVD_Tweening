#include "TweeningSystem.h"
#include "extern.h"

#include <iostream>
#include <string>
TweeningSystem::TweeningSystem() {

}
void TweeningSystem::update(float dt) {

	//access our animation components and do stuff with them
	auto& tweens = ECS.getAllComponents<Tweening>();


	//loop all animation components
	for (auto& tween : tweens) {

		Transform& transform = ECS.getComponentFromEntity<Transform>(tween.owner);
		tween.ms_counter += dt * 1000;
		//Here we can modify the tweening function in runtime

		if (tween.ms_counter >= tween.ms_frame) {
			//stop counter from overflowing
			tween.ms_counter = tween.ms_counter - tween.ms_frame;

			//set transform
			transform.set(tween.keyframes[tween.curr_frame]);

			//advance frame
			tween.curr_frame++;
			//loop
			if (tween.curr_frame == tween.num_frames)
				tween.curr_frame = 0;
		}
		
	}
}
//Aquest metode el podras cridar per seleccionar quina funció vols crear

void TweeningSystem::Tween(lm::vec3 startT, lm::vec3 endT, GLuint numframes, int easingT, lm::vec3 startR, lm::vec3 endR, int easingR, std::string  target_ent)
{
	execute_(startT, endT, startR, endR, numframes, target_ent, easingT, easingR);
}

float TweeningSystem::lerp(float a, float b, float f)
{
	return a + f * (b - a);
}
float TweeningSystem::cubicInterpolation(float a, float b, float f)
{
	return a + (f*f*f) * (b - a);
	
}

float TweeningSystem::easeOutSine(float a, float b, float f)
{
	return a + sin((f * 3.1416) / 2) * (b - a);
}
float TweeningSystem::easeOutQuint(float a, float b, float f)
{
	return a + (1 - pow(1 - f, 5)) * (b - a);

}
float TweeningSystem::easeOutBounce(float a, float b, float f)
{
	float n1 = 7.5625;
	float d1 = 2.75;

	if (f < 1 / d1) {
		return a + (n1 * f * f) * (b-a);
	}
	else if (f < 2 / d1) {
		return a + (n1 * (f -= 1.5 / d1) * f + 0.75) * (b -a);
	}
	else if (f < 2.5 / d1) {
		return a + (n1 * (f -= 2.25 / d1) * f + 0.9375) * (b-a);
	}
	else {
		return a+ (n1 * (f -= 2.625 / d1) * f + 0.984375) * (b-a);
	}

}
bool TweeningSystem::execute_(lm::vec3 startT, lm::vec3 endT, lm::vec3 startR, lm::vec3 endR, GLuint numframes, std::string  target_ent, int optionT, int optionR) {
	int entity_id;
	float newXPosition, newYPosition, newZPosition, newXRotation, newYRotation, newZRotation;
//	std::vector<lm::vec3> positions; // Guardarem aqui les posicións a enviar a l'animació
	if (target_ent != "") {
		entity_id = ECS.getEntity(target_ent);
		if (entity_id == -1) {
			std::cout << "ERROR: entity doesn't exist\n";
			return false;
		}
	}
	//create tween component for entity based in a tweening function
	Tweening& tween = ECS.createComponentForEntity<Tweening>(entity_id);
	float a = startT.x, b = endT.x, c = startT.y, d = endT.y, e = startT.z, f = endT.z;
	float g = startR.x, h = endR.x, n = startR.y, j = endR.y, k = startR.z, l = endR.z;
	for (int i = 0; i <= 100; i+= (100/numframes) ) {
		switch (optionT) {
		case 0:
			 newXPosition = lerp(a, b, (float)i / 100.0f);
			 newYPosition = lerp(c, d, (float)i / 100.0f);
			 newZPosition = lerp(e, f, (float)i / 100.0f);
			break;
		case 1:
			newXPosition = cubicInterpolation(a, b, (float)i / 100.0f);
			newYPosition = cubicInterpolation(c, d, (float)i / 100.0f);
			newZPosition = cubicInterpolation(e, f, (float)i / 100.0f);
			break;
		case 2:
			newXPosition = easeOutSine(a, b, (float)i / 100.0f);
			newYPosition = easeOutSine(c, d, (float)i / 100.0f);
			newZPosition = easeOutSine(e, f, (float)i / 100.0f);
			break;
		case 3:
			newXPosition = easeOutQuint(a, b, (float)i / 100.0f);
			newYPosition = easeOutQuint(c, d, (float)i / 100.0f);
			newZPosition = easeOutQuint(e, f, (float)i / 100.0f);
			break;
		case 4:
			newXPosition = easeOutBounce(a, b, (float)i / 100.0f);
			newYPosition = easeOutBounce(c, d, (float)i / 100.0f);
			newZPosition = easeOutBounce(e, f, (float)i / 100.0f);
			break;
		default:
			std::cout << "This easing doesn't exist" << '\n';
		}
		switch (optionR) {
		case 0:
			newXRotation = lerp(g, h, (float)i / 100.0f);
			newYRotation = lerp(n, j, (float)i / 100.0f);
			newZRotation = lerp(k, l, (float)i / 100.0f);
			break;
		case 1:
			newXRotation = cubicInterpolation(g, h, (float)i / 100.0f);
			newYRotation = cubicInterpolation(n, j, (float)i / 100.0f);
			newZRotation = cubicInterpolation(k, l, (float)i / 100.0f);
			break;
		case 2:
			newXRotation = easeOutSine(g, h, (float)i / 100.0f);
			newYRotation = easeOutSine(n, j, (float)i / 100.0f);
			newZRotation = easeOutSine(k, l, (float)i / 100.0f);
			break;

		case 3:
			newXRotation = easeOutQuint(a, b, (float)i / 100.0f);
			newYRotation = easeOutQuint(c, d, (float)i / 100.0f);
			newZRotation = easeOutQuint(e, f, (float)i / 100.0f);
			break;
		default:
			std::cout << "This easing doesn't exist" << '\n';
		}
	
		lm::mat4 new_frame;
		//translation matrix
		lm::mat4 translation;

		translation.makeTranslationMatrix(newXPosition, newYPosition, newZPosition);

		//rotation matrix

		lm::mat4 rotation;
		lm::quat qrot(newXRotation, newYRotation, newZRotation);
		
		rotation.makeRotationMatrix(qrot);
		//scale matrix
		lm::mat4 scale;

		new_frame = translation * rotation * new_frame;

		tween.keyframes.push_back(new_frame);

		tween.num_frames = numframes;
		tween.ms_frame = 1000.0f / (float)numframes;
	}
}
