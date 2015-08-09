#include "blitAlpha.hpp"
#include <helpful.hpp>
using namespace std;

Shader_blitAlpha::Shader_blitAlpha()
{
	unsigned int a;
	a = glGetError();
	if(a!=0)cout << "Shaderbl setup error3: " << a << endl;
	
	const string block =
"";

	
	const char* vsText = textFileRead("shaders/blitAlpha/shader.vert");
	const char* fsText = textFileRead("shaders/blitAlpha/shader.frag");
	
	
	string vsource = ShaderManager::getVersion() + "\n";
	string fsource = ShaderManager::getVersion() + "\n";
	

	
	vsource += block + "\n\n";
	fsource += block + "\n\n";
	
	vsource += vsText;
	fsource += fsText;
	
	a = glGetError();
	if(a!=0)cout << "Shaderbl setup error2: " << a << endl;

	/*cout << "blitTexture gregmvmwmwemjiomioweiocropcjopqweopr\n\n\n\n" << endl;
	cout << vsource << endl;
	cout << "blitTexture pregmvmwmwemjiomioweiocropcjopqweopr\n\n\n\n" << endl;
	cout << fsource << endl;
	cout << "blitTexture gregmvmwmwemjiomioweiocropcjopqweopr\n\n\n\n" << endl;*/
	
	ofstream log;
	getShaderLog(log, "blitAlpha");
	
	array<GLuint, 3> out = loadShaders(log,vsource,fsource);
	
	shader_id = out[0];
	shader_vp = out[1];
	shader_fp = out[2];
	a = glGetError();
	if(a!=0)cout << "Shaderbl setup error12: " << a << endl;
	glBindAttribLocation(shader_id, 0, "in_Vertex");
	glBindAttribLocation(shader_id, 1, "in_UV");
	glBindFragDataLocation(shader_id, 0, "out_Scene");
	
	a = glGetError();
	if(a!=0)cout << "Shaderbl setup error111: " << a << endl;
	
	glAttachShader(shader_id, shader_fp);
	glAttachShader(shader_id, shader_vp);
	glLinkProgram(shader_id);
	
	glUseProgram(shader_id);
	
	a = glGetError();
	if(a!=0)cout << "Shaderbl setup error11: " << a << endl;
	GLuint ct = glGetUniformLocation(shader_id, "colourTexture");
	
	glUniform1i(ct, 0);

	
	uniforms.colour = glGetUniformLocation(shader_id, "colour");
	glUniform3f(uniforms.colour, 1, 1, 1);
	
	uniforms.projectionMatrix = glGetUniformLocation(shader_id, "projectionMatrix");
	
	a = glGetError();
	if(a!=0)cout << "Shaderbl setup error1: " << a << endl;

	
	a = glGetError();
	if(a!=0)cout << "Shaderbl setup error: " << a << endl;
	
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, vbo);
	glGenBuffers(1, vbo+1);
	
	cout << "BUFFER: " << vbo[0] << " " << vbo[1] << endl;
	
	glBindVertexArray(vao);
	
	const float v[] = {
			-1.f, -1.f,
			1.f, -1.f,
			1.f, 1.f,
			-1.f, -1.f,
			1.f, 1.f,
			-1.f, 1.f
	};
	
	const float u[] = {
			0.f, 0.f,
			1.f, 0.f,
			1.f, 1.f,
			0.f, 0.f,
			1.f, 1.f,
			0.f, 1.f
	};
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 6, v, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * 6, u, GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindVertexArray(0);

	a = glGetError();
	if(a!=0)cout << "alphaShaderbl setup error: " << a << endl;
	
}

