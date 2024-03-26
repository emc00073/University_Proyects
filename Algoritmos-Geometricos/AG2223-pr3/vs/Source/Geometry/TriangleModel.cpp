#include "stdafx.h"
#include "TriangleModel.h"


TriangleModel::TriangleModel(const std::string& pathfile)
{
    std::string binaryFile = pathfile.substr(0, pathfile.find_last_of('.')) + BINARY_EXTENSION;

    if (std::filesystem::exists(binaryFile))
    {
        this->loadModelBinaryFile(binaryFile);
    }
    else
    {
        const aiScene* scene = _assimpImporter.ReadFile(pathfile, aiProcess_JoinIdenticalVertices | aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP::" << _assimpImporter.GetErrorString() << std::endl;
            return;
        }

        std::string shortName = scene->GetShortFilename(pathfile.c_str());
        std::string folder = pathfile.substr(0, pathfile.length() - shortName.length());

        this->processNode(scene->mRootNode, scene, folder);
        this->writeBinaryFile(binaryFile);
    }
}

TriangleModel::~TriangleModel() 
{
}

PointCloud3d TriangleModel::getCloud()
{
    return PointCloud3d(_vertices);
}

Triangle3d TriangleModel::getFace(unsigned index) 
{
    if (index > this->numTriangles()) 
        return Triangle3d();  
    
    Vect3d a = _vertices[_indices[index * 3]];
    Vect3d b = _vertices[_indices[index * 3 + 1]];
    Vect3d c = _vertices[_indices[index * 3 + 2]];
    
    return Triangle3d(a, b, c);
}

std::vector<Triangle3d> TriangleModel::getFaces(){
    
    std::vector<Triangle3d> result;
    
    for (int index = 0; index < this->numTriangles(); index++)
    {
        result.push_back(getFace(index));
    }

    return result;
}

size_t TriangleModel::numTriangles()
{
    return _indices.size() / 3;
}

AABB TriangleModel::getAABB()
{
    double min_x, min_y, min_z, max_x, max_y, max_z;
    if (_vertices.size() > 0)
    {
        min_x = max_x = _vertices[0].getX();
        min_y = max_y = _vertices[0].getY();
        min_z = max_z = _vertices[0].getZ();

        for (auto& vertex : _vertices)
        {
            min_x = std::min(min_x, vertex.getX());
            max_x = std::max(max_x, vertex.getX());
            min_y = std::min(min_y, vertex.getY());
            max_y = std::max(max_y, vertex.getY());
            min_z = std::min(min_z, vertex.getZ());
            max_z = std::max(max_z, vertex.getZ());
		}

        Vect3d min(min_x, min_y, min_z);
        Vect3d max(max_x, max_y, max_z);

		return AABB(min, max);
	}
    return AABB();
}

bool TriangleModel::rayTraversalExh(Ray3d& r, Vect3d& p, Triangle3d& t)
{
    float distance = std::numeric_limits<float>::max();
    bool intersected = false;
    
    for (int i = 0; i < this->numTriangles(); i++)
    {   
        Vect3d intersection;
		Triangle3d triangle = this->getFace(i);
        if (triangle.ray_tri(r, intersection))
        {
            intersected = true;
            float d = r.getOrigin().distance(intersection);
            if (d < distance)
            {
                distance = d;
                t = triangle;
                p = intersection;
            }
		}
	}

	return intersected;
}

bool TriangleModel::rayTraversalExh(Ray3d& r, std::vector<Vect3d> &p, std::vector<Triangle3d> &t)
{
    float distance = std::numeric_limits<float>::max();
    bool intersected = false;

    for (int i = 0; i < this->numTriangles(); i++)
    {
        Vect3d intersection;
        Triangle3d triangle = this->getFace(i);
        if (triangle.ray_tri(r, intersection))
        {
            intersected = true;

            p.push_back(intersection);
            t.push_back(triangle);
        }
    }

    return intersected;
}

