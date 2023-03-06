export module Drawcall:Vertex;

import Math;

/**
 * @brief Structure defining a vertex
*/
export struct Vertex
{
	linalg::vec3f Position; //!< 3D coordinate of the vertex
	linalg::vec3f Normal; //!< Normal of the vertex
	linalg::vec3f Tangent; //!< Tangent of the vertex
	linalg::vec3f Binormal; //!< Binormal of the vertex
	linalg::vec2f TexCoord; //!< 2D texture coordiante of the vertex
};