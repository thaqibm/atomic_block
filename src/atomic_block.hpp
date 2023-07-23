
#include <cstdio>
#include <utility>
namespace atomic_detail {

  struct AtomicDummy {};

  template <typename Fun>
    struct AtomicScope {
      Fun f;

      AtomicScope(Fun&& f): f(std::forward<Fun>(f)) {
        init();
      }
      void init(){
        f();
      }
    };

  template <typename Fun>
    auto operator+(AtomicDummy _info, Fun&& fn){
      auto atomscope = AtomicScope(std::forward<Fun>(fn));
      return atomscope;
    }
} // namespace atomic_detail


// MACRO Magic


#define CONCAT_IMPL(s1, s2) s1##s2
#define CONCAT(s1, s2) CONCAT_IMPL(s1, s2)

#ifdef __COUNTER__
#define ATOM_ANON_VAR(name) \
  CONCAT(name, __COUNTER__)
#else
#define ATOM_ANON_VAR(name) \
  CONCAT(name, __LINE__)
#endif // __COUNTER__

#define atomic_block \
  auto ATOM_ANON_VAR(_ATOM_LAMBDA) \
    = ::atomic_detail::AtomicDummy{} +  [&]() mutable noexcept