bool TriangleModel::pointIntoMesh(Vect3d& v)
{
    Vect3d rayDirection = Vect3d((float)(rand() % 2 - 1), (float)(rand() % 2 - 1), (float)(rand() % 2 - 1));
    Vect3d rayDirection2 = Vect3d((float)(rand() % 2 - 1), (float)(rand() % 2 - 1), (float)(rand() % 2 - 1));
    Vect3d rayDirection3 = Vect3d((float)(rand() % 2 - 1), (float)(rand() % 2 - 1), (float)(rand() % 2 - 1));

    Ray3d ray(v, rayDirection);
    Ray3d ray2(v, rayDirection2);
    Ray3d ray3(v, rayDirection3);

    std::vector<Vect3d> p, q, r;
    std::vector<Triangle3d> t, u, w;

    this->rayTraversalExh(ray, p, t);
    this->rayTraversalExh(ray2, q, u);

    if (p.size() % 2 == 0 && q.size() % 2 == 0) {
        return false;
    }else{
        if (p.size() % 2 != 0 && q.size() % 2 != 0) {
            return true;
        }
        else {
            this->rayTraversalExh(ray3, r, w);
            printf("Lanzado tercer rayo");
            if (r.size() % 2 == 0)
                return false;
            else
                return true;
        }
    }
}

 // Protected methods

void TriangleModel::loadModelBinaryFile(const std::string& path)
{
    std::ifstream fin(path, std::ios::in | std::ios::binary);
    if (!fin.is_open())
    {
        std::cout << "Failed to open the binary file " << path << "!" << std::endl;
        return;
    }

    size_t numVertices, numTextCoords, numIndices;

    fin.read((char*)&numVertices, sizeof(size_t));
    fin.read((char*)&numTextCoords, sizeof(size_t));
    this->_vertices.resize(numVertices);
    this->_normals.resize(numVertices);
    this->_textCoordinates.resize(numTextCoords);

    fin.read((char*)this->_vertices.data(), sizeof(Vect3d) * numVertices);
    fin.read((char*)this->_normals.data(), sizeof(Vect3d) * numVertices);
    if (numTextCoords)
        fin.read((char*)this->_textCoordinates.data(), sizeof(Vect2d) * numVertices);

    fin.read((char*)&numIndices, sizeof(size_t));
    if (numIndices)
    {
        this->_indices.resize(numIndices);
        fin.read((char*)this->_indices.data(), sizeof(GLuint) * numIndices);
    }
}

void TriangleModel::processMesh(aiMesh* mesh, const aiScene* scene, const std::string& folder)
{
    // Vertices
    unsigned baseIndex = this->_vertices.size();
    int numVertices = static_cast<int>(mesh->mNumVertices);

    for (int i = 0; i < numVertices; i++)
    {
        this->_vertices.push_back(Vect3d(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z));
        this->_normals.push_back(Vect3d(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z));
        if (mesh->mTextureCoords[0]) this->_textCoordinates.push_back(Vect2d(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y));
    }

    // Indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            this->_indices.push_back(face.mIndices[j] + baseIndex);
    }
}

void TriangleModel::processNode(aiNode* node, const aiScene* scene, const std::string& folder)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        this->processMesh(mesh, scene, folder);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        this->processNode(node->mChildren[i], scene, folder);
    }
}

void TriangleModel::writeBinaryFile(const std::string& path)
{
    std::ofstream fout(path, std::ios::out | std::ios::binary);
    if (!fout.is_open())
    {
        std::cout << "Failed to write the binary file!" << std::endl;
    }

    size_t numVertices = this->_vertices.size(), numTextCoordinates = this->_textCoordinates.size();

    fout.write((char*)&numVertices, sizeof(size_t));
    fout.write((char*)&numTextCoordinates, sizeof(size_t));
    fout.write((char*)this->_vertices.data(), numVertices * sizeof(Vect3d));
    fout.write((char*)this->_normals.data(), numVertices * sizeof(Vect3d));
    if (numTextCoordinates)
        fout.write((char*)this->_textCoordinates.data(), numTextCoordinates * sizeof(Vect2d));

    size_t numIndices = this->_indices.size();
    fout.write((char*)&numIndices, sizeof(size_t));
    if (numIndices)
        fout.write((char*)this->_indices.data(), numIndices * sizeof(GLuint));

    fout.close();
}
