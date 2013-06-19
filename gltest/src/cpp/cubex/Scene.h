/*
 * Scene.h
 *
 *  Created on: Jun 19, 2013
 *      Author: imizus
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "ShaderProgram.h"
#include "MeshBuffer.h"

#include "MeshBuffer.h"

namespace cubex
{

	class Scene
	{
	private:
		ShaderProgram* program = NULL;
		MeshBuffer* meshBuffer = NULL;

		int vertexCoordinatesAttrib;
		int textureCoordinatesAttrib;
		int diffuseColorAttrib;

		int matrixUniform;

		int viewWidth, viewHeight;

		int textureID;

	public:
		Scene(const string& modelFileName, const string& vertexShaderFileName, const string& fragmentShaderFileName, int viewWidth, int viewHeight);
		void resizeViewport(int width, int height);
		void draw(float angle);

		virtual ~Scene();
	};

}
#endif