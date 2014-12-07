#ifndef INPUTEVENT_H
#define INPUTEVENT_H

#include <cstdint>

class InputEvent
{
	public:
		InputEvent(unsigned char type, unsigned int key, uint16_t mousex, uint16_t mousey) : m_type(type), m_key(key), m_mousex(mousex), m_mousey(mousey) {};

		unsigned char GetType(){return m_type;}
		unsigned int GetKey(){return m_key;}
		uint16_t GetMouseX(){return m_mousex;}
		uint16_t GetMouseY(){return m_mousey;}
	private:
		unsigned char m_type;
		unsigned int m_key;
		uint16_t m_mousex;
		uint16_t m_mousey;
};

#endif

