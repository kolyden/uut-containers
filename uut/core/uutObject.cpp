#include "uutObject.h"
#include "uutCore.h"

namespace uut
{
	Core* Object::GetCore()
	{
		return Core::GetMain();
	}

	Module* Object::GetModule(const HashString& type)
	{
		return GetCore()->GetModule(type);
	}
}