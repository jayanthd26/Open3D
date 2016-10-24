// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2015 Qianyi Zhou <Qianyi.Zhou@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#pragma once

#include <Core/Geometry/Geometry.h>

#include <Visualization/Shader/SimpleShader.h>
#include <Visualization/Shader/SimpleBlackShader.h>
#include <Visualization/Shader/PhongShader.h>
#include <Visualization/Shader/ImageShader.h>

namespace three {

namespace glsl {
	
class GeometryRenderer
{
public:
	virtual ~GeometryRenderer() {}

public:
	virtual bool Render(const RenderOption &option,
			const ViewControl &view) = 0;

	/// Function to add geometry to the renderer
	/// 1. After calling the function, the renderer owns the geometry object.
	/// 2. This function returns FALSE if the geometry type is not matched to
	/// the renderer.
	/// 3. If an added geometry is changed, programmer must call
	/// UpdateGeometry() to notify the renderer.
	virtual bool AddGeometry(std::shared_ptr<const Geometry> geometry_ptr) = 0;

	/// Function to upadte geometry
	/// Programmer must call this function to notify a change of the geometry
	virtual bool UpdateGeometry() = 0;

	bool HasGeometry() const {
		return bool(geometry_ptr_);
	}
	Geometry::GeometryType GetGeometryType() { return type_; }
	
protected:
	std::shared_ptr<const Geometry> geometry_ptr_;
	
private:
	Geometry::GeometryType type_;
};

class PointCloudRenderer : public GeometryRenderer
{
public:
	~PointCloudRenderer() override {}
	
public:
	bool Render(const RenderOption &option, const ViewControl &view) override;
	bool AddGeometry(std::shared_ptr<const Geometry> geometry_ptr) override;
	bool UpdateGeometry() override;
	
protected:
	SimpleShaderForPointCloud simple_point_shader_;
	PhongShaderForPointCloud phong_point_shader_;
	SimpleBlackShaderForPointCloudNormal simpleblack_normal_shader_;
};

class LineSetRenderer : public GeometryRenderer
{
public:
	~LineSetRenderer() override {}
	
public:
	bool Render(const RenderOption &option, const ViewControl &view) override;
	bool AddGeometry(std::shared_ptr<const Geometry> geometry_ptr) override;
	bool UpdateGeometry() override;
	
protected:
	SimpleShaderForLineSet simple_lineset_shader_;
};

class TriangleMeshRenderer : public GeometryRenderer
{
public:
	~TriangleMeshRenderer() override {}
	
public:
	bool Render(const RenderOption &option, const ViewControl &view) override;
	bool AddGeometry(std::shared_ptr<const Geometry> geometry_ptr) override;
	bool UpdateGeometry() override;
	
protected:
	SimpleShaderForTriangleMesh simple_mesh_shader_;
	PhongShaderForTriangleMesh phong_mesh_shader_;
	SimpleBlackShaderForTriangleMeshWireFrame simpleblack_wireframe_shader_;
};

class ImageRenderer : public GeometryRenderer
{
public:
	~ImageRenderer() override {}
	
public:
	bool Render(const RenderOption &option, const ViewControl &view) override;
	bool AddGeometry(std::shared_ptr<const Geometry> geometry_ptr) override;
	bool UpdateGeometry() override;
	
protected:
	ImageShaderForImage image_shader_;
};

}	// namespace three::glsl

}	// namespace three