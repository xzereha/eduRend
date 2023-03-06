export module Drawcall;

export import :Shapes;
export import :Material;
export import :Vertex;

import <vector>;
import <string>;

/**
 * @brief Contains the data specifying a drawcall
*/
export struct Drawcall
{
    std::string GroupName; //!< Name of the drawcall group
    int MaterialIndex = -1; //!< Index of the material used in the drawcall
    std::vector<Triangle> Triangles; //!< List of the Triangles in the drawcall
    std::vector<Quad> Quads; //!< List of the Quads in the drawcall

    /**
     * @brief Used for sorting Drawcalls based on material
    */
    bool operator < (const Drawcall& other) const
    {
        return MaterialIndex < other.MaterialIndex;
    }
};