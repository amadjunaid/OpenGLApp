#ifndef VERTEXATTRIBUTES_H
#define VERTEXATTRIBUTES_H
#include "CommonUtils.h"

namespace mview {
	enum VERTEX_ATTRIBUTES { VA_POSITION, VA_COLOR, VA_NORMAL, VA_UV, VA_COUNT };  //Must match the layout in the shaders if used.

	union attributeDataUnion {
		glm::vec3 position;
		glm::vec3 color;
		glm::vec3 normal;		
		glm::vec2 uv;
	};

	//TODO: Implement some technique, possibly using union to view unstructuredData in a structured way i.e. glm::vec3 or glm::vec4 
	struct VertexAttribute {
		std::vector<float> unstructuredData;

		/*Dummy Default Constructor; can be used for manual initialization of members.*/
		VertexAttribute()
		{
			
		}

		VertexAttribute(int size, const float _data[])
		{
			
			unstructuredData = std::vector<float>(_data, _data + size);
		}

		VertexAttribute(std::vector<float> data)
		{
			
			data = data;
		}

		static int ElementsPerVertex(int VAType)
		{
			switch (VAType)
			{
			case VERTEX_ATTRIBUTES::VA_POSITION:
				return 3;
				break;
			case VERTEX_ATTRIBUTES::VA_NORMAL:
				return 3;
				break;
			case VERTEX_ATTRIBUTES::VA_COLOR:
				return 3;
				break;
			case VERTEX_ATTRIBUTES::VA_UV:
				return 2;
				break;
			default:
				return 0;
				break;
			}
		}
	};

	struct VertexAttributeIndex {
		std::vector<int> unstructuredData;

		int ElementsPerVertex;

		/*Dummy Default Constructor; can be used for manual initialization of members.*/
		VertexAttributeIndex()
		{
			ElementsPerVertex = 0;
		}

		VertexAttributeIndex(int size, int _ElementsPerVertex, const int _data[])
		{
			ElementsPerVertex = _ElementsPerVertex;
			unstructuredData = std::vector<int>(_data, _data + size);
		}

		VertexAttributeIndex(int _sizePerElement, std::vector<float> data)
		{
			ElementsPerVertex = _sizePerElement;
			data = data;
		}
	};
}
#endif // !VERTEXATTRIBUTES_H

