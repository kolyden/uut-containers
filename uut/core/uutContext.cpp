#include "uutContext.h"
#include "uutModule.h"

namespace uut
{
	Context::Context()
		: _inited(false)
	{
	}

	void Context::Init()
	{
		if (_inited)
			return;

		_inited = true;
		for (auto& it : _modules)
			it.second->OnRegister();

		for (auto& it : _modules)
			it.second->OnInit();
	}

	void Context::AddModule(Module* module)
	{
		if (module == nullptr)
			return;

		_modules[module->GetTypeName()] = module;

		if (_inited)
		{
			module->OnRegister();
			module->OnInit();
		}
	}

	Module* Context::GetModule(const HashString& type) const
	{
		auto it = _modules.Find(type);
		if (it == _modules.End())
			return nullptr;

		return it->second;
	}

	void Context::AddFactory(ObjectFactory* factory)
	{
		if (factory == nullptr)
			return;

		_factories[factory->GetTypeInfo()._name] = factory;
	}

	ObjectFactory* Context::GetFactory(const HashString& type) const
	{
		auto it = _factories.Find(type);
		if (it == _factories.End())
			return nullptr;

		return it->second;
	}

	SharedPtr<Object> Context::CreateObject(const HashString& type) const
	{
		auto factory = GetFactory(type);
		if (factory == nullptr)
			return SharedPtr<Object>::EMPTY;

		return factory->CreateObject();
	}

	Context* Context::GetMain()
	{
		static Context core;
		return &core;
	}
}