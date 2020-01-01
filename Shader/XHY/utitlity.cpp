#include "utitlity.h"

#include"../GL//gl_core_4_3.h"

__XHY_BEGIN

void PrintDeviceInfo()
{
	int loaded = ogl_LoadFunctions();
	if (loaded == ogl_LOAD_FAILED)
		printf("Load gl failed!\n");
	else
	{
		int num_failed = loaded - ogl_LOAD_SUCCEEDED;
		printf("Number of functions failed to load: %d\n", num_failed);
	}

	const GLubyte* render = glGetString(GL_RENDERER);
	const GLubyte* vendor = glGetString(GL_VENDOR);
	const GLubyte* version = glGetString(GL_VERSION);
	const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	printf("%s\n%s\n%s\n%s\n", render, vendor, version, glslVersion);
	/*GLint nExtensions;
	glGetIntegerv(GL_NUM_EXTENSIONS, &nExtensions);
	for (int i = 0; i < nExtensions; ++i)
		printf("%s\n", glGetStringi(GL_EXTENSIONS, i));*/
}

__XHY_END
