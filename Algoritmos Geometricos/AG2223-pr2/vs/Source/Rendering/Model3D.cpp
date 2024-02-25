#include "stdafx.h"
#include "Model3D.h"

// Static properties

std::string AlgGeom::Model3D::CHECKER_PATTERN_PATH = "Assets/Textures/Checker.png";
std::unordered_set<std::string> AlgGeom::Model3D::USED_NAMES;

// Public methods

AlgGeom::Model3D::Model3D(): _modelMatrix(1.0f)
{
    this->overrideModelName();
}

AlgGeom::Model3D::~Model3D()
{
}

bool AlgGeom::Model3D::belongsModel(Component* component)
{
    for (auto& comp : _components)
    {
        if (comp.get() == component)
            return true;
    }

    return false;
}

void AlgGeom::Model3D::draw(RenderingShader* shader, MatrixRenderInformation* matrixInformation, ApplicationState* appState, GLuint primitive)
{
    shader->setSubroutineUniform(GL_VERTEX_SHADER, "instanceUniform", "singleInstanceUniform");

    for (auto& component : _components)
    {
        if (component->_enabled && component->_vao)
        {
            VAO::IBO_slots rendering = VAO::IBO_TRIANGLE;

            switch (primitive)
            {
            case GL_TRIANGLES:
                if (component->_material._useUniformColor)
                {
                    shader->setUniform("Kd", component->_material._kdColor);
                    shader->setSubroutineUniform(GL_FRAGMENT_SHADER, "kadUniform", "getUniformColor");
                }
                else
                {
                    Texture* checkerPattern = TextureList::getInstance()->getTexture(CHECKER_PATTERN_PATH);
                    checkerPattern->applyTexture(shader, 0, "texKdSampler");
                    shader->setSubroutineUniform(GL_FRAGMENT_SHADER, "kadUniform", "getTextureColor");
                }

                shader->setUniform("Ks", component->_material._ksColor);
                shader->setUniform("metallic", component->_material._metallic);
                shader->setUniform("roughnessK", component->_material._roughnessK);
                shader->setUniform("mModelView", matrixInformation->multiplyMatrix(MatrixRenderInformation::VIEW, this->_modelMatrix));

                break;
            case GL_LINES:
                rendering = VAO::IBO_LINE;
                shader->setUniform("lineColor", component->_material._lineColor);
                glLineWidth(component->_lineWidth);

                break;
            case GL_POINTS:
                rendering = VAO::IBO_POINT;
                shader->setUniform("pointColor", component->_material._pointColor);
                shader->setUniform("pointSize", component->_pointSize);

                break;
            }

            if (!component->_activeRendering[rendering]) continue;

            shader->setUniform("mModelViewProj", matrixInformation->multiplyMatrix(MatrixRenderInformation::VIEW_PROJECTION, this->_modelMatrix));
            shader->applyActiveSubroutines();

            component->_vao->drawObject(rendering, primitive, static_cast<GLuint>(component->_indices[rendering].size()));

            matrixInformation->undoMatrix(MatrixRenderInformation::VIEW);
            matrixInformation->undoMatrix(MatrixRenderInformation::VIEW_PROJECTION);
        }
    }
}

AlgGeom::Model3D* AlgGeom::Model3D::moveGeometryToOrigin(const mat4& origMatrix, float maxScale)
{
    //AABB aabb = this->getAABB();

    //vec3 translate = -aabb.center();
    //vec3 extent = aabb.extent();
    //float maxScaleAABB = std::max(extent.x, std::max(extent.y, extent.z));
    //vec3 scale = (maxScale < FLT_MAX) ? ((maxScale > maxScaleAABB) ? vec3(1.0f) : vec3(maxScale / maxScaleAABB)) : vec3(1.0f);

    //_modelMatrix = glm::scale(glm::mat4(1.0f), scale) * glm::translate(glm::mat4(1.0f), translate) * origMatrix;

    return this;
}

