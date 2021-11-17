#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

using namespace std;

#define DEBUG_OPENGL true
//#define TRACE

#define CHECK_OPENGL_ERROR(function) { GLint err; if(err = glGetError()) cout << __FILE__ << ":" << __LINE__ << ", Failed " << #function << ", " << gluErrorString(err) << endl; }

#endif