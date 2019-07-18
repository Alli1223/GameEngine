// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// ImGui library
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <SDL_image.h>
#include <SDL.h>


// Graphics libraries
#include <GL/glew.h>
#include <GL/GL.h>
#include <ft2build.h>
#include FT_FREETYPE_H 


#include <gtx\transform.hpp>
#include <gtc\type_ptr.hpp>
#include <gtc\matrix_transform.hpp>


// Additional headers
#include <iostream>
#include <memory>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <set>
#include <list>
#include <math.h>
#include <fstream>
#include <thread>
#include <numeric>
#include <random>
#include <glm.hpp>
#include <unordered_map>

#define PI 3.14159265
#define GL3_PROTOTYPES 1


// Networking headers
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/write.hpp>
#include <boost/bind.hpp>
using boost::asio::ip::tcp;

//SDL TTF for writing to screen
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// Box2D
//#include <Box2D/Box2D.h>

// json parser
#include "json.hpp"
using json = nlohmann::json;
using namespace glm;
