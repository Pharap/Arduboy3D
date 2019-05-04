#include "Particle.h"
#include "FixedMath.h"

#include <stddef.h>

void ParticleSystem::Init()
{
	for (auto & particle : this->particles)
		particle.life = 0;
}

void ParticleSystem::Step()
{
	for (auto & particle : this->particles)
	{
		if (!particle.IsActive())
			continue;

		particle.velY += gravity;
		particle.life--;

		if (particle.x + particle.velX < -127 || particle.x + particle.velX > 127 || particle.y + particle.velY < -127 || !particle.IsActive())
			continue;

		if (particle.y + particle.velY >= 128)
		{
			particle.velY = particle.velX = 0;
			particle.y = 127;
		}

		particle.x += particle.velX;
		particle.y += particle.velY;

		//if(particle.y > 64)
		//{
		//	particle.y = 64;
		//}
	}
}

void ParticleSystem::Draw(int x, int halfScale)
{
	int scale = 2 * halfScale;
	int8_t horizon = GetHorizon(x);
	
	for (auto & particle : this->particles)
	{
		if (!particle.IsActive())
			continue;
	
		//int outX = x + ((particle.x * scale) >> 8);
		//int outY = HORIZON + ((particle.y * scale) >> 8);
		int outX = x + ((particle.x * scale) >> 8);
		int outY = horizon + ((particle.y * scale) >> 8);

		if((outX < 0) || (outX >= DISPLAY_WIDTH))
			continue;

		if((outY < 0) || (outY >= DISPLAY_HEIGHT))
			continue;
	
		if(halfScale < wBuffer[outX])
			continue;

		PutPixel(outX, outY, COLOUR_BLACK);
		PutPixel(outX + 1, outY, COLOUR_BLACK);
		PutPixel(outX + 1, outY + 1, COLOUR_BLACK);
		PutPixel(outX, outY + 1, COLOUR_BLACK);
	}
}

void ParticleSystem::Explode(uint8_t count)
{
	bool searchExhausted = false;
	
	size_t index = 0;
	while(true)
	{
		Particle & particle = particles[index];

		if (searchExhausted || !particle.IsActive())
		{
			particle.x = (Random() & 31) - 16;
			particle.y = (Random() & 31) - 16;

			particle.velX = (Random() & 31) - 16;
			particle.velY = (Random() & 31) - 25;

			particle.life = (Random() & 15) + 6;
			count--;
			
			if(count == 0)
				return;
		}

		if (index < (PARTICLES_PER_SYSTEM - 1))
		{
			++index;
		}
		else
		{
			searchExhausted = true;
			index = 0;
		}
	}
}
