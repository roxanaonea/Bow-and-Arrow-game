#pragma once
#include <include/glm.h>
#include <include/math.h>

namespace Balloon {
	class Balloon
	{
		public:
			float translateX, translateY;
			float scaleX, scaleY;
			float angularStep;

			Balloon()
			{
			}

			Balloon(float translateX, float translateY, float scaleX, float scaleY, float angularStep)
			{
				Set(translateX, translateY, scaleX, scaleY, angularStep);
			}

			~Balloon()
			{ }

			void Set(float translateX, float translateY, float scaleX, float scaleY, float angularStep)
			{
				this->translateX = translateX;
				this->translateY = translateY;
				this->scaleX = scaleX;
				this->scaleY = scaleY;
				this->angularStep = angularStep;
			}
	};
}

