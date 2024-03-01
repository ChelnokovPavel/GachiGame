#include "Rock.h"
#include "Settings.h"
#include "Resource.h"
#include "Math.h"

namespace ApplesGame {

	void InitRock(Rock& rock, Resource* resource)
	{
		// Shape с текусторой для визуала
		rock.mainShape.setRadius(ROCK_SIZE / 2.f);
		rock.mainShape.setTexture(&resource->rockTexture);
		rock.mainShape.setOrigin(ROCK_SIZE / 2.f, ROCK_SIZE / 2.f);


		// Shape, который не будет отрисовываться для проверки коллизий
		rock.internalShape.setRadius((ROCK_SIZE * 0.90f) / 2.f);
		rock.internalShape.setOrigin((ROCK_SIZE * 0.90f) / 2.f, (ROCK_SIZE * 0.90f) / 2.f);
	}

	void SetRockPosition(Rock& rock)
	{
		rock.mainShape.setPosition(rock.position.x, rock.position.y);
		rock.internalShape.setPosition(rock.position.x, rock.position.y);
	}

}
