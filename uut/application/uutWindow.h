#pragma once
#include "core/uutModule.h"
#include "core/uutPtr.h"
#include "containers/uutList.h"
#include "math/uutVector2.h"
#include <bitset>

namespace uut
{
	class EventListener;

	class Window : public Module
	{
		OBJECT(Window, Module)
	public:
		Window();

		bool Create(const Vector2i& size);
		bool MessagePool();

		void SetTitle(const String& title);
		const Vector2i& GetSize() const { return _size; }

		void AddEventListener(EventListener* listener);
		void RemoveEventListener(EventListener* listener);
		const List<EventListener*>& GetListeners() const { return _listeners; }

		void* GetHWND() const { return _handle; }

	protected:
		void* _handle;
		Vector2i _size;
		List<EventListener*> _listeners;
	};
}