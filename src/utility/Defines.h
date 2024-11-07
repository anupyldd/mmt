#pragma once

#define SINGLETON(ClassName)    private: \
                                    ClassName() { } \
                                public: \
                                    ClassName(const ClassName& src) = delete; \
                                    void operator = (const ClassName& rhs) = delete; \
                                    static ClassName& GetInstance() { static ClassName instance; return instance; }

#define STR(type) #type
