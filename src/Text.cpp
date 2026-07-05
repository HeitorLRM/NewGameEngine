#include "Text.hpp"

#include "Camera2D.hpp"
#include "Game.hpp"
#include "RenderPass.hpp"
#include "SDL_AppIO.hpp"
#include "Transform2D.hpp"

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <array>
#include <cmath>
#include <stdexcept>

using namespace engine;
using std::runtime_error;
using std::string;
using std::array;

const std::string& Text::getResourceType() const {
	static const string RES_NAME = "Text";
	return RES_NAME;
}

Text::~Text() {
	if (font) {
		TTF_CloseFont(font);
		font = nullptr;
	}
	if (texture) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void Text::loadFont(const string& path, float pointSize) {
	if (font) TTF_CloseFont(font);
	font = TTF_OpenFont(path.c_str(), pointSize);
	if (!font)
		throw runtime_error(string("could not load font '") + path + "'.");
	dirty = true;
}

void Text::setText(const string& t) {
	text = t;
	dirty = true;
}

void Text::setColor(const Color& c) {
	modulation = c;
	dirty = true;
}

void Text::rebuildTexture() {
	if (texture) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
	if (!font || text.empty())
		return;

	// Kinda sus que ele usa modulation aqui e ali embaixo tambem...
	//  talvez vale a pena investigar depois, mas por enquanto tanto faz pra o branco eu acho
	SDL_Color sdl_color{
		(Uint8)(modulation.r * 255.0f),
		(Uint8)(modulation.g * 255.0f),
		(Uint8)(modulation.b * 255.0f),
		(Uint8)(modulation.a * 255.0f)
	};

	SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), 0, sdl_color);
	if (!surface)
		throw runtime_error("could not render text.");

	texture = SDL_CreateTextureFromSurface(AppIO::SDL::renderer, surface);
	SDL_DestroySurface(surface);

	if (!texture)
		throw runtime_error("could not create text texture.");

	SDL_GetTextureSize(texture, &dimensions.x, &dimensions.y);
}

void Text::preRender() {
	auto pass = Game::getRenderPass();
	if (!pass || !pass->active_camera2D) return;

	pass->queue(this);

	Object2D::preRender();
}

void Text::render() {
	Object2D::render();

	if (dirty) {
		rebuildTexture();
		dirty = false;
	}
	if (!texture) return;

	const auto camera = Game::getRenderPass()->active_camera2D;
	Transform2D viewTransform = camera->getInverseGlobal();
	viewTransform.translate(camera->feed->screen_area.dimensions / 2);

	const Vec2 D = dimensions;
	const Vec2 P = pivot * D;
	array<Vec2, 4> vertices {
		Vec2{0.0, 0.0} - P,
		Vec2{D.x, 0.0} - P,
		Vec2{0.0, D.y} - P,
		Vec2{D.x, D.y} - P
	};

	const auto globalTransform = getGlobalTransform();
	for (auto& vertex : vertices)
		vertex = globalTransform * vertex;
	for (auto& vertex : vertices)
		vertex = viewTransform * vertex;

	// Text was blurry without rounding to integers
	for (auto& vertex : vertices) {
		vertex.x = std::floor(vertex.x);
		vertex.y = std::floor(vertex.y);
	}

	const array<Vec2, 4> uvs {
		Vec2{0.0, 0.0},
		Vec2{1.0, 0.0},
		Vec2{0.0, 1.0},
		Vec2{1.0, 1.0}
	};

	SDL_Vertex vertices_sdl[4];
	for (unsigned i = 0; i < 4; i++) {
		vertices_sdl[i] = {
			vertices[i].x, vertices[i].y,
			modulation.r, modulation.g, modulation.b, modulation.a,
			uvs[i].x, uvs[i].y
		};
	}
	const int indices[6] = {0, 1, 2, 2, 1, 3};

	SDL_RenderGeometry(
		AppIO::SDL::renderer,
		texture,
		vertices_sdl,
		4,
		indices,
		6
	);
}
