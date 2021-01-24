#pragma once
#include <include/glm.h>
#include <include/math.h>

namespace Shuriken {
	class Shuriken
	{
		public:
			float translateX, translateY;
			float scaleX, scaleY;
			float angularStep;
			float centerX, centerY;

			Shuriken()
			{
			}

			Shuriken(float translateX, float translateY, float scaleX, float scaleY, float angularStep, float centerX, float centerY)
			{
				Set(translateX, translateY, scaleX, scaleY, angularStep, centerX, centerY);
			}

			~Shuriken()
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

