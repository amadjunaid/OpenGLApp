#pragma once
#ifndef ARCBALL_H
#define ARCBALL_H
#include "CommonUtils_Lib_OpenGL.h"
#include "GLTriangleMesh.h"

namespace mview {

	class Arcball
	{
	private:
		float fov;
		int fovStartY;
		int fovCurrentY;

		float transX, transY;
		float currentTransX, currentTransY;
		float startTransX, startTransY;

		glm::mat4 startMatrix;
		glm::mat4 currentMatrix;
		glm::vec3 startRotationVector;
		glm::vec3 currentRotationVector;
		bool isRotating;
		float ballRadius;
		double residualSpin;
		static const float INITIAL_FOV;
		static const float MINIMAL_FOV;
		static const float TRANSLATION_FACTOR;

		glm::vec3 convertXY(int x, int y);
		int width, height;
	public:
		Arcball();

		void setWidthHeight(int w, int h);
		void startRotation(int , int );
		void updateRotation(int , int );
		void stopRotation(GLSimpleBox& box);


		void applyTranslationMatrix(bool reverse = false);
		glm::mat4 getRotationMatrix(GLSimpleBox& box); //Make generic for all models

		void setRadius(const float& newRadius);
		void reset();
	};

}

#endif // !ARCBALL_H




