export module Drawcall:Shapes;

/**
 * @brief Indices representing a triangle
*/
export struct Triangle
{
	unsigned VertexIndices[3]; //!< Indices of the triangle
};

/**
 * @brief Indices representing a quad
*/
export struct Quad
{
	unsigned VertexIndices[4]; //!< Indices of the quad
};