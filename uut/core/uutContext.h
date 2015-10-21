#pragma once
#include "uutPtr.h"
#include "uutTypeInfo.h"
#include "containers/uutDictionary.h"

namespace uut
{
	class Module;
	class Object;
	class ObjectFactory;

	class Context
	{
	public:
		void Init();

		void AddModule(Module* module);
		Module* GetModule(const HashString& type) const;
		template<class T>T* GetModule() const { return (T*)GetModule(T::GetTypeNameStatic()); }

		void AddFactory(ObjectFactory* factory);
		ObjectFactory* GetFactory(const HashString& type) const;

		SharedPtr<Object> CreateObject(const HashString& type) const;

		static Context* GetMain();

	protected:
		bool _inited;

		Context();

		Dictionary<HashString, SharedPtr<Module>> _modules;
		Dictionary<HashString, SharedPtr<ObjectFactory>> _factories;
	};
}