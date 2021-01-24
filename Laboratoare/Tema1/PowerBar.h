#pragma once
#include <include/glm.h>
#include <include/math.h>

namespace PowerBar {
	class PowerBar
	{
		public:
			float translateX, translateY;
			float scaleX, scaleY;
			float angularStep;

			PowerBar()
			{
			}

			PowerBar(float translateX, float translateY, float scaleX, float scaleY, float angularStep)
			{
				Set(translateX, translateY, scaleX, scaleY, angularStep);
			}

			~PowerBar()
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

