#pragma once
#include <include/glm.h>
#include <include/math.h>

namespace Arrow {
	class Arrow
	{
		public:
			float translateX, translateY;
			float scaleX, scaleY;
			float angularStep;
			float centerX, centerY;
			float arrowheadX, arrowheadY;

			Arrow()
			{
			}

			Arrow(float translateX, float translateY, float scaleX, float scaleY, float angularStep, float centerX, float centerY, float arrowheadX, float arrowheadY)
			{
				Set(translateX, translateY, scaleX, scaleY, angularStep, centerX, centerY, arrowheadX, arrowheadY);
			}

			~Arrow()
			{ }

			void Set(float translateX, float translateY, float scaleX, float scaleY, float angularStep, float centerX, float centerY, float arrowheadX, float arrowheadY)
			{
				this->translateX = translateX;
				this->translateY = translateY;
				this->scaleX = scaleX;
				this->scaleY = scaleY;
				this->angularStep = angularStep;
				this->centerX = centerX;
				this->centerY = centerY;
				this->arrowheadX = arrowheadX;
				this->arrowheadY = arrowheadY;
			}
	};
}

