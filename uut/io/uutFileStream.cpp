#include "uutFileStream.h"

namespace uut
{
	FileStream::FileStream()
		: _handle(INVALID_HANDLE_VALUE)
	{
	}

	FileStream::~FileStream()
	{
		Close();
	}

	bool FileStream::Open(const String& path, FileMode mode)
	{
		Close();

		DWORD access = 0;
		DWORD shareMode = 0;
		DWORD create = 0;

		switch (mode)
		{
		case FileMode::OpenRead:
			access = GENERIC_READ;
			shareMode = FILE_SHARE_READ;
			create = OPEN_EXISTING;
			break;

		case FileMode::Create:
			access = GENERIC_WRITE;
			shareMode = FILE_SHARE_WRITE;
			create = CREATE_ALWAYS;
			break;

		case FileMode::Append:
			access = GENERIC_ALL;
			shareMode = FILE_SHARE_READ | FILE_SHARE_WRITE;
			create = OPEN_ALWAYS;
			break;
		}

		_handle = CreateFileA(path, access, shareMode,
			NULL, create, FILE_ATTRIBUTE_NORMAL, NULL);
		if (_handle == INVALID_HANDLE_VALUE)
			return false;

		_fileMode = mode;
		_path = path;
		return true;
	}

	void FileStream::Close()
	{
		if (!IsOpened())
			return;

		CloseHandle(_handle);
		_handle = INVALID_HANDLE_VALUE;
		_path.Clear();
	}

	bool FileStream::CanRead() const
	{
		return IsOpened();
	}

	bool FileStream::CanWrite() const
	{
		return IsOpened() && _fileMode != FileMode::OpenRead;
	}

	bool FileStream::CanSeek() const
	{
		return IsOpened();
	}

	bool FileStream::IsOpened() const
	{
		return (_handle != INVALID_HANDLE_VALUE);
	}

// 	bool FileStream::IsEOF() const
// 	{
// 		return !IsOpened() || engObject::GetEngine()->FileEof(_handle);
// 	}

	void FileStream::SetPosition(unsigned position)
	{
		if (!CanSeek())
			return;

		SetFilePointer(_handle, position, 0, FILE_BEGIN);
	}

	unsigned FileStream::GetPosition() const
	{
		if (!IsOpened())
			return 0;

		return SetFilePointer(_handle, 0, 0, FILE_CURRENT);
	}

	unsigned FileStream::GetLength() const
	{
		if (!IsOpened())
			return 0;

		return GetFileSize(_handle, 0);
	}

	int FileStream::Read(void* buffer, unsigned size)
	{
		if (!CanRead())
			return 0;

		DWORD readed;
		const BOOL ret = ReadFile(_handle, buffer, size, &readed, NULL);
		return readed;
	}

	int FileStream::Write(const void* buffer, unsigned size)
	{
		if (!CanWrite())
			return 0;

		DWORD writed;
		const BOOL ret = WriteFile(_handle, buffer, size, &writed, NULL);
		return writed;
	}
}