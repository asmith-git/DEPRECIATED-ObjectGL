#ifndef OBJECT_GL_WINDOW_INL
#define OBJECT_GL_WINDOW_INL

//Copyright 2015 Adam Smith
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.

// Contact :
// Email             : $objectgl_email
// GitHub repository : $objectgl_git

/*!
	\file Window.inl
	\brief
	\author Adam Smith
	\date 4th November 2015
*/

#include <stdexcept>
#include <cstdint>
#include <map>

namespace ObjectGL{


	static std::map<int, Window*> WINDOW_MAP;

	// Window

	Window::Window(Context& aContext):
		mContext(&aContext),
		mTitle(""),
		mID(0),
		mWidth(0),
		mHeight(0),
		mPosX(0),
		mPosY(0),
		mFullscreen(0),
		mHidden(0),
		mCreated(0)
	{}

	Window::Window(Window&& aOther) :
		mContext(aOther.mContext),
		mTitle(aOther.mTitle),
		mID(aOther.mID),
		mWidth(aOther.mWidth),
		mHeight(aOther.mHeight),
		mPosX(aOther.mPosX),
		mPosY(aOther.mPosY),
		mFullscreen(aOther.mFullscreen),
		mHidden(aOther.mHidden),
		mCreated(aOther.mCreated)
	{
		aOther.mCreated = 0;
	}

	Window::~Window(){
		if(IsCreated()) Destroy();
	}

	Window& Window::operator=(Window&& aOther){
		std::swap(mContext, aOther.mContext);
		std::swap(mTitle, aOther.mTitle);
		std::swap(mID, aOther.mID);
		std::swap(mWidth, aOther.mWidth);
		std::swap(mHeight, aOther.mHeight);
		std::swap(mPosX, aOther.mPosX);
		std::swap(mPosY, aOther.mPosY);
		std::swap(mFlags, aOther.mFlags);

		return *this;
	}

	const char* Window::GetTitle() const{
		return mTitle.c_str();
	}

	void Window::SetTitle(const char* const aTitle){
		mTitle = aTitle;
		const int prev = glutGetWindow();
		glutSetWindow(mID);
			glutSetWindowTitle(mTitle.c_str());
		glutSetWindow(prev);
	}

	void Window::Show(){
		if(! IsHidden()) throw std::runtime_error("ObjectGL::Window Window is not hidden");

		const int prev = glutGetWindow();
		glutSetWindow(mID);
			glutShowWindow();
		glutSetWindow(prev);

		mHidden = 1;
	}

	void Window::Hide(){
		if(IsHidden()) throw std::runtime_error("ObjectGL::Window Window is already hidden");

		const int prev = glutGetWindow();
		glutSetWindow(mID);
			glutHideWindow();
		glutSetWindow(prev);

		mHidden = 0;
	}

	bool Window::IsHidden() const{
		return mHidden;
	}


	GLuint Window::GetWidth() const{
		return mWidth;
	}

	GLuint Window::GetHeight() const{
		return mHeight;
	}

	void Window::Resize(const GLuint aWidth, const GLuint aHeight){
		mWidth = aWidth;
		mHeight = aHeight;

		const int prev = glutGetWindow();
		glutSetWindow(mID);
			glutReshapeWindow(aWidth, aHeight);
		glutSetWindow(prev);
	}

	GLuint Window::GetPositionX() const{
		return mPosX;
	}

	GLuint Window::GetPositionY() const{
		return mPosY;
	}

	void Window::SetPosition(const GLuint aX, const GLuint aY){
		mPosX = aX;
		mPosY = aY;

		const int prev = glutGetWindow();
		glutSetWindow(mID);
			glutPositionWindow(aX, aY);
		glutSetWindow(prev);
	}

	void Window::RedisplayFn(){
		Window& win = *WINDOW_MAP.find(glutGetWindow())->second;
		win.OnRedisplay();
	}

	void Window::EntryFn(int aState){
		Window& win = *WINDOW_MAP.find(glutGetWindow())->second;

		switch (aState)
		{
		case GLUT_ENTERED:
			win.OnMouseEnter();
			break;
		case GLUT_LEFT:
			win.OnMouseLeave();
			break;
		default:
			throw std::runtime_error("ObjectGL::Window Unknown state in EntryFn");
		}
	}

