#pragma once
#include "core/uutObject.h"
#include "containers/uutString.h"

namespace uut
{
	class FileStream;

	class FileSystem : public Object
	{
	public:
		FileSystem();

		SharedPtr<FileStream> OpenRead(const String& path);
	};
}
