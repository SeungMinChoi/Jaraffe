#pragma once

// Singleton
#define SINGLETONE(class_name) private: class_name(void); ~class_name(void); \
public: static class_name* GetInstance() { static class_name instance; return &instance; }

// Safe Macros
#define ReleaseCOM(x)		{ if(x){ x->Release(); } }
#define ReleaseCOM_PTR(x)	{ if(x){ x.Release(); } }
#define ReleasePX(x)		{ if(x){ x->release(); } }
#define SafeDelete(x)		{ delete x; x = 0; }

// Check
#define HR(x) (x)
#define RETURN_IF(x, y) if(x) return y;
#define CONTINUE_IF(x) if(x) continue;