#include "uutObject.h"
#include "uutContext.h"

namespace uut
{
	Context* Object::GetCore()
	{
		return Context::GetMain();
	}

	Module* Object::GetModule(const HashString& type)
	{
		return GetCore()->GetModule(type);
	}
}