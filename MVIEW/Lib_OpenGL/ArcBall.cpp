#include "ArcBall.h"

#include <glm\gtx\norm.hpp>

#define _USE_MATH_DEFINES
#include <math.h>


namespace mview {
	glm::vec3 Arcball::convertXY(int x, int y)
	{
		int d = x*x + y*y;
		float radiusSquared = ballRadius*ballRadius;
		if (d > radiusSquared)
		{
			return glm::vec3((float)x, (float)y, 0);
		}
		else
		{
			return glm::vec3((float)x, (float)y, sqrt(radiusSquared - d));
		}
	}
	/**
	* Default constructor, it sets the ballRadius to 600
	**/
	Arcball::Arcball()
	{
		this->ballRadius = 600;
		isRotating = false;
		width = height = 0;
		reset();
	}

	/**
	* Set width and height of the current windows, it's needed every time you resize the window
	* \param w Width of the rendering window
	* \param h Height of the rendering window
	**/
	void Arcball::setWidthHeight(int w, int h)
	{
		width = w;
		height = h;
		ballRadius = glm::min((int)(w / 2), (int)(h / 2));
	}
	/**
	* Start the rotation. Use this method in association with the left click.
	* Here you must give directly the coordinates of the mouse as the glut functions extract. This method supposes that the 0,0 is in the upper-left part of the screen
	* \param _x Horizontal position of the mouse (0,0) = upperleft corner (w,h) = lower right
	* \param _y Vertical position of the mouse (0,0) = upperleft corner (w,h) = lower right
	*
	**/
	void Arcball::startRotation(int _x, int _y)
	{
		int x = ((_x)-(width / 2));
		int y = ((height / 2) - _y);

		startRotationVector = convertXY(x, y);
		startRotationVector = glm::normalize(startRotationVector);

		currentRotationVector = startRotationVector;
		isRotating = true;
	}

	void Arcball::updateRotation(int _x, int _y)
	{
		int x = ((_x)-(width / 2));
		int y = ((height / 2) - _y);

		currentRotationVector = convertXY(x, y);

		currentRotationVector = glm::normalize(currentRotationVector);
	}

	void Arcball::stopRotation(GLSimpleBox& box)
	{		
		isRotating = false;
		glm::mat4 rotatedMat = getRotationMatrix(box);
		box.m_modelMat = rotatedMat;
	}
	

	void Arcball::applyTranslationMatrix(bool reverse)
	{
		float factor = (reverse ? -1.0f : 1.0f);
		float tx = transX + (currentTransX - startTransX)*TRANSLATION_FACTOR;
		float ty = transY + (currentTransY - startTransY)*TRANSLATION_FACTOR;
		//glTranslatef(factor*tx, factor*(-ty), 0);
	}

	glm::mat4 Arcball::getRotationMatrix(GLSimpleBox& box)
	{
		if (isRotating)
		{  // Do some rotation according to start and current rotation vectors
		   //cerr << currentRotationVector.transpose() << " " << startRotationVector.transpose() << endl;
			if (glm::l2Norm(currentRotationVector - startRotationVector) > 1E-6)
			{
				glm::vec3 rotationAxis = glm::cross(currentRotationVector,startRotationVector);
				rotationAxis = glm::vec3( rotationAxis );

				double val = glm::dot(currentRotationVector,startRotationVector);
				val > (1 - 1E-10) ? val = 1.0 : val = val;
				double rotationAngle = acos(val) * 180.0f / (float)M_PI;

				// rotate around the current position
				applyTranslationMatrix(true);
				currentMatrix = glm::rotate(box.m_modelMat, (float)rotationAngle * 2, glm::vec3(-rotationAxis.x, -rotationAxis.y, -rotationAxis.z));
				applyTranslationMatrix(false);
			}
		}
		return currentMatrix;

	}

	/**
	* Set the radius of the ball (a typical radius for a 1024x768 window is 600
	* \param newRadius The radius of the spherical dragging area
	**/
	void Arcball::setRadius(const float& newRadius)
	{
		ballRadius = newRadius;
	}

	void Arcball::reset()
	{
		fov = INITIAL_FOV;
		// reset matrix
		startMatrix = glm::mat4(1.0);

		transX = transY = 0;
		startTransX = startTransY = currentTransX = currentTransY = 0;
	}

	const float Arcball::INITIAL_FOV = 30;
	const float Arcball::TRANSLATION_FACTOR = 0.01f;
}