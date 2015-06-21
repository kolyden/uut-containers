#include "uutCore.h"
#include "uutModule.h"

namespace uut
{
	Core::Core()
	{
	}

	void Core::AddModule(Module* module)
	{
		if (module == nullptr)
			return;

		_modules[module->GetTypeName()] = module;
	}

	Module* Core::GetModule(const HashString& type) const
	{
		auto it = _modules.Find(type);
		if (it == _modules.End())
			return nullptr;

		return it->second;
	}

	void Core::AddFactory(ObjectFactory* factory)
	{
		if (factory == nullptr)
			return;

		_factories[factory->GetTypeInfo()._name] = factory;
	}

	ObjectFactory* Core::GetFactory(const HashString& type) const
	{
		auto it = _factories.Find(type);
		if (it == _factories.End())
			return nullptr;

		return it->second;
	}

	SharedPtr<Object> Core::CreateObject(const HashString& type) const
	{
		auto factory = GetFactory(type);
		if (factory == nullptr)
			return SharedPtr<Object>::EMPTY;

		return factory->CreateObject();
	}

	Core* Core::GetMain()
	{
		static Core core;
		return &core;
	}
}