AlgGeom::Model3D* AlgGeom::Model3D::overrideModelName()
{
    std::string className = typeid(*this).name();
    std::string classTarget = "class ";
    size_t classIndex = className.find(classTarget);
    if (classIndex != std::string::npos)
    {
        className = className.substr(classIndex + classTarget.size(), className.size() - classIndex - classTarget.size());
    }

    unsigned modelIdx = 0;
    bool nameValid = false;

    while (!nameValid)
    {
        this->_name = className + " " + std::to_string(modelIdx);
        nameValid = USED_NAMES.find(this->_name) == USED_NAMES.end();
        ++modelIdx;
    }

    USED_NAMES.insert(this->_name);

    return this;
}

AlgGeom::Model3D* AlgGeom::Model3D::setLineColor(const vec3& color)
{
    for (auto& component : _components)
    {
        component->_material._lineColor = color;
    }

    return this;
}

AlgGeom::Model3D* AlgGeom::Model3D::setPointColor(const vec3& color)
{
    for (auto& component : _components)
    {
        component->_material._pointColor = color;
    }

    return this;
}

AlgGeom::Model3D* AlgGeom::Model3D::setTriangleColor(const vec4& color)
{
    for (auto& component : _components)
    {
        component->_material._kdColor = color;
    }

    return this;
}

AlgGeom::Model3D* AlgGeom::Model3D::setLineWidth(float width)
{
    for (auto& component : _components)
    {
        component->_lineWidth = width;
    }

    return this;
}

AlgGeom::Model3D* AlgGeom::Model3D::setPointSize(float size)
{
    for (auto& component : _components)
    {
        component->_pointSize = size;
    }

    return this;
}

AlgGeom::Model3D* AlgGeom::Model3D::setTopologyVisibility(VAO::IBO_slots topology, bool visible)
{
    for (auto& component : _components)
    {
        component->_activeRendering[topology] = visible;
    }

    return this;
}

// Private methods

void AlgGeom::Model3D::buildVao(Component* component)
{
    VAO* vao = new VAO(true);
    vao->setVBOData(component->_vertices);
    vao->setIBOData(VAO::IBO_POINT, component->_indices[VAO::IBO_POINT]);
    vao->setIBOData(VAO::IBO_LINE, component->_indices[VAO::IBO_LINE]);
    vao->setIBOData(VAO::IBO_TRIANGLE, component->_indices[VAO::IBO_TRIANGLE]);
    component->_vao = vao;
}

AlgGeom::Model3D::Component* AlgGeom::Model3D::getVoxel()
{
    Component* component = new Component;

    // Geometry
    {
        const vec3 minPosition(-.5f), maxPosition(.5f);
        const std::vector<vec3> points
        {
            vec3(minPosition[0], minPosition[1], maxPosition[2]),		vec3(maxPosition[0], minPosition[1], maxPosition[2]),
            vec3(minPosition[0], minPosition[1], minPosition[2]),	    vec3(maxPosition[0], minPosition[1], minPosition[2]),
            vec3(minPosition[0], maxPosition[1], maxPosition[2]),		vec3(maxPosition[0], maxPosition[1], maxPosition[2]),
            vec3(minPosition[0], maxPosition[1], minPosition[2]),		vec3(maxPosition[0], maxPosition[1], minPosition[2])
        };
        const std::vector<vec3> normals
        {
            glm::normalize(vec3(-0.5f, -0.5f, 0.5f)),	glm::normalize(vec3(0.5f, -0.5f, 0.5f)),
            glm::normalize(vec3(-0.5f, -0.5f, -0.5f)),	glm::normalize(vec3(0.5f, -0.5f, -0.5f)),
            glm::normalize(vec3(-0.5f, 0.5f, 0.5f)),	glm::normalize(vec3(0.5f, 0.5f, 0.5f)),
            glm::normalize(vec3(-0.5f, 0.5f, -0.5f)),	glm::normalize(vec3(0.5f, 0.5f, -0.5f))
        };
        const std::vector<vec2> textCoords{ vec2(0.0f), vec2(0.0f), vec2(0.0f), vec2(0.0f), vec2(0.0f), vec2(0.0f), vec2(0.0f), vec2(0.0f) };

        for (int pointIdx = 0; pointIdx < points.size(); ++pointIdx)
        {
            component->_vertices.push_back(VAO::Vertex{ points[pointIdx], normals[pointIdx], textCoords[pointIdx] });
        }
    }

    // Topology
    {
        component->_indices[VAO::IBO_TRIANGLE] = std::vector<GLuint>
        {
            0, 1, 2, RESTART_PRIMITIVE_INDEX, 1, 3, 2, RESTART_PRIMITIVE_INDEX, 4, 5, 6, RESTART_PRIMITIVE_INDEX,
            5, 7, 6, RESTART_PRIMITIVE_INDEX, 0, 1, 4, RESTART_PRIMITIVE_INDEX, 1, 5, 4, RESTART_PRIMITIVE_INDEX,
            2, 0, 4, RESTART_PRIMITIVE_INDEX, 2, 4, 6, RESTART_PRIMITIVE_INDEX, 1, 3, 5, RESTART_PRIMITIVE_INDEX,
            3, 7, 5, RESTART_PRIMITIVE_INDEX, 3, 2, 6, RESTART_PRIMITIVE_INDEX, 3, 6, 7, RESTART_PRIMITIVE_INDEX
        };

        component->generatePointCloud();
        component->generateWireframe();
    }

    return component;
}

