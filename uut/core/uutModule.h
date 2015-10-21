#pragma once
#include "uutObject.h"

namespace uut
{
	class Module : public Object
	{
		OBJECT(Module, Object)
	public:

	protected:

		virtual void OnRegister() {}
		virtual void OnUnregister() {}

		virtual void OnInit() {}
		virtual void OnDone() {}

		friend class Context;
	};
}