#include "Terrain.h"

namespace mview
{

	Terrain::Terrain(): TriangleMesh()
	{
		
	}

	Terrain::Terrain(const TerrainParams& data): Terrain()
	{
		

		m_data = data; m_objectName = getFileName(m_data.heightFieldFile);
		if (!LoadBitmapHeightMap())
		{
			Logger::Message(LOG_WARNING, "Heightmap file load failed.");
			return;
		}

		m_numLines = m_data.width * m_data.width;

					
		SetTerrainCoordinates();

		//Create mesh vertices
		int i, j, index, index1, index2, index3, index4;


		// Calculate the number of vertices in the 3D terrain model.
		m_numVertices = (m_data.height - 1) * (m_data.width - 1) * 6;
		m_numTris = (m_data.height - 1) * (m_data.width - 1) * 2;

		
		// Load the 3D terrain model with the height map terrain data.
		// We will be creating 2 triangles for each of the four points in a quad.	

		for (j = 0; j<(m_data.height - 1); j++)
		{
			for (i = 0; i<(m_data.width - 1); i++)
			{
				// Get the indexes to the four points of the quad.
				index1 = (m_data.width * j) + i;          // Upper left.
				index2 = (m_data.width * j) + (i + 1);      // Upper right.
				index3 = (m_data.width * (j + 1)) + i;      // Bottom left.
				index4 = (m_data.width * (j + 1)) + (i + 1);  // Bottom right.

				// Now create two triangles for that quad.
				// Triangle 1 - Upper left.
				m_vertices[VA_POSITION].unstructuredData.push_back( m_heightMap[index1].x );
				m_vertices[VA_POSITION].unstructuredData.push_back( m_heightMap[index1].y );
				m_vertices[VA_POSITION].unstructuredData.push_back( m_heightMap[index1].z );
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.r);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.g);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.b);
				m_vertices[VA_UV].unstructuredData.push_back(0.f);
				m_vertices[VA_UV].unstructuredData.push_back(0.f);
				
