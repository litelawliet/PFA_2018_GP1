#include <stdafx.h>
#include <Rendering/Resources/Loaders/MeshLoader.h>

Rendering::Resources::Mesh* Rendering::Resources::Loaders::MeshLoader::MakeCube() noexcept
{
	const std::vector<Geometry::Vertex> vertices
	{
		{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {-1.0f, +0.0f, +0.0f}},
		{{+0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}, {-1.0f, +1.0f, +0.0f}},
		{{+0.5f, +0.5f, -0.5f}, {1.0f, 1.0f}, {-1.0f, +1.0f, +1.0f}},
		{{+0.5f, +0.5f, -0.5f}, {1.0f, 1.0f}, {-1.0f, +1.0f, +1.0f}},
		{{-0.5f, +0.5f, -0.5f}, {0.0f, 1.0f}, {-1.0f, +0.0f, +1.0f}},
		{{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}, {-1.0f, +0.0f, +0.0f}},

		{{-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}, {+1.0f, +0.0f, +0.0f}},
		{{+0.5f, -0.5f, +0.5f}, {1.0f, 0.0f}, {+1.0f, +1.0f, +0.0f}},
		{{+0.5f, +0.5f, +0.5f}, {1.0f, 1.0f}, {+1.0f, +1.0f, +1.0f}},
		{{+0.5f, +0.5f, +0.5f}, {1.0f, 1.0f}, {+1.0f, +1.0f, +1.0f}},
		{{-0.5f, +0.5f, +0.5f}, {0.0f, 1.0f}, {+1.0f, +0.0f, +1.0f}},
		{{-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}, {+1.0f, +0.0f, +0.0f}},

		{{-0.5f, +0.5f, +0.5f}, {1.0f, 0.0f}, {+0.0f, +1.0f, +0.0f}},
		{{-0.5f, +0.5f, -0.5f}, {1.0f, 1.0f}, {+0.0f, +1.0f, +1.0f}},
		{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, {+0.0f, +0.0f, +1.0f}},
		{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, {+0.0f, +0.0f, +1.0f}},
		{{-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}, {+0.0f, +0.0f, +0.0f}},
		{{-0.5f, +0.5f, +0.5f}, {1.0f, 0.0f}, {+0.0f, +1.0f, +0.0f}},

		{{+0.5f, +0.5f, +0.5f}, {1.0f, 0.0f}, {+0.0f, +1.0f, +0.0f}},
		{{+0.5f, +0.5f, -0.5f}, {1.0f, 1.0f}, {+0.0f, +1.0f, +1.0f}},
		{{+0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, {+0.0f, +0.0f, +1.0f}},
		{{+0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, {+0.0f, +0.0f, +1.0f}},
		{{+0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}, {+0.0f, +0.0f, +0.0f}},
		{{+0.5f, +0.5f, +0.5f}, {1.0f, 0.0f}, {+0.0f, +1.0f, +0.0f}},

		{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, {+0.0f, +0.0f, +1.0f}},
		{{+0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}, {+0.0f, +1.0f, +1.0f}},
		{{+0.5f, -0.5f, +0.5f}, {1.0f, 0.0f}, {+0.0f, +1.0f, +0.0f}},
		{{+0.5f, -0.5f, +0.5f}, {1.0f, 0.0f}, {+0.0f, +1.0f, +0.0f}},
		{{-0.5f, -0.5f, +0.5f}, {0.0f, 0.0f}, {+0.0f, +0.0f, +0.0f}},
		{{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}, {+0.0f, +0.0f, +1.0f}},

		{{-0.5f, +0.5f, -0.5f}, {0.0f, 1.0f}, {+0.0f, +0.0f, +1.0f}},
		{{+0.5f, +0.5f, -0.5f}, {1.0f, 1.0f}, {+0.0f, +1.0f, +1.0f}},
		{{+0.5f, +0.5f, +0.5f}, {1.0f, 0.0f}, {+0.0f, +1.0f, +0.0f}},
		{{+0.5f, +0.5f, +0.5f}, {1.0f, 0.0f}, {+0.0f, +1.0f, +0.0f}},
		{{-0.5f, +0.5f, +0.5f}, {0.0f, 0.0f}, {+0.0f, +0.0f, +0.0f}},
		{{-0.5f, +0.5f, -0.5f}, {0.0f, 1.0f}, {+0.0f, +0.0f, +1.0f}},
	};

	const std::vector<uint32_t> indices
	{
		0, 1, 2, 3, 4, 5,
		6, 7, 8, 9, 10, 11,
		12, 13, 14, 15, 16, 17,
		18, 19, 20, 21, 22, 23,
		24, 25, 26, 27, 28, 29,
		30, 31, 32, 33, 34, 35
	};

	return new Mesh(vertices, indices);
}

bool Rendering::Resources::Loaders::MeshLoader::Destroy(Mesh*& p_meshInstanceReference) noexcept
{
	if (p_meshInstanceReference != nullptr)
	{
		delete p_meshInstanceReference;
		p_meshInstanceReference = nullptr;

		return true;
	}
	return false;
}
