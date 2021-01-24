#pragma once
#include <include/glm.h>
#include <include/math.h>

namespace Bow {
	class Bow2
	{
		public:
			float translateX, translateY;
			float scaleX, scaleY;
			float angularStep;
			float centerX, centerY;

			Bow2()
			{
			}

			Bow2(float translateX, float translateY, float scaleX, float scaleY, float angularStep, float centerX, float centerY)
			{
				Set(translateX, translateY, scaleX, scaleY, angularStep, centerX, centerY);
			}

			~Bow2()
			{ }

			void Set(float translateX, float translateY, float scaleX, float scaleY, float angularStep, float centerX, float centerY)
			{
				this->translateX = translateX;
				this->translateY = translateY;
				this->scaleX = scaleX;
				this->scaleY = scaleY;
				this->angularStep = angularStep;
				this->centerX = centerX;
				this->centerY = centerY;
			}
	};
}

