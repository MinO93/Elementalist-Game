#ifndef __MEMORY_LEAK_H__
#define __MEMORY_LEAK_H__

	#ifdef _DEBUG

			#include <stdlib.h>
			#include <crtdbg.h>

			#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

	#endif
#endif