AlgGeom::Model3D::MatrixRenderInformation::MatrixRenderInformation()
{
    for (mat4& matrix : _matrix)
    {
        matrix = mat4(1.0f);
    }
}

void AlgGeom::Model3D::MatrixRenderInformation::undoMatrix(MatrixType type)
{
    if (_heapMatrices[type].empty())
    {
        _matrix[type] = mat4(1.0f);
    }
    else
    {
        _matrix[type] = *(--_heapMatrices[type].end());
        _heapMatrices[type].erase(--_heapMatrices[type].end());
    }
}

void AlgGeom::Model3D::Component::completeTopology()
{
    if (!this->_indices[VAO::IBO_TRIANGLE].empty() && this->_indices[VAO::IBO_LINE].empty())
    {
        this->generateWireframe();
    }

    if (!this->_indices[VAO::IBO_LINE].empty() && this->_indices[VAO::IBO_POINT].empty())
    {
        this->generatePointCloud();
    }
}

void AlgGeom::Model3D::Component::generateWireframe()
{
    std::unordered_map<int, std::unordered_set<int>>* segmentIncluded = new std::unordered_map<int, std::unordered_set<int>>;
    auto isIncluded = [&](int index1, int index2) -> bool
    {
        std::unordered_map<int, std::unordered_set<int>>::iterator it;

        if ((it = segmentIncluded->find(index1)) != segmentIncluded->end())
        {
            if (it->second.find(index2) != it->second.end())
            {
                return true;
            }
        }

        if ((it = segmentIncluded->find(index2)) != segmentIncluded->end())
        {
            if (it->second.find(index1) != it->second.end())
            {
                return true;
            }
        }

        return false;
    };

    const size_t numIndices = this->_indices[VAO::IBO_TRIANGLE].size();

    for (size_t i = 0; i < numIndices; i += 4)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            if (!isIncluded(this->_indices[VAO::IBO_TRIANGLE][i + j], this->_indices[VAO::IBO_TRIANGLE][(j + 1) % 3 + i]))
            {
                this->_indices[VAO::IBO_LINE].push_back(this->_indices[VAO::IBO_TRIANGLE][i + j]);
                this->_indices[VAO::IBO_LINE].push_back(this->_indices[VAO::IBO_TRIANGLE][(j + 1) % 3 + i]);
                this->_indices[VAO::IBO_LINE].push_back(RESTART_PRIMITIVE_INDEX);
            }
        }
    }
}

void AlgGeom::Model3D::Component::generatePointCloud()
{
    this->_indices[VAO::IBO_POINT].resize(this->_vertices.size());
    std::iota(this->_indices[VAO::IBO_POINT].begin(), this->_indices[VAO::IBO_POINT].end(), 0);
}
