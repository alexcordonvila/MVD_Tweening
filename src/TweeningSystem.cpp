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
void TweeningSystem::Translation(lm::vec3 start, lm::vec3 end, GLuint numframes, int easing, std::string  target_ent) 
{
	//Animation& anim = ECS.getComponentFromEntity<Animation>("TweeningBall");

	switch (easing){
	//switch (resolveOption(easing)) {
	case 0:
		linear(start, end, numframes, target_ent);
		break; 
	case 1:
		cubic(start, end, numframes, target_ent);
		break;

	 
	default: 
		std::cout << "This easing doesn't exist" << '\n';
	}
}
void TweeningSystem::Rotation(lm::vec3 start, lm::vec3 end, GLuint numframes, std::string easing, std::string  target_ent) {
	
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
bool TweeningSystem::linear(lm::vec3 start, lm::vec3 end, GLuint numframes, std::string  target_ent) {
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
	Tweening& tween = ECS.createComponentForEntity<Tweening>(entity_id);
	float a = start.x, b = end.x, c = start.y, d = end.y, e = start.z, f = end.z;
	for (int i = 0; i <= 100; i+= (100/numframes) ) {
		float newXPosition = lerp(a, b, (float)i / 100.0f);
		float newYPosition = lerp(c, d, (float)i / 100.0f);
		float newZPosition = lerp(e, f, (float)i / 100.0f);

		std::cout << "New position= " << newXPosition << '\n';
		positions.push_back(lm::vec3(newXPosition, newYPosition, newZPosition));
		
		lm::mat4 new_frame;
		//translation matrix
		lm::mat4 translation;

		translation.makeTranslationMatrix(newXPosition, newYPosition, newZPosition);

		//rotation matrix

		lm::mat4 rotation;
		//scale matrix
		lm::mat4 scale;

		new_frame = translation * new_frame;

		tween.keyframes.push_back(new_frame);

		tween.num_frames = numframes;
		tween.ms_frame = 1000.0f / (float)numframes;
	}
}

bool TweeningSystem::cubic(lm::vec3 start, lm::vec3 end, GLuint numframes, std::string  target_ent) {
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
	Animation& anim = ECS.createComponentForEntity<Animation>(entity_id);

	float a = start.x, b = end.x, c = start.y, d = end.y, e = start.z, f = end.z;
	for (int i = 0; i <= 100; i += (100 / numframes)) {
		float newXPosition = cubicInterpolation(a, b, (float)i / 100.0f);
		float newYPosition = cubicInterpolation(c, d, (float)i / 100.0f);
		float newZPosition = cubicInterpolation(e, f, (float)i / 100.0f);

		std::cout << "X position= " << (float)newXPosition << '\n';
		std::cout << "Y position= " << (float)newYPosition << '\n';
		std::cout << "Z position= " << (float)newZPosition << '\n';
		positions.push_back(lm::vec3(newXPosition, newYPosition, newZPosition));

		lm::mat4 new_frame;
		//translation matrix
		lm::mat4 translation;

		translation.makeTranslationMatrix(newXPosition, newYPosition, newZPosition);

		//rotation matrix

		lm::mat4 rotation;
		//scale matrix
		lm::mat4 scale;

		new_frame = translation * new_frame;

		anim.keyframes.push_back(new_frame);

		anim.num_frames = numframes;
		anim.ms_frame = 1000.0f / (float)numframes;
	}
}