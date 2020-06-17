#include "Controller_Walker.h"


namespace mview
{

	Controller_Walker::Controller_Walker(shrd_mat4 viewMat_cam, shrd_Param_mat4 viewMatCombined) : CameraController(viewMat_cam, viewMatCombined)
	{
		m_translationVec = glm::vec3((viewMatCombined->Get())[3].x, (viewMatCombined->Get())[3].y, (viewMatCombined->Get())[3].z);
		
		m_frameTime = 0.003f;

		m_forwardSpeed = 0.0f;
		m_backwardSpeed = 0.0f;
		m_upwardSpeed = 0.0f;
		m_downwardSpeed = 0.0f;
		m_leftTurnSpeed = 0.0f;
		m_rightTurnSpeed = 0.0f;
		m_lookUpSpeed = 0.0f;
		m_lookDownSpeed = 0.0f;	
		SetCombinedViewMat();
	}


	Controller_Walker::~Controller_Walker()
	{
	}

	void Controller_Walker::Resize(const int& width, const int& height, const glm::vec3& eye, const glm::vec3& up, const glm::mat4& viewMat, const glm::mat4& projMat, const Viewport& viewport)
	{
		m_width = width; m_height = height;
	}

	void Controller_Walker::MouseClick(const BUTTON& btn, const int& cx, const int& cy)
	{
		//TODO: Fix erratic mouse movement
		if (isDragging) {
			switch (btn)
			{
			case BUTTON::LEFT:
				MouseMove(cx, m_height - cy);
				break;
			/*case BUTTON::MIDDLE:
				ArcballTranslate(cx, m_height - cy);
				m_lastCx = cx; m_lastCy = m_height - cy;
				break;
			case BUTTON::RIGHT:
				ArcballWalk(m_height - cy);
				m_walkSpeed = float(m_height - cy);
				break;*/
			default:
				break;
			}
		}
		else {
			isDragging = true;
			switch (btn)
			{
			case BUTTON::LEFT:
				m_lastCx = cx; m_lastCy = m_height - cy;				
				break;
			/*case BUTTON::MIDDLE:
				m_lastCx = cx; m_lastCy = m_height - cy;
				break;
			case BUTTON::RIGHT:
				m_walkSpeed = float(m_height - cy);
				break;*/
			default:
				break;
			}
		}
	}


	void Controller_Walker::MouseRelease(const int& cx, const int& cy)
	{
		//m_TransformationMat = glm::translate(m_TransformationMat, glm::vec3(0.f, 0.f, 0.f));
		isDragging = false;
		//std::cout << "MouseReleasedNow" << std::endl;
	}

	void Controller_Walker::MouseMove(int cx, int cy)
	{
		//always compute delta
		//mousePosition is the last mouse position
		glm::vec2 mouse_delta = glm::vec2(cx - m_lastCx, cy - m_lastCy );

		const float mouseX_Sensitivity = 0.2f;
		const float mouseY_Sensitivity = 0.2f;
		//note that yaw and pitch must be converted to radians.
		//this is done in UpdateView() by glm::rotate
		m_rotation += glm::vec3(mouseY_Sensitivity * -mouse_delta.y, mouseX_Sensitivity * mouse_delta.x, 0.f);

		m_lastCx = cx; m_lastCy = cy;
		SetCombinedViewMat();
	}

	void Controller_Walker::KeyPressed(const KEY& key)
	{
		//TODO: Add acceleration to make it more attractive.
		bool keyA = false, keyD = false, keyW = false, keyS = false, keyE = false, keyQ = false, keyC = false, keyY = false;
		float posX, posY, posZ, rotX, rotY, rotZ;

		float dx = 0.f; //how much we strafe on x
		float dz = 0.f; //how much we walk on z
		// Handle the input.
		switch (key) {
		case KEY::A:
			dx = -2.f;
			break;
		case KEY::D:
			dx = 2.f;
			break;
		case KEY::W:
			keyW = true;			
			dz = 2.f;
			break;
		case KEY::S:
			keyS = true;	
			dz = -2.f;
			break;
		case KEY::E:
			keyE = true;
			//MoveUpward(keyE);
			break;
		case KEY::Q:
			keyQ = true;			
			break;
		case KEY::C:
			keyC = true;
			//MoveDownward(keyC);
			break;
		case KEY::Y:
			keyY = true;			
			break;
		default:
			break;
		}

		
		
		/*TurnRight(keyD);
		TurnLeft(keyA);
		
		LookUpward(keyQ);
				
		LookDownward(keyY);*/
		//row major
		glm::mat4 mat = *m_combinedViewMat;
		glm::vec3 forward(mat[0][2], mat[1][2], mat[2][2]);
		glm::vec3 strafe(mat[0][0], mat[1][0], mat[2][0]);

		const float speed = 0.36f;//how fast we move

		//forward vector must be negative to look forward. 
		//read :http://in2gpu.com/2015/05/17/view-matrix/
		m_translationVec += (-dz * forward + dx * strafe) * speed;
		SetCombinedViewMat();
		return;
	}

