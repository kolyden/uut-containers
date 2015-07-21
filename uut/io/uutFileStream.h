#pragma once
#include "uutStream.h"
#include <windows.h>

namespace uut
{
	enum class FileMode
	{
		OpenRead,
		Create,
		Append,
	};

	class FileStream : public Stream
	{
		OBJECT(FileStream, Stream)
	public:
		FileStream();
		virtual ~FileStream();

		bool Open(const String& path, FileMode mode);
		void Close();
		const String& GetPath() const { return _path; }

		virtual bool CanRead() const override;
		virtual bool CanWrite() const override;
		virtual bool CanSeek() const override;
		virtual bool IsOpened() const override;
// 		virtual bool IsEOF() const override;

		virtual void SetPosition(unsigned position) override;
		virtual unsigned GetPosition() const override;
		virtual unsigned GetLength() const override;

		virtual int Read(void* buffer, unsigned size) override;
		virtual int Write(const void* buffer, unsigned size) override;

	protected:
		HANDLE _handle;
		FileMode _fileMode;
		String _path;
	};
}