	void Window::KeyFn(unsigned char aKey, int aX, int aY){
		Window& win = *WINDOW_MAP.find(glutGetWindow())->second;
		win.OnKeyPress(aKey);
	}

	void Window::SpecialFn(int aKey, int aX, int aY){
		Window& win = *WINDOW_MAP.find(glutGetWindow())->second;
		win.OnKeyPress(aKey);
	}

	void Window::KeyUpFn(unsigned char aKey, int aX, int aY){
		Window& win = *WINDOW_MAP.find(glutGetWindow())->second;
		win.OnKeyRelease(aKey);
	}

	void Window::SpecialUpFn(int aKey, int aX, int aY){
		Window& win = *WINDOW_MAP.find(glutGetWindow())->second;
		win.OnKeyRelease(aKey);
	}

	void Window::MouseFn(int aButton, int aState, int aX, int aY){
		Window& win = *WINDOW_MAP.find(glutGetWindow())->second;

		switch (aState)
		{
		case GLUT_DOWN:
			win.OnMousePress(aButton);
			break;
		case GLUT_UP:
			win.OnMouseRelease(aButton);
			break;
		default:
			throw std::runtime_error("ObjectGL::Window Unknown state in MouseFn");
		}
	}

	void Window::MouseMoveFn(int aX, int aY){
		Window& win = *WINDOW_MAP.find(glutGetWindow())->second;
		win.OnMouseMove(aX, aY);
	}

	void Window::MouseWheelFn(int aWheel, int aDirection, int aX, int aY){
		Window& win = *WINDOW_MAP.find(glutGetWindow())->second;
		win.OnMouseWheelMove(aDirection);
	}

	void Window::Create(){
		if(IsCreated()) throw std::runtime_error("ObjectGL::Window Window has already been created");

		glutInitWindowPosition(mPosX, mPosY);
		glutInitWindowSize(mWidth, mHeight);
		glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

		mID = glutCreateWindow(mTitle.c_str());
		WINDOW_MAP.emplace(mID, this);
		mCreated = 1;

		const int prev = glutGetWindow();
		glutSetWindow(mID);
			glutDisplayFunc(&Window::RedisplayFn);
			glutEntryFunc(&Window::EntryFn);
			glutKeyboardFunc(&Window::KeyFn);
			glutSpecialFunc(&Window::SpecialFn);
			glutKeyboardUpFunc(&Window::KeyUpFn);
			glutSpecialUpFunc(&Window::SpecialUpFn);
			glutMouseFunc(&Window::MouseFn);
			glutMotionFunc(&Window::MouseMoveFn);
			glutPassiveMotionFunc(&Window::MouseMoveFn);
			glutMouseWheelFunc(&Window::MouseWheelFn);

			if(mFullscreen) glutFullScreen();
			if(mHidden) glutHideWindow();
		glutSetWindow(prev);

		ogl_LoadFunctions();
	}

	void Window::Destroy(){
		if(!IsCreated()) throw std::runtime_error("ObjectGL::Window Window has not been created");

		glutDestroyWindow(mID);
		WINDOW_MAP.erase(WINDOW_MAP.find(mID));
		mCreated = 0;
	}

	bool Window::IsCreated(){
		return mCreated;
	}

	Context& Window::GetContext(){
		return *mContext;
	}

	Window::Mode Window::GetMode() const{
		return mFullscreen ? Mode::FULLSCREEN : Mode::WINDOW;
	}

	void Window::SetMode(const Mode aMode){
		const int prev = glutGetWindow();
		glutSetWindow(mID);

		if(aMode == Mode::FULLSCREEN && ! mFullscreen){
			glutFullScreen();
		}else if (aMode == Mode::WINDOW && mFullscreen){
			glutFullScreen();
		}

		glutSetWindow(prev);
	}

	void Window::SwapBuffers(){
		const int prev = glutGetWindow();
		glutSetWindow(mID);
			glutSwapBuffers();
		glutSetWindow(prev);
	}


}

#endif