	void Controller_Walker::SetCombinedViewMat()
	{
		float yaw, pitch, roll;
		

		// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians.
		pitch = m_rotation.x * 0.0174532925f;
		yaw = m_rotation.y * 0.0174532925f;
		roll = m_rotation.z * 0.0174532925f;

		// Create the rotation matrix from the yaw, pitch, and roll values.
		//rotation = glm::yawPitchRoll(pitch, yaw, roll);

		//roll can be removed from here. because is not actually used in FPS camera
		glm::mat4 matRoll = glm::mat4(1.0f);//identity matrix; 
		glm::mat4 matPitch = glm::mat4(1.0f);//identity matrix
		glm::mat4 matYaw = glm::mat4(1.0f);//identity matrix

		//roll, pitch and yaw are used to store our angles in our class
		//matRoll = glm::rotate(matRoll, roll, glm::vec3(0.0f, 0.0f, 1.0f));
		matPitch = glm::rotate(matPitch, pitch, glm::vec3(1.0f, 0.0f, 0.0f));
		matYaw = glm::rotate(matYaw, yaw, glm::vec3(0.0f, 1.0f, 0.0f));

		//order matters
		m_rotationMat = matRoll * matPitch * matYaw;

		glm::mat4 translateMat = glm::mat4(1.0f);
		translateMat = glm::translate(translateMat, -m_translationVec);

		glm::mat4 transform = m_rotationMat * translateMat;

		*m_combinedViewMat = *m_viewMat_cam * transform;
	}

	//void Controller_Walker::MoveForward(bool keydown)
	//{
	//	float radians;


	//	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	//	if(keydown)
	//	{
	//		m_forwardSpeed += m_frameTime * 1.0f;
	//		if(m_forwardSpeed > (m_frameTime * 50.0f))
	//		{
	//			m_forwardSpeed = m_frameTime * 50.0f;
	//		}
	//	}
	//	else
	//	{
	//		m_forwardSpeed -= m_frameTime * 0.5f;

	//		if(m_forwardSpeed < 0.0f)
	//		{
	//			m_forwardSpeed = 0.0f;
	//		}
	//	}

	//	// Convert degrees to radians.
	//	radians = m_rotationY * 0.0174532925f;

	//	// Update the position.
	//	m_positionX += sinf(radians) * 0.5/*m_forwardSpeed*/;
	//	m_positionZ += cosf(radians) * 0.5/*m_forwardSpeed*/;

	//	return;
	//}


	//void Controller_Walker::MoveBackward(bool keydown)
	//{
	//	float radians;


	//	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	//	if(keydown)
	//	{
	//		m_backwardSpeed += m_frameTime * 1.0f;

	//		if(m_backwardSpeed > (m_frameTime * 50.0f))
	//		{
	//			m_backwardSpeed = m_frameTime * 50.0f;
	//		}
	//	}
	//	else
	//	{
	//		m_backwardSpeed -= m_frameTime * 0.5f;
	//	
	//		if(m_backwardSpeed < 0.0f)
	//		{
	//			m_backwardSpeed = 0.0f;
	//		}
	//	}

	//	// Convert degrees to radians.
	//	radians = m_rotationY * 0.0174532925f;

	//	// Update the position.
	//	m_positionX -= sinf(radians) * 0.5/*m_backwardSpeed*/;
	//	m_positionZ -= cosf(radians) * 0.5/*m_backwardSpeed*/;

	//	return;
	//}


	//void Controller_Walker::MoveUpward(bool keydown)
	//{
	//	// Update the upward speed movement based on the frame time and whether the user is holding the key down or not.
	//	if(keydown)
	//	{
	//		m_upwardSpeed += m_frameTime * 1.5f;

	//		if(m_upwardSpeed > (m_frameTime * 15.0f))
	//		{
	//			m_upwardSpeed = m_frameTime * 15.0f;
	//		}
	//	}
	//	else
	//	{
	//		m_upwardSpeed -= m_frameTime * 0.5f;

	//		if(m_upwardSpeed < 0.0f)
	//		{
	//			m_upwardSpeed = 0.0f;
	//		}
	//	}

