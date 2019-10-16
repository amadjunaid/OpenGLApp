
#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "CommonUtils.h"
#include "MObject.h"
#include "TriangleMesh.h"
#include "Param.h"

namespace mview {
	enum RENDER_MODE { RM_NORMAL, RM_WIREFRAME, RM_COUNT };
	//************
	//Base class for scene objects i.e. objects visible in the scene(meshes, lights etc).. exceptions are textures etc
	//************
	class DLLEXPORT SceneObject: public MObject
	{
	
	protected:		
		shrd_mat4 m_pose;

		std::vector<shrd_TriangleMesh> m_meshes;
	public:						
		
		shrd_Param_T<RENDER_MODE> m_renderMode;
		SceneObject();
		virtual ~SceneObject();

		shrd_mat4 getPose();
		glm::vec3 getPosition();

		virtual const std::vector<shrd_TriangleMesh>& getTriMeshes();

		enum {PM_RENDERMODE, PM_POSE, COUNT};
	};

	typedef std::shared_ptr<SceneObject> shrd_SceneObject;
	typedef std::vector<shrd_SceneObject> SceneObjectList;
	typedef std::shared_ptr<SceneObjectList> shrd_SceneObjectList;
	typedef SceneObjectList::iterator SceneObjectList_Itr;
}
#endif // !SCENEOBJECT_H








