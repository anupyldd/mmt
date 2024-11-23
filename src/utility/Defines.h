#pragma once

// only some global macros are here, other are defined where they are relevant

#define HND_SINGLETON(ClassName)    private: \
                                    ClassName() { } \
                                public: \
                                    ClassName(const ClassName& src) = delete; \
                                    void operator = (const ClassName& rhs) = delete; \
                                    static ClassName& GetInstance() { static ClassName instance; return instance; }

// idk if i should add a prefix to these, since their point is to do less typing
#define STR(type) #type
#define PAIR(t1, t2) std::make_pair(t1, t2)
#define REF(var) std::ref(var)

#define HND_DESERIALIZE(var) std::make_pair(std::ref(var), #var)
#define HND_DESERIALIZE_EX(var, var2) std::make_pair(std::ref(var), #var2)

#define HND_SERIALIZE(var) std::make_pair(var, #var)
#define HND_SERIALIZE_EX(var, var2) std::make_pair(var, #var2)