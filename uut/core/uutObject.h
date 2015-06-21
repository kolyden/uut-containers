#pragma once
#include "uutPtr.h"
#include "uutTypeInfo.h"

namespace uut
{
	class Core;
	class Module;

#define OBJECT(type, basetype) \
	public: \
		typedef type Classname; \
		typedef basetype Super; \
		static const TypeInfo& GetTypeInfoStatic() { static const TypeInfo type(#type, typeid(type)); return type; } \
		static const HashString& GetTypeNameStatic() { return GetTypeInfoStatic()._name; } \
		virtual const TypeInfo& GetTypeInfo() const { return GetTypeInfoStatic(); }; \
		virtual const HashString& GetTypeName() const { return GetTypeNameStatic(); }; \
	private:

	//////////////////////////////////////////////////////////////////////////
	class UUT_API Object : public RefCounted
	{
		OBJECT(Object, Object)
	public:
		typedef Object Classname;

		virtual ~Object() {}

		static Core* GetCore();
		static Module* GetModule(const HashString& type);
		template<class T>static T* GetModule() { return (T*)GetModule(T::GetTypeNameStatic()); }

	private:
		friend class Core;
	};

	//////////////////////////////////////////////////////////////////////////
	class ObjectFactory : public RefCounted
	{
	public:
		virtual SharedPtr<Object> CreateObject() = 0;
		virtual const TypeInfo& GetTypeInfo() const = 0;
	};

	template<class T>
	class ObjectFactoryImpl : public ObjectFactory
	{
	public:
		virtual SharedPtr<Object> CreateObject() override { return new T(); }
		virtual const TypeInfo& GetTypeInfo() const override { return T::GetTypeInfo(); }
	};
}