				// Triangle 1 - Upper right.
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index2].x);
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index2].y);
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index2].z);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.r);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.g);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.b);
				m_vertices[VA_UV].unstructuredData.push_back(1.f);
				m_vertices[VA_UV].unstructuredData.push_back(0.f);
				
				// Triangle 1 - Bottom left.
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index3].x);
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index3].y);
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index3].z);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.r);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.g);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.b);
				m_vertices[VA_UV].unstructuredData.push_back(0.f);
				m_vertices[VA_UV].unstructuredData.push_back(1.f);
				
				// Triangle 2 - Bottom left.
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index3].x);
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index3].y);
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index3].z);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.r);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.g);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.b);
				m_vertices[VA_UV].unstructuredData.push_back(0.f);
				m_vertices[VA_UV].unstructuredData.push_back(1.f);
				
				// Triangle 2 - Upper right.
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index2].x);
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index2].y);
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index2].z);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.r);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.g);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.b);
				m_vertices[VA_UV].unstructuredData.push_back(1.f);
				m_vertices[VA_UV].unstructuredData.push_back(0.f);
				
				// Triangle 2 - Bottom right.
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index4].x);
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index4].y);
				m_vertices[VA_POSITION].unstructuredData.push_back(m_heightMap[index4].z);				
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.r);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.g);
				m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.b);
				m_vertices[VA_UV].unstructuredData.push_back(1.f);
				m_vertices[VA_UV].unstructuredData.push_back(1.f);
			}
		}

	
		m_terrainType = TT_TRIMESH;

		

		m_initialized = true;
	}


	Terrain::~Terrain()
	{
		if (m_heightMap) delete m_heightMap;
	}

	bool Terrain::LoadBitmapHeightMap()
	{

		int error, imageSize, i, j, k, index;
		FILE* filePtr;
		unsigned long long count;
		BITMAPFILEHEADER bitmapFileHeader;
		BITMAPINFOHEADER bitmapInfoHeader;
		unsigned char* bitmapImage;
		unsigned char height;
				

		// Open the bitmap map file in binary.
		error = fopen_s(&filePtr, m_data.heightFieldFile.c_str(), "rb");
		if (error != 0)
		{
			Logger::Message(LOG_WARNING, "Heightmap file " + m_data.heightFieldFile + " could not be opened.");
			return false;
		}

		// Read in the bitmap file header.
		count = fread(&bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, filePtr);
		if (count != 1)
		{
			Logger::Message(LOG_WARNING, "Heightmap file " + m_data.heightFieldFile + " header error.");
			return false;
		}

		// Read in the bitmap info header.
		count = fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, filePtr);
		if (count != 1)
		{
			Logger::Message(LOG_WARNING, "Heightmap file " + m_data.heightFieldFile + " header error.");
			return false;
		}

		m_data.width = bitmapInfoHeader.biWidth; m_data.height = bitmapInfoHeader.biHeight;

		// Start by creating the array structure to hold the height map data.
		m_heightMap = new HeightMapType[m_data.width * m_data.height];

		// Make sure the height map dimensions are the same as the terrain dimensions for easy 1 to 1 mapping.
		if ((bitmapInfoHeader.biHeight != m_data.height) || (bitmapInfoHeader.biWidth != m_data.width))
		{
			return false;
		}

		// Calculate the size of the bitmap image data.  
		// Since we use non-divide by 2 dimensions (eg. 257x257) we need to add an extra byte to each line.
		imageSize = m_data.height * ((m_data.width * 3) + 1);

		// Allocate memory for the bitmap image data.
		bitmapImage = new unsigned char[imageSize];
		

		// Move to the beginning of the bitmap data.
		fseek(filePtr, bitmapFileHeader.bfOffBits, SEEK_SET);

		// Read in the bitmap image data.
		count = fread(bitmapImage, 1, imageSize, filePtr);
		if (count != imageSize)
		{
			Logger::Message(LOG_WARNING, "Heightmap file " + m_data.heightFieldFile + " read error.");
			return false;
		}

		// Close the file.
		error = fclose(filePtr);
		if (error != 0)
		{
			Logger::Message(LOG_WARNING, "Heightmap file " + m_data.heightFieldFile + " close error.");
			return false;
		}

		// Initialize the position in the image data buffer.
		k = 0;

		// Read the image data into the height map array.
		for (j = 0; j<m_data.height; j++)
		{
			for (i = 0; i<m_data.width; i++)
			{
				// Bitmaps are upside down so load bottom to top into the height map array.
				index = (m_data.width * (m_data.height - 1 - j)) + i;

				// Get the grey scale pixel value from the bitmap image data at this location.
				height = bitmapImage[k];

				// Store the pixel value as the height at this point in the height map array.
				m_heightMap[index].y = (float)height;

				// Increment the bitmap image data index.
				k += 3;
			}

			// Compensate for the extra byte at end of each line in non-divide by 2 bitmaps (eg. 257x257).
			k++;
		}

		// Release the bitmap image data now that the height map array has been loaded.
		delete[] bitmapImage;
		bitmapImage = 0;

		return true;
	}

	void Terrain::LoadDummyData()
	{
		float pointPosX = 0.f - ((float)m_data.width - m_data.spacing) / 2.f * m_data.spacing;
		float endPointPosX = pointPosX;
		float pointPosZ = 0.f - ((float)m_data.height - m_data.spacing) / 2.f * m_data.spacing;
		float endPointPosZ = pointPosZ;


		//Filling Vertex positions and colors
		//Vertical line
		for (int i = 0; i < m_data.width; i++) {
			m_vertices[VA_POSITION].unstructuredData.push_back(pointPosX); //X
			m_vertices[VA_POSITION].unstructuredData.push_back(0.f); //Y
			m_vertices[VA_POSITION].unstructuredData.push_back(endPointPosZ); //Z
			m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.r);
			m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.g);
			m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.b);


			m_vertices[VA_POSITION].unstructuredData.push_back(pointPosX); //X
			m_vertices[VA_POSITION].unstructuredData.push_back(0.f); //Y
			m_vertices[VA_POSITION].unstructuredData.push_back(-endPointPosZ); //Z
			m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.r);
			m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.g);
			m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.b);
			pointPosX += m_data.spacing;
		}


		//Horizontal lines
		for (int i = 0; i < m_data.height; i++) {
			m_vertices[VA_POSITION].unstructuredData.push_back(endPointPosX); //X
			m_vertices[VA_POSITION].unstructuredData.push_back(0.f); //Y
			m_vertices[VA_POSITION].unstructuredData.push_back(pointPosZ); //Z
			m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.r);
			m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.g);
			m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.b);

			m_vertices[VA_POSITION].unstructuredData.push_back(-endPointPosX); //X
			m_vertices[VA_POSITION].unstructuredData.push_back(0.f); //Y
			m_vertices[VA_POSITION].unstructuredData.push_back(pointPosZ); //Z			
			m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.r);
			m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.g);
			m_vertices[VA_COLOR].unstructuredData.push_back(m_data.color.b);


			pointPosZ += m_data.spacing;
		}

		m_numVertices = m_vertices[VA_POSITION].unstructuredData.size() / VertexAttribute::ElementsPerVertex(VA_POSITION);

	}

	void Terrain::SetTerrainCoordinates()
	{
		int i, j, index;
		int height_2 = m_data.height / 2;  //Using this so the grid will be centered on the origin
		int width_2 = m_data.width / 2;

		// Loop through all the elements in the height map array and adjust their coordinates correctly.
		
		for (j = 0; j<m_data.height; j++)
		{
			for (i = 0; i<m_data.width; i++)
			{
				index = (m_data.width * j) + i;

				// Set the X and Z coordinates.
				m_heightMap[index].x = (float)i - width_2;
				m_heightMap[index].z = -(float)j + height_2;

				// Move the terrain depth into the positive range.  For example from (0, -256) to (256, 0).
				//m_heightMap[index].z += (float)(m_data.height - 1);

				// Scale the height.
				m_heightMap[index].y /= m_data.scale;
			}
		}		

		return;
	}

}