#pragma once
#include "Component.h"
#include "Spritesheet.h"
namespace RoHAPI {

	struct AnimationClip
	{
		std::string animationName = "";
		Vec2i start_TexUV;
		Vec2i boundary_TexUV;

		AnimationClip(std::string name, Vec2i start, Vec2i boundary)					//AnimationClip requires specifying a name, a start UV, and an end UV in pixel coordinates for the spritesheet
		{																				//being used by the Animation component that contains this clip
			start_TexUV.x = start.x;
			start_TexUV.y = start.y;
			animationName = name;
			boundary_TexUV = boundary;
		};
		AnimationClip() {};
	};

	class Animation : public Component
	{
	private:
		bool flipX = false;
		std::string currentAnimation = "";
		int currentSprite = 0;
		double frameDelay = 1.0/10.0;
		double frameUpdateTime = 0;		//Time at which animation frame was last updated
		std::map<std::string, AnimationClip> clips;
		Spritesheet* m_spritesheet;

		bool looping = true;

		int currentAnimationStart = 0;
		int currentAnimationEnd = 0;

		void Animate();

	public:
		Animation(GameObject* parentObj) : Component(parentObj) { id = AnimationC; };
		virtual ~Animation();

		bool isFlipped() { return flipX; }
		void isFlipped(bool flip) { flipX = flip; }
		void Start() override;
		void Update() override;

		void AddAnimationClip(AnimationClip newAnim);

		std::string GetCurrentAnimationName() const { return currentAnimation; }

		bool SetAnimation(std::string animName);
		void SetAnimSpeed(const int newAnimSpeed) { frameDelay = newAnimSpeed; };
		void SetSpritesheet(Spritesheet* spritesheet);

		BYTE* GetCurrentSprite()const;
		int GetCurrentSpriteIndex()const { return currentSprite; }
		Rect GetBoundingBox();
		Vec2i GetSpritesheetDims() { return m_spritesheet->GetSpriteDims(); }

		void Loop(const bool shouldLoop) { looping = shouldLoop; };
		Vec2i GetIdvSpriteDims() const { return m_spritesheet->GetIdvSpriteDims(); }
	
	};
}
