#include "filterx/expr-builtin.h"
#include "filterx/object-primitive.h"

typedef struct _FilterXBuiltinFilter
{
  FilterXExpr super;
  FilterExprNode *expr;
} FilterXBuiltinFilter;

static FilterXObject *
_eval(FilterXExpr *s)
{
  FilterXBuiltinFilter *self = (FilterXBuiltinFilter *) s;
  FilterXEvalContext *context = filterx_eval_get_context();

  /* FIXME: path_options */
  gboolean result = filter_expr_eval_root_with_context(self->expr, context->msgs, context->num_msg, context->template_eval_options, NULL);
  return filterx_boolean_new(result);
}

static void
_free(FilterXExpr *s)
{
  FilterXBuiltinFilter *self = (FilterXBuiltinFilter *) s;
  filter_expr_unref(self->expr);
}

FilterXExpr *
filterx_builtin_filter_new(FilterExprNode *expr)
{
  FilterXBuiltinFilter *self = g_new0(FilterXBuiltinFilter, 1);

  filterx_expr_init_instance(&self->super);
  self->super.eval = _eval;
  self->super.free_fn = _free;
  self->expr = expr;
  return &self->super;
}
