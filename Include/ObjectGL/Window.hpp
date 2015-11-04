#ifndef OBJECT_GL_WINDOW_HPP
#define OBJECT_GL_WINDOW_HPP

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

#include <string>
#include "Context.hpp"

/*!
	\file Window.hpp
	\brief
	\author Adam Smith
	\date 4th November 2015
*/

namespace ObjectGL{
	
	/*!
		\brief
		\author Adam Smith
		\date 4th November 2015
		\version 1.0
	*/
	class Window{
	public:
		enum class Mode{
			WINDOW,
			FULLSCREEN
		};
	private:
		Context* mContext;
		std::string mTitle;
		int mID;
		GLushort mWidth;
		GLushort mHeight;
		GLushort mPosX;
		GLushort mPosY;
		union{
			struct{
				GLubyte mFullscreen : 1;
				GLubyte mHidden : 1;
				GLubyte mCreated : 1;
			};
			GLubyte mFlags;
		};
	private:
		Window(const Window&);
		Window& operator=(const Window&);
	private:
		static void RedisplayFn();
		static void EntryFn(int);
		static void KeyFn(unsigned char, int, int);
		static void SpecialFn(int, int, int);
		static void KeyUpFn(unsigned char, int, int);
		static void SpecialUpFn(int, int, int);
		static void MouseFn(int, int, int, int);
		static void MouseMoveFn(int, int);
		static void MouseWheelFn(int, int, int, int);
	protected:
		virtual void OnMouseEnter() = 0;
		virtual void OnMouseLeave() = 0;
		virtual void OnRedisplay() = 0;
		virtual void OnKeyPress(const int) = 0;
		virtual void OnKeyRelease(const int) = 0;
		virtual void OnMousePress(const int) = 0;
		virtual void OnMouseRelease(const int) = 0;
		virtual void OnMouseMove(const GLuint, const GLuint) = 0;
		virtual void OnMouseWheelMove(int) = 0;
	public:
		Window(Context& aContext);
		Window(Window&&);
		virtual ~Window();

		Window& operator=(Window&&);

		void Show();
		void Hide();
		bool IsHidden() const;

		const char* GetTitle() const;
		void SetTitle(const char* const);

		GLuint GetWidth() const;
		GLuint GetHeight() const;
		void Resize(const GLuint, const GLuint);

		GLuint GetPositionX() const;
		GLuint GetPositionY() const;
		void SetPosition(const GLuint, const GLuint);

		void Create();
		void Destroy();
		bool IsCreated();

		Mode GetMode() const;
		void SetMode(const Mode);

		void SwapBuffers();

		Context& GetContext();
	};

}

#include "Window.inl"

#endif
