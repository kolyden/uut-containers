#pragma once
#include "core/uutModule.h"

namespace uut
{
	class FileStream;

	class FileSystem : public Module
	{
		OBJECT(FileSystem, Module);
	public:
		SharedPtr<FileStream> OpenRead(const String& path);
	};
}
