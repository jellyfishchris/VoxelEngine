#ifndef RENDERER
#define RENDERER

#include <vector>

class Renderer
{
	public:
		//Renderer(void);
		//~Renderer(void);

		virtual void Initialize(int width, int height, unsigned int fpsCap, std::vector<unsigned int>& settings) = 0;
		virtual void Initialize(int width, int height, unsigned int fpsCap) = 0;
		const virtual void Update(const float& dt) = 0;
		const virtual void Draw(const float& dt) = 0;
		virtual void HandleEvents(float dt) = 0;
	protected:
		unsigned int m_width;
		unsigned int m_height;

		unsigned int m_fpsCap;
};

#endif
