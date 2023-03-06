export module Drawcall:Material;

import Math;
import Texture;

import <string>;
import <unordered_map>;

/**
 * @brief Phong-esque material
*/
export struct Material
{
	linalg::vec3f AmbientColour = { 0.0f, 0.5f, 0.0f }; //!< Ambient colour component
	linalg::vec3f DiffuseColour = { 0.0f, 0.5f, 0.0f }; //!< Diffuse colour component
	linalg::vec3f SpecularColour = { 1.0f, 1.0f, 1.0f }; //!< Specular colour component

	std::string Name; //!< Name of the Material

	// File paths to textures
	std::string DiffuseTextureFilename; //!< Diffuse texture path
	std::string NormalTextureFilename; //!< Normal texture path

	// + more texture types (extend OBJLoader::LoadMaterials if needed)

	// Device textures
	Texture DiffuseTexture; //!< Diffuse Texture
	// + other texture types
};

/**
 * @brief Default material
*/
export Material DefaultMaterial = Material();

/**
 * @brief Map between Material using name as the key.
*/
export typedef std::unordered_map<std::string, Material> MaterialHash;