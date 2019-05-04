#include "Particle.h"
#include "FixedMath.h"

#include <stddef.h>

// void ParticleSystem::Init()
// {
	// for (auto & particle : this->particles)
		// particle.life = 0;
// }

// void ParticleSystem::Step()
// {
	// for (auto & particle : this->particles)
	// {
		// if(particle.life < 2)
		// {
			// particle.life = 0;
			// continue;
		// }

		// particle.velY += gravity;

		// const auto destinationX = (particle.x + particle.velX);

		// if ((destinationX < -127) || (destinationX > 127))
			// continue;
		
		// const auto destinationY = (particle.y + particle.velY);

		// if (destinationY < -127)
			// continue;

		// if (destinationY < 128)
		// {
			// particle.x = destinationX;
			// particle.y = destinationY;
		// }
		// else
		// {
			// particle.velY = 0;
			// particle.velX = 0;
			// particle.y = 127;
		// }
	// }
// }

// void ParticleSystem::Draw(int x, int halfScale) const
// {
	// const int scale = (halfScale * 2);
	// const int8_t horizon = GetHorizon(x);
	
	// for (const auto & particle : this->particles)
	// {
		// if (!particle.IsActive())
			// continue;
	
		// const int outX = (x + ((particle.x * scale) >> 8));
		// const int outY = (horizon + ((particle.y * scale) >> 8));

		// if((outX < 0) || (outX >= DISPLAY_WIDTH))
			// continue;

		// if((outY < 0) || (outY >= DISPLAY_HEIGHT))
			// continue;
	
		// if(halfScale < wBuffer[outX])
			// continue;

		// PutPixel(outX, outY, COLOUR_BLACK);
		// PutPixel(outX + 1, outY, COLOUR_BLACK);
		// PutPixel(outX + 1, outY + 1, COLOUR_BLACK);
		// PutPixel(outX, outY + 1, COLOUR_BLACK);
	// }
// }

// void ParticleSystem::Explode(uint8_t count)
// {
	// bool searchExhausted = false;
	
	// size_t index = 0;
	// while(true)
	// {
		// Particle & particle = particles[index];

		// if (searchExhausted || !particle.IsActive())
		// {
			// particle.x = ((Random() % 32) - 16);
			// particle.y = ((Random() % 32) - 16);

			// particle.velX = ((Random() % 32) - 16);
			// particle.velY = ((Random() % 32) - 25);

			// particle.life = ((Random() % 16) + 6);
			// --count;
			
			// if(count == 0)
				// return;
		// }

		// if (index < (PARTICLES_PER_SYSTEM - 1))
		// {
			// ++index;
		// }
		// else
		// {
			// searchExhausted = true;
			// index = 0;
		// }
	// }
// }
