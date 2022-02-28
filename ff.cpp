#include <bitset>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>

using std::cout;
using std::endl;

class THD {};
class PT_item_list;
class POS {};
class Item {};
class LEX_STRING {};

class Item_func_abs : public Item {
public:
  Item_func_abs(POS pos, PT_item_list *args) {}
};

template <typename Function_class, uint Min_argc, uint Max_argc = Min_argc>
class Instantiator {
public:
  static const uint Min_argcount = Min_argc;
  static const uint Max_argcount = Max_argc;

  Item *instantiate(THD *thd, PT_item_list *args) {
    return new /* (thd->mem_root) */ Function_class(POS(), args);
  }
};

class Create_func {
public:
  /**
    The builder create method.
    Given the function name and list or arguments, this method creates
    an <code>Item</code> that represents the function call.
    In case or errors, a NULL item is returned, and an error is reported.
    Note that the <code>thd</code> object may be modified by the builder.
    In particular, the following members/methods can be set/called,
    depending on the function called and the function possible side effects.
    <ul>
      <li><code>thd->lex->binlog_row_based_if_mixed</code></li>
      <li><code>thd->lex->current_context()</code></li>
      <li><code>thd->lex->safe_to_cache_query</code></li>
      <li><code>thd->lex->uncacheable(UNCACHEABLE_SIDEEFFECT)</code></li>
      <li><code>thd->lex->uncacheable(UNCACHEABLE_RAND)</code></li>
      <li><code>thd->lex->add_time_zone_tables_to_query_tables(thd)</code></li>
    </ul>
    @param thd The current thread
    @param name The function name
    @param item_list The list of arguments to the function, can be NULL
    @return An item representing the parsed function call, or NULL
  */
  virtual Item *create_func(THD *thd, LEX_STRING name,
                            PT_item_list *item_list) = 0;
};

uint arglist_length(const PT_item_list *args) {
  if (args == nullptr)
    return 0;
  return 1;
}

bool check_argcount_bounds(THD *thd, LEX_STRING function_name,
                           PT_item_list *item_list, uint min_argcount,
                           uint max_argcount) {
  uint argcount = arglist_length(item_list);
  if (argcount < min_argcount || argcount > max_argcount) {
    //    my_error(ER_WRONG_PARAMCOUNT_TO_NATIVE_FCT, MYF(0),
    //    function_name.str);
    return true;
  }
  return false;
}

template <typename Instantiator_fn>
class Function_factory : public Create_func {
public:
  Item *create_func(THD *thd, LEX_STRING function_name,
                    PT_item_list *item_list) override {
    if (check_argcount_bounds(thd, function_name, item_list,
                              m_instantiator.Min_argcount,
                              m_instantiator.Max_argcount))
      return nullptr;
    return m_instantiator.instantiate(thd, item_list);
  }

private:
  //  Function_factory() {}
  Instantiator_fn m_instantiator;
};

Function_factory<Item_func_abs> s_singleton;

#define SQL_FN(F, N) &Function_factory<Instantiator<F, N>>::s_singleton

static constexpr std::pair<const char *, Create_func *> func_array[] = {
    {"ABS", SQL_FN(Item_func_abs, 1)},
};

int main() { cout << "Hej hopp" << endl; }
