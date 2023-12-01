#include "filterx/expr-function.h"

typedef struct _FilterXFunction
{
  FilterXExpr super;
  gchar *function_name;
  GList *argument_expressions;
} FilterXFunction;

static FilterXObject *
_eval(FilterXExpr *s)
{
  FilterXFunction *self = (FilterXFunction *) s;

  // lookup self->function_name
  // eval arguments filterx_expr_eval(FilterXExpr *self)
  // call function implementation with Object list as argument, which returns a FilterXObject
exit:
  return NULL;
}

static void
_free(FilterXExpr *s)
{
  FilterXFunction *self = (FilterXFunction *) s;
  g_free(self->function_name);
//  g_list_free_all(self->argument_expressions);
}

/* NOTE: takes the object reference */
FilterXExpr *
filterx_function_new(const gchar *function_name, GList *arguments)
{
  FilterXFunction *self = g_new0(FilterXFunction, 1);

  filterx_expr_init_instance(&self->super);
  self->super.eval = _eval;
  self->super.free_fn = _free;
  self->function_name = g_strdup(function_name);
  return &self->super;
}
