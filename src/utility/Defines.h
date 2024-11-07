#pragma once

// only some global macros are here, other are defined where they are relevant

#define SINGLETON(ClassName)    private: \
                                    ClassName() { } \
                                public: \
                                    ClassName(const ClassName& src) = delete; \
                                    void operator = (const ClassName& rhs) = delete; \
                                    static ClassName& GetInstance() { static ClassName instance; return instance; }

#define STR(type) #type
#define PAIR(t1, t2) std::make_pair(t1, t2)
#define REF(var) std::ref(var)