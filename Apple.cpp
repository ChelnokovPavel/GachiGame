#include "Apple.h"
#include "Settings.h"

namespace ApplesGame {

	void InitApple(Apple& apple, Resource* resource)
	{
		apple.shape.setRadius(APPLE_SIZE / 2.f);
		apple.shape.setTexture(&resource->appleTexture);
		apple.shape.setOrigin(APPLE_SIZE / 2.f, APPLE_SIZE / 2.f);
	}

	void SetApplePosition(Apple& apple)
	{
		apple.shape.setPosition(apple.position.x, apple.position.y);
	}

}
