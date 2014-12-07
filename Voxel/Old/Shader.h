#ifndef SHADER_H
#define SHADER_H


class Shader
{
public:
	Shader(void);
	~Shader(void);
protected:
	int        program_type;  //!< The program type. 1=Vertex Program, 2=Fragment Program, 3=Geometry Progam, 0=none
	GLuint     ShaderObject;  //!< Shader Object
	GLcharARB* compiler_log;
	bool       is_compiled;   //!< true if compiled
};

#endif
