#pragma once


#define DECLARE_SINGLE(classname)		\
private:								\
	classname() {}						\
public:									\
	static classname* GetInstance()		\
	{									\
		static classname s_instance;	\
		return &s_instance;				\
	}									

#define GET_SINGLE(classname) classname::GetInstance()

#define SAFE_DELETE(ptr)		\
	if (ptr)					\
	{							\
		delete ptr;				\
		ptr = nullptr;			\
	}


#define DEBUG_LOG(hdc, y, str)	\
::TextOut(hdc, 650 + (y) * 20, str.c_str(), static_cast<int32>(str.size()))