#ifndef SERVICES_H
#define SERVICES_H

#include <string>
#include <map>

class Services
{
public:
	template<typename T>
	static void registerService(const std::string& name, T* service)
	{
		mServices[name] = static_cast<void*>(service);
	}

	template<typename T>
	static T* getService(const std::string& name)
	{
		auto it = mServices.find(name);
		if (it != mServices.end())
		{
			return static_cast<T*>(it->second);
		}
		return nullptr;
	}
private:
	static std::map<std::string, void*> mServices;
};

#endif // SERVICES_H