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

Options TweeningSystem::resolveOption(std::string input) {
	if (input == "Linear") return Option1;
	if (input == "Cubic") return Option2;
	//...
	return Option_Invalid;
}
void TweeningSystem::Tween(lm::vec3 startT, lm::vec3 endT, GLuint numframes, int easingT, lm::vec3 startR, lm::vec3 endR, int easingR, std::string  target_ent)
{
	
	switch (easingT){
	case 0:
		execute(startT, endT, startR, endR, numframes, target_ent);
		break; 
	case 1:
		cubic(startT, endT, startR, endR, numframes, target_ent);
		break;
	default: 
		std::cout << "This easing doesn't exist" << '\n';
	}
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


bool TweeningSystem::execute(lm::vec3 startT, lm::vec3 endT, lm::vec3 startR, lm::vec3 endR, GLuint numframes, std::string  target_ent) {
	int entity_id;
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
		float newXPosition = lerp(a, b, (float)i / 100.0f);
		float newYPosition = lerp(c, d, (float)i / 100.0f);
		float newZPosition = lerp(e, f, (float)i / 100.0f);

		float newXRotation = lerp(g, h, (float)i / 100.0f);
		float newYRotation = lerp(n, j, (float)i / 100.0f);
		float newZRotation = lerp(k, l, (float)i / 100.0f);
	
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

bool TweeningSystem::cubic(lm::vec3 startT, lm::vec3 endT, lm::vec3 startR, lm::vec3 endR, GLuint numframes, std::string  target_ent) {
	int entity_id;
	std::vector<lm::vec3> positions; // Guardarem aqui les posicións a enviar a l'animació
	if (target_ent != "") {
		entity_id = ECS.getEntity(target_ent);
		if (entity_id == -1) {
			std::cout << "ERROR: entity doesn't exist\n";
			return false;
		}
	}
	//create animation component for entity based in a tweening function
		//create tween component for entity based in a tweening function
	Tweening& tween = ECS.createComponentForEntity<Tweening>(entity_id);
	float a = startT.x, b = endT.x, c = startT.y, d = endT.y, e = startT.z, f = endT.z;
	float g = startR.x, h = endR.x, n = startR.y, j = endR.y, k = startR.z, l = endR.z;

	for (int i = 0; i <= 100; i += (100 / numframes)) {
		float newXPosition = cubicInterpolation(a, b, (float)i / 100.0f);
		float newYPosition = cubicInterpolation(c, d, (float)i / 100.0f);
		float newZPosition = cubicInterpolation(e, f, (float)i / 100.0f);

		float newXRotation = cubicInterpolation(g, h, (float)i / 100.0f);
		float newYRotation = cubicInterpolation(n, j, (float)i / 100.0f);
		float newZRotation = cubicInterpolation(k, l, (float)i / 100.0f);

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