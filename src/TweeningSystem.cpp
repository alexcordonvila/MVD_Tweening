#include "TweeningSystem.h"
#include "extern.h"

#include <iostream>
#include <string>
TweeningSystem::TweeningSystem() {

}
void TweeningSystem::update(float dt) {

	//access our animation components and do stuff with them
	auto& anims = ECS.getAllComponents<Animation>();


	//loop all animation components
	for (auto& anim : anims) {

		Transform& transform = ECS.getComponentFromEntity<Transform>(anim.owner);
		anim.ms_counter += dt * 1000;
		if (anim.ms_counter >= anim.ms_frame) {
			//stop counter from overflowing
			anim.ms_counter = anim.ms_counter - anim.ms_frame;

			//set transform
			transform.set(anim.keyframes[anim.curr_frame]);


			//advance frame
			anim.curr_frame++;
			//loop
			if (anim.curr_frame == anim.num_frames)
				anim.curr_frame = 0;
		}
		
	}
}
//Aquest metode el podras cridar per seleccionar quina funció vols crear

Options TweeningSystem::resolveOption(std::string input) {
	if (input == "Linear") return Option1;
	if (input == "option2") return Option2;
	//...
	return Option_Invalid;
}
void TweeningSystem::Translation(lm::vec3 start, lm::vec3 end, GLuint numframes, std::string easing, std::string  target_ent) 
{
	
	switch (resolveOption(easing)) {
	case Option1:
		linear(start, end, numframes, target_ent);
		break; 
	case Option2:

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
	Animation& anim = ECS.createComponentForEntity<Animation>(entity_id);

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

		anim.keyframes.push_back(new_frame);

		anim.num_frames = numframes;
		anim.ms_frame = 1000.0f / (float)numframes;
	}
}

