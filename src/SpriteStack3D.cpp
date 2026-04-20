#include "SpriteStack3D.hpp"
#include "Camera3D.hpp"

using namespace engine;

using std::array;

void SpriteStack3D::render() {
	Object3D::render();

	if (!texture.get()) return;

	const auto& camera = Game::getRenderPass()->active_camera3D;
	const Transform3D to_world = getGlobalTransform();
	const Transform3D to_camera = camera->getInverseGlobal();
	const Transform3D camera_global = camera->getGlobalTransform();
	const Transform3D to_clip = Transform3D{camera->getProjectionMatrix()};
	const Vec2 D = getDimensions() * pixel_size;
	const Vec2 P = pivot * pixel_size;
	const float L = 0.0 - P.x;
	const float R = D.x - P.x;
	const float B = 0.0 - P.y;
	const float T = D.y - P.y;

	bool forwards = (to_camera*to_world).basis.k.z > 0;
	unsigned layer_count = stack.size();
	for (int render_i=0; render_i<layer_count; render_i++) {
		int layer_i = forwards ? render_i : layer_count-render_i-1;
		unsigned frame = stack[layer_i];
		// Model space
		float Z = separation * layer_i;
		array<Vec3,4> vertices3D {
			Vec3{L, T, Z}, // Top Left
			Vec3{R, T, Z}, // Top Right
			Vec3{L, B, Z}, // Bottom Left
			Vec3{R, B, Z}, // Bottom Right
		};
		
		for (auto& vertex : vertices3D) {
			// World space
			if (is_billboard) vertex = 
				vertex.x*camera_global.basis.i + 
				vertex.y*camera_global.basis.j + 
				to_world.position;
			else
				vertex = to_world * vertex;

			// Camera space
			vertex = to_camera * vertex;

			// Clip space
			Vec4 v_clip = to_clip.matrix * Vec4{vertex.x, vertex.y, vertex.z, 1};
			
			// Perspective
			vertex = v_clip.xyz / v_clip.w;
			// Note: NDC space maps clip boundaries to [-1, 1] in x,y,z

			// Z-culling
			if (vertex.z < -1.0)
				continue;
		} 
		// Screen space
		const Vec2 feed_offset = camera->feed->screen_area.dimensions/2;
		array<Vec2,4> vertices2D;
		for (int i=0; i<4; i++) {
			vertices2D[i].x = (1.0f + vertices3D[i].x) * feed_offset.x;
			vertices2D[i].y = (1.0f - vertices3D[i].y) * feed_offset.y;
		}

		texture->renderQuad(vertices2D, getFrameUVs(frame));
	}
}
