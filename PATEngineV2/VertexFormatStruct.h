#pragma once
#include "Dependencies\GLM\glm.hpp"

struct VertexFormtat {
	glm::vec3 position;
	glm::vec4 color;
	VertexFormtat(const glm::vec3 &pos, const glm::vec4 &col) {
		position = pos;
		color = col;
	}
};
