#include "AnimationSystem.h"
#include "extern.h"

AnimationSystem::AnimationSystem() {

}
void AnimationSystem::update(float dt) {

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