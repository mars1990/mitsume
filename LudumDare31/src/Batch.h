#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

struct Vertex
{
	glm::vec3 _position;
	glm::vec4 _color;
	glm::vec2 _texture;

	Vertex(glm::vec3 position, glm::vec4 color, glm::vec2 texture = glm::vec2()) :
		_position(position), _color(color), _texture(texture) {}
};

struct BatchConfig
{
	GLuint _renderType;
	GLint _priority;
	GLuint _textureId;
	glm::mat4 _transformMatrix;

	BatchConfig(GLuint renderType, GLint priority, GLuint textureId) :
		_renderType(renderType), _priority(priority), _textureId(textureId) {}

	bool operator==(const BatchConfig& other) const
	{
		if (_renderType != other._renderType ||
			_priority != other._priority ||
			_textureId != other._textureId ||
			_transformMatrix != other._transformMatrix)
		{
			return false;
		}

		return true;
	}

	bool operator!=(const BatchConfig& other) const
	{
		return !(*this == other);
	}
};

class CBatch final
{
public:
	CBatch(GLuint maxVertices);
	~CBatch();

	bool matchesConfig(const BatchConfig& config) const;
	bool isEmpty() const;
	bool isEnoughRoom(GLuint numVertices);
	CBatch* getFuller(CBatch* batch);
	GLint getPriority() const;

	void add(const std::vector<Vertex>& vertices, const BatchConfig& config);
	void add(const std::vector<Vertex>& vertices);
	void render();

private:
	CBatch(const CBatch& batch);
	CBatch& operator=(const CBatch& batch);

	void cleanUp();

	GLuint _maxNumVertices;
	GLuint _numUsedVertices;
	GLuint _vao;
	GLuint _vbo;
	BatchConfig _config;
	Vertex _lastVertex;
};

struct CompareBatch
{
	bool operator() (const CBatch* batchA, const CBatch* batchB) const
	{
		return (batchA->getPriority() > batchB->getPriority());
	}
};