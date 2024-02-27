/*   Copyright (C) 2023 Lidia Ortega Alvarado, Alfonso Lopez Ruiz
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see https://github.com/AlfonsoLRz/AG2223.
*/

#pragma once

#include "stdafx.h"
#include "ApplicationState.h"
#include "Camera.h"
#include "Model3D.h"

namespace AlgGeom
{
	class SceneContent
	{
	public:
		std::vector<std::unique_ptr<Camera>>	_camera;
		std::vector<std::unique_ptr<Model3D>>	_model;

		SceneContent();
		virtual ~SceneContent();

		void addNewCamera(ApplicationState* appState);
		void addNewModel(Model3D* model);
		void buildCamera(uint16_t width, uint16_t height);
		void buildScenario();
		Model3D* getModel(Model3D::Component* component);
	};
}