	//	// Update the height position.
	//	m_positionY += 0.5/*m_upwardSpeed*/;

	//	return;
	//}


	//void Controller_Walker::MoveDownward(bool keydown)
	//{
	//	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	//	if(keydown)
	//	{
	//		m_downwardSpeed += m_frameTime * 1.5f;

	//		if(m_downwardSpeed > (m_frameTime * 15.0f))
	//		{
	//			m_downwardSpeed = m_frameTime * 15.0f;
	//		}
	//	}
	//	else
	//	{
	//		m_downwardSpeed -= m_frameTime * 0.5f;

	//		if(m_downwardSpeed < 0.0f)
	//		{
	//			m_downwardSpeed = 0.0f;
	//		}
	//	}

	//	// Update the height position.
	//	m_positionY -= 0.5/*m_downwardSpeed*/;

	//	return;
	//}


	//void Controller_Walker::TurnLeft(bool keydown)
	//{
	//	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
	//	if(keydown)
	//	{
	//		m_leftTurnSpeed += m_frameTime * 5.0f;

	//		if(m_leftTurnSpeed > (m_frameTime * 150.0f))
	//		{
	//			m_leftTurnSpeed = m_frameTime * 150.0f;
	//		}
	//	}
	//	else
	//	{
	//		m_leftTurnSpeed -= m_frameTime* 3.5f;

	//		if(m_leftTurnSpeed < 0.0f)
	//		{
	//			m_leftTurnSpeed = 0.0f;
	//		}
	//	}

	//	// Update the rotation.
	//	m_rotationY -= m_leftTurnSpeed;

	//	// Keep the rotation in the 0 to 360 range.
	//	if(m_rotationY < 0.0f)
	//	{
	//		m_rotationY += 360.0f;
	//	}

	//	return;
	//}


	//void Controller_Walker::TurnRight(bool keydown)
	//{
	//	// Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.
	//	if(keydown)
	//	{
	//		m_rightTurnSpeed += m_frameTime * 5.0f;

	//		if(m_rightTurnSpeed > (m_frameTime * 150.0f))
	//		{
	//			m_rightTurnSpeed = m_frameTime * 150.0f;
	//		}
	//	}
	//	else
	//	{
	//		m_rightTurnSpeed -= m_frameTime* 3.5f;

	//		if(m_rightTurnSpeed < 0.0f)
	//		{
	//			m_rightTurnSpeed = 0.0f;
	//		}
	//	}

	//	// Update the rotation.
	//	m_rotationY += m_rightTurnSpeed;

	//	// Keep the rotation in the 0 to 360 range.
	//	if(m_rotationY > 360.0f)
	//	{
	//		m_rotationY -= 360.0f;
	//	}

	//	return;
	//}


	//void Controller_Walker::LookUpward(bool keydown)
	//{
	//	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	//	if(keydown)
	//	{
	//		m_lookUpSpeed += m_frameTime * 7.5f;

	//		if(m_lookUpSpeed > (m_frameTime * 75.0f))
	//		{
	//			m_lookUpSpeed = m_frameTime * 75.0f;
	//		}
	//	}
	//	else
	//	{
	//		m_lookUpSpeed -= m_frameTime* 2.0f;

	//		if(m_lookUpSpeed < 0.0f)
	//		{
	//			m_lookUpSpeed = 0.0f;
	//		}
	//	}

	//	// Update the rotation.
	//	m_rotationX -= m_lookUpSpeed;

	//	// Keep the rotation maximum 90 degrees.
	//	if(m_rotationX > 90.0f)
	//	{
	//		m_rotationX = 90.0f;
	//	}

	//	return;
	//}


	//void Controller_Walker::LookDownward(bool keydown)
	//{
	//	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	//	if(keydown)
	//	{
	//		m_lookDownSpeed += m_frameTime * 7.5f;

	//		if(m_lookDownSpeed > (m_frameTime * 75.0f))
	//		{
	//			m_lookDownSpeed = m_frameTime * 75.0f;
	//		}
	//	}
	//	else
	//	{
	//		m_lookDownSpeed -= m_frameTime* 2.0f;

	//		if(m_lookDownSpeed < 0.0f)
	//		{
	//			m_lookDownSpeed = 0.0f;
	//		}
	//	}

	//	// Update the rotation.
	//	m_rotationX += m_lookDownSpeed;

	//	// Keep the rotation maximum 90 degrees.
	//	if(m_rotationX < -90.0f)
	//	{
	//		m_rotationX = -90.0f;
	//	}

	//	return;
	//}


	
}